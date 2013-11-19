#include "../schedule_strategy/schedule_strategy.h"


void FCFS_Schedule::execute_burst( VirtualCPU& cpu ) {
  if( queue.size() ) {

    if( cpu.burst_time == 0 ) {
      cpu.load_process( pop_front() );
    }
    cpu.execute_process();
  }
}