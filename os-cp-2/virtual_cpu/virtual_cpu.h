#include "../schedule_simulator/simulation_macros.h"
#include "virtual_pcb.h"

#ifndef _virtual_cpu
#define _virtual_cpu

class VirtualCPU
{
public:
  SYSTEM_TIME   system_time;
  PROCESS_ID    pid;
  SYSTEM_TIME   burst_time;

  VirtualCPU();
  VirtualCPU( const VirtualPCB& pcb, SYSTEM_TIME system_time = 0 );
  virtual ~VirtualCPU() {}


  VirtualPCB    get_PCB();
  // Returns PCB of last process
  VirtualPCB    load_process( const VirtualPCB& pcb );
  // Returns duration process executes for
  SYSTEM_TIME   execute_process( SYSTEM_TIME duration = CPU_TICK );
  // Returns current system time
  SYSTEM_TIME   increment_system_clock( SYSTEM_TIME duration = CPU_TICK );

};



#endif