/**
 * @file ipcheck.cpp
 * @brief Implements IP filtering logic for the Load Balancer Project.
 *
 * This file defines the functionality for determining whether
 * an incoming IP address should be blocked based on a configured
 * starting and ending range for the first octet.
 *
 * The firewall checks only the first segment of the IP address
 * and blocks requests that fall within the specified range.
 *
 * @author Anthony Huang
 * @course CSCE 412 Cloud Computing
 * @project Load Balancer Project
 * @date 3/1/2026
 */

#include "ipcheck.h"
#include <sstream>

/**
 * @brief Constructs an IP filtering object.
 *
 * Initializes the blocked IP range using the provided
 * starting and ending values for the first octet.
 *
 * @param start The starting value of the blocked range.
 * @param end The ending value of the blocked range.
 */
ip_check::ip_check(int start, int end)
{
    start_block = start;
    end_block = end;
}

/**
 * @brief Determines whether an IP address is blocked.
 *
 * Extracts the first octet of the IP address and checks
 * whether it falls within the configured blocked range.
 *
 * @param ip The IP address as a string.
 * @return True if the IP address is blocked, false otherwise.
 */
bool ip_check::blocked(std::string ip)
{
    std::stringstream ss(ip);
    std::string first_part;
    std::getline(ss, first_part, '.');

    if (first_part.length() == 0)
    {
        return false;
    }

    int number = std::stoi(first_part);

    if (number >= start_block)
    {
        if (number <= end_block)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}