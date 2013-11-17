#include "../schedule_strategy.h"

SYSTEM_TIME FCFS_Schedule::execute_burst(){
  if( queue.size() ){

    cpu.load_process( pop_front() );
    return cpu.execute_process( 0 );

  } else {
    return 0;
  }
}