#pragma once

/**
 * @file ipcheck.h
 * @brief Defines the ip_check class used for firewall filtering.
 *
 * The ip_check class determines whether an incoming IP address
 * should be blocked based on a configured range applied to the
 * first octet of the IP address.
 *
 * @author Anthony Huang
 * @course CSCE 412 Cloud Computing
 * @project Load Balancer Project
 * @date 3/1/2026
 */

#include <string>

/**
 * @class ip_check
 * @brief Simulates a simple firewall IP filter.
 *
 * This class blocks IP addresses whose first octet
 * falls within a specified numeric range.
 */
class ip_check {
private:

    /** Starting value of blocked IP range (first octet). */
    int start_block;

    /** Ending value of blocked IP range (first octet). */
    int end_block;

public:

    /**
     * @brief Constructs an IP filter.
     *
     * Initializes the firewall with a starting and ending
     * range for blocked IP addresses.
     *
     * @param start Lower bound of blocked range (default 100).
     * @param end Upper bound of blocked range (default 200).
     */
    ip_check(int start = 100, int end = 200);

    /**
     * @brief Checks whether an IP address is blocked.
     *
     * Extracts the first octet of the IP address and compares
     * it to the configured blocked range.
     *
     * @param ip The IP address as a string.
     * @return True if the IP is blocked, false otherwise.
     */
    bool blocked(std::string ip);
};