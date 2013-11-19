#ifndef _process_arrival_simulator
#define _process_arrival_simulator

#include "../virtual_cpu/virtual_pcb.h"
#include "../list/list.h"
#include "input_file_parser.h"

// Simulates the arrival of processes at CPU clock times
class ProcessArrivalSimulator
{
public:
  typedef unsigned size_t;

  void                      parse_file( std::fstream* file );
  bool                      process_ready( SYSTEM_TIME );
  IncomingProcess           next_process();
  size_t                    size();

private:
  fw_list<IncomingProcess>  processes;
};

#endif // !_process_arrival_simulator
