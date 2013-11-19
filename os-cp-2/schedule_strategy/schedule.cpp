#include "../schedule_strategy/schedule_strategy.h"

void ScheduleStrategy::add( const VirtualPCB& pcb ) {
  queue.push_back( pcb );
  return;
}


VirtualPCB ScheduleStrategy::front() {
  try {
    return VirtualPCB( queue.front() );
  } catch( std::exception e ) {
    return VirtualPCB();
  }
}


VirtualPCB ScheduleStrategy::pop_front() {
  try {
    VirtualPCB pcb( queue.front() );
    queue.pop_front();
    return pcb;
  } catch( std::exception e ) {
    return VirtualPCB();
  }
}

ScheduleStrategy::size_t ScheduleStrategy::size() {
  return queue.size();
}