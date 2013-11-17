#include "../schedule_strategy.h"

SYSTEM_TIME RR_Schedule::execute_burst() {
  if( queue.size() ) {

    VirtualPCB pcb( pop_front() );

    // TODO remove passing copies, use references
    cpu.load_process( pcb );
    SYSTEM_TIME burst_duration = cpu.execute_process( time_quanta );
    pcb = cpu.get_PCB( );
    if( pcb.burst_time != 0 ) {
      add( pcb );
    }
    return burst_duration;

  } else {
    return 0;
  }
}