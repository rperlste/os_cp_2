/*
Author: Robbie Perlstein
SSID:   101130094
Class:  Operating Systems, Fall 2013
Assign: Lab 2 - CPU scheduling algorithm simulator
*/

#include <iostream>
#include <sstream>
#include "schedule_simulator/schedule_simulator.h"

int main( int argc, const char** argv ) {
  if( argc != 4 && argc != 3 ) {
    std::cerr << "\nERROR: Invalid argument count.";
    return 1;
  }

  std::fstream file( argv[1] );
  SYSTEM_TIME time_quanta = ( argc == 4 ) ? atoi( argv[3] ) : MILLISECOND;
  ScheduleSimulator simulator( &file, ScheduleType(atoi(argv[2]) ), time_quanta);
  simulator.run();
  simulator.print_results();


  std::cout << "\n\nPress ENTER to continue...";
  std::cin.ignore();
  return 0;
}