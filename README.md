Simulation-of-Open-Queueing-Networks-system
===========================================

This program simulates an open queueing network system.  Run simulation until at least 500,000 customers have departed from system.


event.cpp - Functions for inserting and removing Events from EventLists 
event.h - Data structures for Events and EventLists
main.cpp - Main program for simulation
Makefile - Makefile for simulation
rv.cpp - Functions which return uniform and exponential random variables
rv.h - Header file for rv.cpp


Edit Makefile to point to the c++ compiler on the local machine.
To compile, type "make -f Makefile"
To run, type "./sim".
  

