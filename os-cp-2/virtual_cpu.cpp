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
  return original_pcb;
}

VirtualPCB VirtualCPU::get_PCB() {
  return VirtualPCB( pid, burst_time );
}

BURST_TIME VirtualCPU::execute_process( BURST_TIME duration ) {
  while( burst_time > 0 ) {
    -- duration;
    -- burst_time;
    increment_system_clock();
  }
  return duration;
}

SYSTEM_TIME VirtualCPU::increment_system_clock( SYSTEM_TIME duration ) {
  while( duration ) {
    ++ system_time;
  }
  return system_time;
}