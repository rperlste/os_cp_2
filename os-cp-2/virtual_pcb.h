#include "simulation_macros.h"

#ifndef _virtual_pcb
#define _virtual_pcb

class VirtualPCB
{
public:
  PROCESS_ID pid;
  BURST_TIME burst_time;

  VirtualPCB( PROCESS_ID pid, BURST_TIME burst_time ) :pid( pid ), burst_time( burst_time ) {};

  inline bool operator == ( const VirtualPCB& right_side ) const {
    return ( this->pid == right_side.pid && this->burst_time == right_side.burst_time );
  }

};

#endif