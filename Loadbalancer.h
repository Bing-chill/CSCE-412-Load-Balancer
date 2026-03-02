#pragma once
/**
 * @file Loadbalancer.h
 * @brief Implements the loadbalancer class for dynamic server scaling.
 *
 * The loadbalancer class simulates a cloud load balancing system.
 * It manages a queue of incoming requests, dynamically allocates
 * and deallocates servers, and applies firewall filtering.
 *
 * The system maintains the queue size between 50 and 80 times
 * the number of active servers and prevents rapid scaling using
 * a cooldown timer.
 *
 * @author Anthony Huang
 * @course CSCE 412 Cloud Computing
 * @project Load Balancer Project
 * @date 3/1/2026
 */

#include <queue>
#include <vector>
#include <memory>
#include "request.h"
#include "webserver.h"
#include "ipcheck.h"

/**
 * @class loadbalancer
 * @brief Simulates a dynamic load balancing system.
 *
 * This class manages:
 * - A queue of incoming requests
 * - A collection of active web servers
 * - Firewall filtering for incoming IP addresses
 * - Dynamic server scaling based on workload
 */
class loadbalancer
{

private:

    /** Queue storing incoming requests waiting to be processed. */
    std::queue<request> q;

    /** Collection of dynamically allocated web servers. */
    std::vector<std::unique_ptr<web_server>> servers;

    /** Firewall object used to block specific IP ranges. */
    ip_check firewall;

    /** Total number of accepted requests. */
    int total_requests;

    /** Number of simulation cycles to execute. */
    int num_cycles;

    /** Cooldown timer to prevent rapid scaling changes. */
    int wait_time;

    /** Initial size of the request queue. */
    int starting_queue_size;

    /** Highest recorded queue size during simulation. */
    size_t peak_queue_size;

    /** Total number of completed requests. */
    int completed_requests;

    /** Number of servers dynamically added. */
    int servers_added;

    /** Number of servers dynamically removed. */
    int servers_removed;

    /** Number of rejected requests. */
    int rejected_requests;

    /** Number of initial servers. */
    int initial_server_count;

    /**
     * @brief Dynamically allocates a new server.
     */
    void add_server();

    /**
     * @brief Dynamically removes an existing server.
     */
    void remove_server();

    /**
     * @brief Balances server count based on queue thresholds.
     *
     * Adds a server if queue exceeds 80×servers.
     * Removes a server if queue drops below 50×servers.
     */
    void balance();

    /**
     * @brief Assigns queued requests to available servers.
     */
    void give_jobs();

    /**
     * @brief Counts active and inactive servers.
     *
     * @param active Number of busy servers.
     * @param inactive Number of idle servers.
     */
    void count_servers(int &active, int &inactive);

public:

    /**
     * @brief Constructs a loadbalancer instance.
     *
     * Initializes the specified number of servers and prepares
     * the simulation environment.
     *
     * @param server_count Initial number of servers.
     * @param cycle_count Number of cycles to simulate.
     */
    loadbalancer(int server_count, int cycle_count);

    /** Deleted copy constructor to prevent copying. */
    loadbalancer(const loadbalancer&) = delete;

    /** Deleted assignment operator to prevent copying. */
    loadbalancer& operator=(const loadbalancer&) = delete;

    /**
     * @brief Adds an external request into the queue.
     *
     * @param r The request to add.
     */
    void add_external_request(request r);

    /**
     * @brief Executes a single simulation cycle.
     */
    void run_one_cycle();

    /**
     * @brief Logs simulation statistics to file.
     */
    void log(int run_number, int input_servers, int input_cycles);

    /**
     * @brief Starts the full load balancing simulation.
     */
    void start();
};