/**
 * @file main.cpp
 * @brief Entry point for the Load Balancer Project.
 *
 * This file handles user input and initializes the simulation
 * by creating a Switch object that manages processing and
 * streaming load balancers.
 *
 * The program allows the user to either:
 * - Run a single manual simulation
 * - Automatically run 10 simulations (for project requirement)
 *
 * @author Anthony Huang
 * @course CSCE 412 Cloud Computing
 * @project Load Balancer Project
 * @date 3/1/2026
 */

#include <iostream>
#include <ctime>
#include "Switch.h"

/**
 * @brief Program entry point.
 *
 * Collects user input for server counts and simulation cycles,
 * then asks whether to run once or automatically run 10 times.
 *
 * @return 0 upon successful completion.
 */
int main()
{
    int processing_servers;
    int streaming_servers;
    int cycles;
    int mode;

    std::cout << "Enter number of processing servers: ";
    std::cin >> processing_servers;

    while (processing_servers <= 0)
    {
        std::cout << "Enter a positive number: ";
        std::cin >> processing_servers;
    }

    std::cout << "Enter number of streaming servers: ";
    std::cin >> streaming_servers;

    while (streaming_servers <= 0)
    {
        std::cout << "Enter a positive number: ";
        std::cin >> streaming_servers;
    }

    std::cout << "Enter number of cycles: ";
    std::cin >> cycles;

    while (cycles <= 0)
    {
        std::cout << "Enter a positive number: ";
        std::cin >> cycles;
    }

    std::cout << "\nSelect mode:\n";
    std::cout << "1 - Run once\n";
    std::cout << "2 - Run 10 automatic simulations\n";
    std::cout << "Choice: ";
    std::cin >> mode;

    if (mode == 2)
    {
        for (int i = 1; i <= 10; i++)
        {
            srand(time(0) + i);  
            Switch s(processing_servers, streaming_servers, cycles);
            s.start(i, processing_servers, streaming_servers, cycles);
        }

        std::cout << "\nCompleted 10 automatic runs.\n";
    }
    else
    {
        srand(time(0));
        Switch s(processing_servers, streaming_servers, cycles);
        s.start(1, processing_servers, streaming_servers, cycles);

        std::cout << "\nCompleted single run.\n";
    }

    return 0;
}