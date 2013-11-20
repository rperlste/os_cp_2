#include "../schedule_strategy/schedule_strategy.h"

void SRTF_Schedule::add( const VirtualPCB& pcb ) {
  ScheduleStrategy::add( pcb );
  sort();
  return;
}

void SRTF_Schedule::execute_burst( VirtualCPU& cpu, ScheduleMonitor& monitor ) {
  if( cpu.burst_time == 0 ) {
    cpu.load_process( pop_front() );
    monitor.response( cpu.pid, cpu.system_time );
  } else if( size() && cpu.burst_time > queue.front().burst_time ) {
    add( cpu.get_PCB() );
    monitor.context_switch( cpu.pid );
    cpu.load_process( pop_front() );
    monitor.response( cpu.pid, cpu.system_time );
  }

  cpu.execute_process();
  monitor.cpu_burst( cpu.pid );
  if( cpu.pid > 0 && cpu.burst_time == 0 ) {
    monitor.complete( cpu.pid, cpu.system_time );
  }
}

void SRTF_Schedule::sort() {
  queue.sort();
  return;
}