#pragma once

/**
 * @file request.h
 * @brief Defines the request structure used in the Load Balancer Project.
 *
 * The request structure represents a simulated network request.
 * Each request contains:
 * - A processing time in clock cycles
 * - A request type (Processing or Streaming)
 * - An incoming IP address
 * - An outgoing IP address
 *
 * Requests are randomly generated in the constructor.
 *
 * @author Anthony Huang
 * @course CSCE 412 Cloud Computing
 * @project Load Balancer Project
 * @date 3/1/2026
 */

#include <string>

/**
 * @struct request
 * @brief Represents a simulated network request.
 *
 * A request includes metadata such as processing time,
 * request type, and source and destination IP addresses.
 */
struct request {

    /** Processing time required in clock cycles (1–10). */
    int time;

    /** Type of request: 'P' for processing or 'S' for streaming. */
    char type;

    /** Incoming IP address. */
    std::string ip_in;

    /** Outgoing IP address. */
    std::string ip_out;

    /**
     * @brief Constructs a randomly generated request.
     *
     * Generates random IP addresses, assigns a random
     * processing time, and randomly selects a request type.
     */
    request();
};