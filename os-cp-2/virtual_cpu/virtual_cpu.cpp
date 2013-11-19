#include "virtual_cpu.h"

VirtualCPU::VirtualCPU() {
  system_time = 0;
  pid = 0;
  burst_time = 0;
}

VirtualCPU::VirtualCPU( const VirtualPCB& pcb, SYSTEM_TIME system_time ) {
  this->pid = pcb.pid;
  this->burst_time = pcb.burst_time;
  this->system_time = system_time;
}

VirtualPCB VirtualCPU::load_process( const VirtualPCB& pcb ) {
  if( burst_time > 0 ) {
    increment_system_clock( CONTEXT_SWITCH_TIME );
  }

  VirtualPCB original_pcb = get_PCB();
  pid = pcb.pid;
  burst_time = pcb.burst_time;

  return original_pcb;
}

VirtualPCB VirtualCPU::get_PCB() {
  return VirtualPCB( pid, burst_time );
}

// TODO this is broken for SRTF
SYSTEM_TIME VirtualCPU::execute_process( SYSTEM_TIME max_duration ) {
  SYSTEM_TIME executed_duration = 0;
  while( executed_duration < max_duration && burst_time > 0 ) {
    burst_time -= CPU_TICK;
    increment_system_clock( CPU_TICK );
    executed_duration += CPU_TICK;
  }
  return executed_duration;
}

SYSTEM_TIME VirtualCPU::increment_system_clock( SYSTEM_TIME duration ) {
  system_time += duration;
  return system_time;
}