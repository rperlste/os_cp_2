#include "../schedule_strategy/schedule_strategy.h"

void RR_Schedule::execute_burst( VirtualCPU& cpu ) {
  if( queue.size() ) {

    VirtualPCB pcb( pop_front() );

    // TODO remove passing copies, use references
    cpu.load_process( pcb );
    SYSTEM_TIME burst_duration = cpu.execute_process( time_quanta );
    if( cpu.burst_time > 0 ) {
      add( cpu.get_PCB() );
    }
  }
}