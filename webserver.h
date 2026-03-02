#pragma once

/**
 * @file webserver.h
 * @brief Defines the web_server class for handling individual requests.
 *
 * The web_server class simulates a single server in the load
 * balancing system. Each server can process one request at a time
 * and tracks how many clock cycles remain before completing the task.
 *
 * @author Anthony Huang
 * @course CSCE 412 Cloud Computing
 * @project Load Balancer Project
 * @date 3/1/2026
 */

#include "request.h"

/**
 * @class web_server
 * @brief Simulates a single request-processing server.
 *
 * Each web_server instance:
 * - Accepts one request at a time
 * - Tracks whether it is currently busy
 * - Decrements processing time each cycle
 * - Becomes idle once processing is complete
 */
class web_server {
private:

    /** Indicates whether the server is currently processing a request. */
    bool busy;

    /** Remaining processing time in clock cycles. */
    int time_left;

public:

    /**
     * @brief Constructs a web_server instance.
     *
     * Initializes the server in an idle state.
     */
    web_server();

    /**
     * @brief Checks if the server is currently busy.
     *
     * @return True if processing a request, false otherwise.
     */
    bool is_busy();

    /**
     * @brief Assigns a request to the server.
     *
     * If the server is idle, it begins processing the request.
     *
     * @param r The request to process.
     */
    void take_job(request r);

    /**
     * @brief Updates the server for one simulation cycle.
     *
     * Decrements the remaining processing time. If time reaches zero,
     * the server becomes idle.
     */
    void update();
};