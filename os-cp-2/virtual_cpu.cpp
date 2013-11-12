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

VirtualPCB VirtualCPU::load_process( const VirtualPCB& pcb ){
  VirtualPCB original_pcb = get_PCB();
  pid = pcb.pid;
  burst_time = pcb.burst_time;
  if( original_pcb.pid > 0 ) {
    increment_system_clock( CONTEXT_SWITCH_TIME );
  }
  return original_pcb;
}

VirtualPCB VirtualCPU::get_PCB() {
  return VirtualPCB( pid, burst_time );
}

// TODO this is broken for SRTF
SYSTEM_TIME VirtualCPU::execute_process( SYSTEM_TIME duration ) {
  SYSTEM_TIME remaining_duration = 
    (duration >= burst_time) ? duration - burst_time : 0;
  SYSTEM_TIME duration_executed = 
    (duration == 0) ? duration - remaining_duration : burst_time;
  SYSTEM_TIME current_duration = 0;
  while( current_duration < duration_executed ){
    burst_time -= CPU_TICK;
    increment_system_clock( CPU_TICK );
  }

  return duration_executed;
}

SYSTEM_TIME VirtualCPU::increment_system_clock( SYSTEM_TIME duration ) {
  system_time += duration;
  return system_time;
}