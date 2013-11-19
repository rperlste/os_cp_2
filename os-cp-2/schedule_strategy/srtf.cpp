#include "../schedule_strategy/schedule_strategy.h"

void SRTF_Schedule::add( const VirtualPCB& pcb ) {
  ScheduleStrategy::add( pcb );
  sort();
  return;
}

void SRTF_Schedule::execute_burst( VirtualCPU& cpu ) {
  if( queue.size() ) {

    cpu.load_process( front() );
    SYSTEM_TIME burst_duration = 0;
    while( cpu.get_PCB().burst_time > 0 &&  cpu.get_PCB().pid == front().pid ) {
      burst_duration += cpu.execute_process( CPU_TICK );
      sort();
    }
    if( cpu.get_PCB().burst_time == 0 ) {
      pop_front();
    }

  }
}

void SRTF_Schedule::sort() {
  return;
}