# Load Balancer Project

## Overview

This project simulates how a large company manages incoming web traffic using a load balancer. The system models web requests, web servers, and load balancers over a number of clock cycles.

Each request contains:
- An incoming IP address
- An outgoing IP address
- A processing time (in clock cycles)
- A job type: 
  - 'P' for Processing
  - 'S' for Streaming

The goal of the project is to distribute requests efficiently across multiple web servers without overloading or underutilizing the system.

## Main Components

### Request
Represents a web request with random IP addresses and a random processing time.

### Web Server
Processes one request at a time. Each server counts down the remaining time for a request until it is complete.

### Load Balancer
Manages:
- A queue of incoming requests
- A group of web servers
- Distribution of jobs to available servers
- Dynamic scaling (adding or removing servers based on queue size)

### Switch Bonus
Routes requests based on job type:
- Processing jobs go to one load balancer
- Streaming jobs go to another load balancer

## Features

- Random request generation
- Queue-based request handling
- Dynamic server allocation
- IP range blocking (firewall simulation)
- Logging of system activity
- Simulation of multiple clock cycles

## Course

CSCE 412 – Cloud Computing  
Spring 2026  
Anthony Huang