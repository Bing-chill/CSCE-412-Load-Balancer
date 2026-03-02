/**
 * @file Switch.cpp
 * @brief Implements the Switch class for routing requests.
 *
 * The Switch class simulates a higher-level network router
 * that directs incoming requests to either the processing
 * or streaming load balancer based on request type.
 *
 * It coordinates simulation cycles and generates separate
 * log files for each system.
 *
 * @author Anthony Huang
 * @course CSCE 412 Cloud Computing
 * @project Load Balancer Project
 * @date 3/1/2026
 */

#include "Switch.h"
#include <cstdlib>
#include <iostream>

/**
 * @brief Constructs a Switch instance.
 *
 * Initializes separate load balancers for processing
 * and streaming requests.
 *
 * @param num_processing Number of processing servers.
 * @param num_streaming Number of streaming servers.
 * @param num_cycles Number of simulation cycles to run.
 */
Switch::Switch(int num_processing, int num_streaming, int num_cycles)
    : processing_lb(num_processing, num_cycles),
      streaming_lb(num_streaming, num_cycles)
{
    this->num_cycles = num_cycles;
}

/**
 * @brief Executes the full simulation for one run.
 *
 * For each cycle:
 * - Randomly generates a request
 * - Routes it to the appropriate load balancer
 * - Executes one cycle for both load balancers
 *
 * After completion, logs are generated for both systems.
 *
 * @param run_number Identifier for the simulation run.
 */
void Switch::start(int run_number,
                   int processing_servers,
                   int streaming_servers,
                   int cycles)
{
    for (int i = 0; i < num_cycles; i++)
    {
        int x = rand() % 5;

        if (x == 0)
        {
            request r;

            if (r.type == 'P')
                processing_lb.add_external_request(r);
            else
                streaming_lb.add_external_request(r);
        }

        processing_lb.run_one_cycle();
        streaming_lb.run_one_cycle();
    }
    processing_lb.log(run_number, processing_servers, cycles);
    streaming_lb.log(run_number, streaming_servers, cycles);
}