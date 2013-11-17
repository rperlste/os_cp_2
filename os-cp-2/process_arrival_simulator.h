#ifndef _process_arrival_simulator
#define _process_arrival_simulator

#include "virtual_pcb.h"
#include "input_file_parser.h"

// Simulates the arrival of processes at CPU clock times
class ProcessArrivalSimulator
{
public:
  typedef unsigned size_t;

  ProcessArrivalSimulator();
  virtual ~ProcessArrivalSimulator();

  void                      parse_file( const char* filename );
  bool                      process_ready( SYSTEM_TIME );
  IncomingProcess           next_process();
  size_t                    size();

private:
  fw_list<IncomingProcess>  processes;
};

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

#endif // !_process_arrival_simulator
