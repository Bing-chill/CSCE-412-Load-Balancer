/**
 * @file Loadbalancer.cpp
 * @brief Implements the loadbalancer class for dynamic server scaling.
 *
 * Contains the implementation of request distribution,
 * dynamic server balancing, firewall filtering, and logging.
 *
 * @author Anthony Huang
 * @course CSCE 412 Cloud Computing
 * @project Load Balancer Project
 * @date 3/1/2026
 */

#include "loadbalancer.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

/**
 * @brief Constructs a loadbalancer instance.
 *
 * Initializes server counters, creates the initial number of servers,
 * and preloads the queue with a starting workload equal to
 * 100 × server_count.
 *
 * @param server_count Initial number of active servers.
 * @param cycle_count Number of simulation cycles to execute.
 */
loadbalancer::loadbalancer(int server_count, int cycle_count)
{
    num_cycles = cycle_count;
    total_requests = 0;
    rejected_requests = 0;
    wait_time = 0;
    initial_server_count = server_count;

    servers_added = 0;
    servers_removed = 0;
    completed_requests = 0;

    for (int i = 0; i < server_count; i++)
        add_server();

    int starting_requests = server_count * 100;

    for (int i = 0; i < starting_requests; i++)
    {
        request r;

        if (!firewall.blocked(r.ip_in))
        {
            q.push(r);
            total_requests++;
        }
        else
        {
            rejected_requests++;
        }
    }

    starting_queue_size = q.size();
    peak_queue_size = q.size();
}

/**
 * @brief Dynamically allocates a new web server.
 *
 * Adds a new server instance to the server pool
 * and increments the servers_added counter.
 */
void loadbalancer::add_server()
{
    servers.push_back(std::make_unique<web_server>());
    servers_added++;
}

/**
 * @brief Dynamically removes a web server.
 *
 * Removes the most recently added server if more than
 * one server is active. Ensures at least one server
 * remains in the system.
 */
void loadbalancer::remove_server()
{
    if (servers.size() > 1)
    {
        servers.pop_back();
        servers_removed++;
    }
}

/**
 * @brief Balances the number of active servers.
 *
 * Adds a server if the queue exceeds 80 × server_count.
 * Removes a server if the queue falls below 50 × server_count.
 * A cooldown timer prevents rapid oscillation.
 */
void loadbalancer::balance()
{
    if (wait_time > 0)
    {
        wait_time--;
        return;
    }

    int server_count = servers.size();
    size_t lower_limit = 50 * server_count;
    size_t upper_limit = 80 * server_count;

    if (q.size() > upper_limit)
    {
        add_server();
        wait_time = 5;
    }
    else if (q.size() < lower_limit && servers.size() > 1)
    {
        remove_server();
        wait_time = 5;
    }
}

/**
 * @brief Assigns queued requests to available servers.
 *
 * Iterates through the server pool and assigns jobs
 * to any idle server while the queue is not empty.
 */
void loadbalancer::give_jobs()
{
    for (size_t i = 0; i < servers.size(); i++)
    {
        if (!servers[i]->is_busy() && !q.empty())
        {
            request next = q.front();
            q.pop();
            servers[i]->take_job(next);
        }
    }
}

/**
 * @brief Counts the number of active and inactive servers.
 *
 * @param active Reference to store number of busy servers.
 * @param inactive Reference to store number of idle servers.
 */
void loadbalancer::count_servers(int &active, int &inactive)
{
    active = 0;
    inactive = 0;

    for (size_t i = 0; i < servers.size(); i++)
    {
        if (servers[i]->is_busy())
            active++;
        else
            inactive++;
    }
}

/**
 * @brief Executes a single simulation cycle.
 *
 * Performs:
 * - Queue peak tracking
 * - Server balancing
 * - Job assignment
 * - Server state updates
 * - Completion tracking
 */
void loadbalancer::run_one_cycle()
{
    if (q.size() > peak_queue_size)
        peak_queue_size = q.size();

    balance();
    give_jobs();

    for (size_t i = 0; i < servers.size(); i++)
    {
        bool was_busy = servers[i]->is_busy();
        servers[i]->update();

        if (was_busy && !servers[i]->is_busy())
            completed_requests++;
    }
}

/**
 * @brief Adds an externally generated request.
 *
 * Applies firewall filtering before insertion into queue.
 *
 * @param r The request to add.
 */
void loadbalancer::add_external_request(request r)
{
    if (!firewall.blocked(r.ip_in))
    {
        q.push(r);
        total_requests++;
    }
    else
    {
        rejected_requests++;
    }
}

/**
 * @brief Generates a log file for a simulation run.
 *
 * Logs:
 * - Initial configuration
 * - Starting queue state
 * - Runtime events
 * - Aggregate statistics
 * - Final system status
 *
 * @param run_number The run identifier.
 * @param input_servers Number of servers entered by user.
 * @param input_cycles Number of cycles entered by user.
 */
void loadbalancer::log(int run_number,
                       int input_servers,
                       int input_cycles)
{
    int active;
    int inactive;

    std::string filename = "logs/run_" + std::to_string(run_number) + ".txt";
    std::ofstream logfile(filename);

    logfile << "User entered server count: " << input_servers << "\n";
    logfile << "User entered cycles: " << input_cycles << "\n";
    logfile << "Task time range: 1 - 10 cycles\n\n";

    logfile << "Starting queue size: " << starting_queue_size << "\n\n";

    logfile << "Runtime Event\n";

    for (int cycle = 0; cycle < num_cycles; cycle++)
    {
        int random_value = rand() % 5;

        if (random_value == 0)
        {
            request r;

            if (!firewall.blocked(r.ip_in))
            {
                q.push(r);
                total_requests++;
                logfile << "New Request Time=" << r.time
                        << " | Queue size: " << q.size() << "\n";
            }
            else
            {
                rejected_requests++;
                logfile << "Blocked Request rejected\n";
            }
        }

        size_t previous_server_count = servers.size();
        run_one_cycle();

        if (servers.size() > previous_server_count)
            logfile << "Scale up Servers now: " << servers.size() << "\n";
        else if (servers.size() < previous_server_count)
            logfile << "Scale down Servers now: " << servers.size() << "\n";
    }

    count_servers(active, inactive);

    logfile << "Log Information \n";
    logfile << "Total requests generated: " << total_requests << "\n";
    logfile << "Rejected requests: " << rejected_requests << "\n";
    logfile << "Peak queue size: " << peak_queue_size << "\n";
    logfile << "Servers added: " << servers_added << "\n";
    logfile << "Servers removed: " << servers_removed << "\n";
    logfile << "Completed requests: " << completed_requests << "\n\n";

    logfile << "End Information Status\n";
    logfile << "Ending queue size: " << q.size() << "\n";
    logfile << "Active servers: " << active << "\n";
    logfile << "Inactive servers: " << inactive << "\n";
    logfile << "Final server count: " << servers.size() << "\n";
    logfile << "Remaining in queue: " << q.size() << "\n";

    logfile.close();
}