#include "../schedule_simulator/simulation_macros.h"

#ifndef _virtual_pcb
#define _virtual_pcb

class VirtualPCB
{
public:
  PROCESS_ID    pid;
  SYSTEM_TIME   burst_time;

  VirtualPCB( PROCESS_ID pid = 0, SYSTEM_TIME burst_time = 0 )
    :pid( pid ), burst_time( burst_time ) {};

  inline bool operator == ( const VirtualPCB& right_side ) const {
    return ( this->pid == right_side.pid
             && this->burst_time == right_side.burst_time );
  }

  inline bool operator < ( const VirtualPCB& right_side ) const {
    return ( this->burst_time < right_side.burst_time );
  }

};

struct IncomingProcess
{
  IncomingProcess() {}
  IncomingProcess( VirtualPCB pcb, SYSTEM_TIME arrival_time ) :
    pcb( pcb ), arrival_time( arrival_time ) {}
  VirtualPCB    pcb;
  SYSTEM_TIME   arrival_time;

  inline bool operator < ( const IncomingProcess& right_side ) const {
    return ( this->arrival_time < right_side.arrival_time );
  }
};

struct ProcessLifetime
{
  ProcessLifetime() {}
  ProcessLifetime( const IncomingProcess& incoming_process ) {
    pcb = incoming_process.pcb;
    arrival_time = incoming_process.arrival_time;
    completion_time = MAX_SYSTEM_TIME;
    response_time = MAX_SYSTEM_TIME;
    context_switches = 0;
  }
  VirtualPCB    pcb;
  SYSTEM_TIME   arrival_time;
  SYSTEM_TIME   completion_time;
  SYSTEM_TIME   response_time;
  unsigned      context_switches;
};


#endif