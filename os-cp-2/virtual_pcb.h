#ifndef _virtual_pcb
#define _virtual_pcb

class VirtualPCB
{
public:
  VirtualPCB( unsigned pid, unsigned burst_time ) :pid( pid ), burst_time( burst_time ) {};
  unsigned pid;
  unsigned burst_time;
};

#endif