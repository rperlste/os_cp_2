#include "process_arrival_simulator.h"

void ProcessArrivalSimulator::parse_file( const char* filename ) {
  InputFileParser parser( filename );
  while( !parser.complete() ) {
    processes.push_back( parser.next_process() );
  }
  return;
}

bool ProcessArrivalSimulator::process_ready( SYSTEM_TIME system_time ) {
  return processes.front().arrival_time <= system_time;
}

IncomingProcess ProcessArrivalSimulator::next_process() {
  IncomingProcess incoming_process( processes.front() );
  processes.pop_front();
  return incoming_process;
}

ProcessArrivalSimulator::size_t ProcessArrivalSimulator::size() {
  return processes.size();
}