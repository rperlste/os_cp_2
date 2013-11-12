#include "../schedule_strategy.h"

void FCFS_Schedule::add( const VirtualPCB& pcb ){
  queue.push_back( pcb );
  return;
}

SYSTEM_TIME FCFS_Schedule::execute_burst(){
  if( queue.size() ){

    VirtualPCB pcb = queue.front();
    queue.pop_front();

    cpu.load_process( pcb );
    return cpu.execute_process( 0 );

  } else {
    return 0;
  }
}