/**
 * @file webserver.cpp
 * @brief Implements the web_server class for request processing.
 *
 * The web_server class simulates a single server that can
 * process one request at a time. Each server tracks whether
 * it is busy and how many clock cycles remain for the current task.
 *
 * @author Anthony Huang
 * @course CSCE 412 Cloud Computing
 * @project Load Balancer Project
 * @date 3/1/2026
 */

#include "webserver.h"

/**
 * @brief Constructs a web_server instance.
 *
 * Initializes the server as idle with zero remaining time.
 */
web_server::web_server() {
    busy = false;
    time_left = 0;
}

/**
 * @brief Checks whether the server is currently busy.
 *
 * @return True if the server is processing a request,
 *         false otherwise.
 */
bool web_server::is_busy() {
    if (busy == true) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Assigns a request to the server.
 *
 * If the server is idle, it accepts the request and sets
 * the remaining processing time. If the server is already
 * busy, the request is ignored.
 *
 * @param r The request to process.
 */
void web_server::take_job(request r) {
    if (busy == false) {
        time_left = r.time;

        if (time_left > 0) {
            busy = true;
        } else {
            busy = false;
        }
    } else {
        busy = busy;
    }
}

/**
 * @brief Updates the server state for one clock cycle.
 *
 * If the server is busy, the remaining processing time
 * is decremented. Once the remaining time reaches zero,
 * the server becomes idle.
 */
void web_server::update() {

    if (busy == true) {

        time_left = time_left - 1;

        if (time_left > 0) {
            busy = true;
        } else {
            if (time_left == 0) {
                busy = false;
            } else {
                busy = false;
            }
        }

    } else {
        busy = false;
    }
}