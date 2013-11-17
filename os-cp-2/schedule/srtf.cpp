#include "../schedule_strategy.h"

void SRTF_Schedule::add( const VirtualPCB& pcb ) {
  ScheduleStrategy::add( pcb );
  sort();
  return;
}

SYSTEM_TIME SRTF_Schedule::execute_burst( ) {
  if( queue.size() ) {

    cpu.load_process( front() );
    SYSTEM_TIME burst_duration = 0;
    while( cpu.get_PCB().burst_time > 0 &&  cpu.get_PCB( ).pid == front().pid ) {
      burst_duration += cpu.execute_process( MILLISECOND );
      sort();
    }
    if( cpu.get_PCB().burst_time == 0 ) {
      pop_front();
    }

    return burst_duration;

  } else {
    return 0;
  }
}

void SRTF_Schedule::sort( ) {
  return;
}