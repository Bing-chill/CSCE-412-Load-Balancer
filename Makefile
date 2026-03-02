##
# @file Makefile
# @brief Build configuration for the Load Balancer Project.
#
# This Makefile compiles all source files for the Load Balancer
# simulation and links them into a single executable named
# "loadbalancer".
#
# Compilation uses the GNU C++ compiler with C++14 standard
# and enables all compiler warnings.
#
# Targets:
# - all: Builds the loadbalancer executable
# - clean: Removes object files and executable
#
# @author Anthony Huang
# @course CSCE 412 Cloud Computing
# @project Load Balancer Project
# @date 3/1/2026
##

CXX = g++
CXXFLAGS = -std=c++14 -Wall

all: loadbalancer

loadbalancer: main.o request.o webserver.o ipcheck.o Loadbalancer.o Switch.o
	$(CXX) $(CXXFLAGS) -o loadbalancer main.o request.o webserver.o ipcheck.o Loadbalancer.o Switch.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

request.o: request.cpp
	$(CXX) $(CXXFLAGS) -c request.cpp

webserver.o: webserver.cpp
	$(CXX) $(CXXFLAGS) -c webserver.cpp

ipcheck.o: ipcheck.cpp
	$(CXX) $(CXXFLAGS) -c ipcheck.cpp

Loadbalancer.o: Loadbalancer.cpp
	$(CXX) $(CXXFLAGS) -c Loadbalancer.cpp

Switch.o: Switch.cpp
	$(CXX) $(CXXFLAGS) -c Switch.cpp

clean:
	rm -f *.o loadbalancer