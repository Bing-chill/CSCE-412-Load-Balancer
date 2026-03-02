/**
 * @file Switch.h
 * @brief Defines the Switch class for routing requests.
 *
 * The Switch class simulates a higher-level network router
 * that directs incoming requests to either a processing
 * load balancer or a streaming load balancer based on
 * the request type.
 *
 * This allows separation of workloads and mimics real
 * cloud architectures where different traffic types
 * are handled independently.
 *
 * @author Anthony Huang
 * @course CSCE 412 Cloud Computing
 * @project Load Balancer Project
 * @date 3/1/2026
 */

#ifndef SWITCH_H
#define SWITCH_H

#include "loadbalancer.h"
#include "request.h"

/**
 * @class Switch
 * @brief Routes requests to appropriate load balancers.
 *
 * The Switch maintains two load balancer instances:
 * - One for processing ('P') requests
 * - One for streaming ('S') requests
 *
 * It executes simulation cycles and forwards requests
 * based on job type.
 */
class Switch
{
private:

    /** Load balancer handling processing ('P') requests. */
    loadbalancer processing_lb;

    /** Load balancer handling streaming ('S') requests. */
    loadbalancer streaming_lb;

    /** Total number of simulation cycles. */
    int num_cycles;

public:

    /**
     * @brief Constructs a Switch instance.
     *
     * Initializes separate load balancers for processing
     * and streaming workloads.
     *
     * @param num_processing Number of processing servers.
     * @param num_streaming Number of streaming servers.
     * @param num_cycles Number of simulation cycles.
     */
    Switch(int num_processing, int num_streaming, int num_cycles);

    /**
     * @brief Starts the full simulation.
     *
     * Runs the configured number of cycles, routes
     * generated requests to the correct load balancer,
     * and generates log files for the given run number.
     *
     * @param run_number The simulation run identifier.
     */
    void start(int run_number,
           int processing_servers,
           int streaming_servers,
           int cycles);
};

#endif