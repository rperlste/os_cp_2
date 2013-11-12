#include "../schedule_strategy.h"

VirtualPCB ScheduleStrategy::front(){
  try {
    return VirtualPCB( queue.front() );
  } catch ( std::exception e ){
    return VirtualPCB();
  }
}

ScheduleStrategy::size_t ScheduleStrategy::size(){
  return queue.size();
}

void ScheduleStrategy::pop_front(){
  queue.pop_front();
  return;
}