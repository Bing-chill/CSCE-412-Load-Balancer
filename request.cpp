/**
 * @file request.cpp
 * @brief Implements the request class for the Load Balancer Project.
 *
 * The request class represents a simulated network request.
 * Each request randomly generates:
 * - An incoming IP address
 * - An outgoing IP address
 * - A processing time between 1 and 10 cycles
 * - A request type (Processing or Streaming)
 *
 * @author Anthony Huang
 * @course CSCE 412 Cloud Computing
 * @project Load Balancer Project
 * @date 3/1/2026
 */

#include "request.h"

/**
 * @brief Constructs a random request.
 *
 * Generates random IP addresses for incoming and outgoing traffic,
 * assigns a random processing time between 1 and 10 cycles,
 * and randomly selects a request type:
 * - 'P' for processing
 * - 'S' for streaming
 */
request::request()
{
    int a = rand() % 150;
    int b = rand() % 200;
    int c = rand() % 250;
    int d = rand() % 200;

    ip_in = std::to_string(a) + "." + std::to_string(b) + "." + std::to_string(c) + "." + std::to_string(d);

    int e = rand() % 150;
    int f = rand() % 200;
    int g = rand() % 250;
    int h = rand() % 200;

    ip_out = std::to_string(e) + "." + std::to_string(f) + "." + std::to_string(g) + "." + std::to_string(h);

    time = rand() % 10 + 1;

    if (rand() % 2 == 0) 
        type = 'P';
    else
        type = 'S';
}