/*
Author: Robbie Perlstein
SSID:   101130094
Class:  Operating Systems, Fall 2013
Assign: Lab 2 - CPU scheduling algorithm simulator
*/

#include <iostream>
#include "schedule_simulator/schedule_simulator.h"

int main( unsigned argc, const char* argv ) {
  if( argc != 2 && argc != 3 ) {
    std::cerr << "\nERROR: Invalid argument count.";
    return 1;
  }
  
  return 0;
}