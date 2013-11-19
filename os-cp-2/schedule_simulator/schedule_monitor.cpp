#include "schedule_monitor.h"

void ScheduleMonitor::add( const IncomingProcess& incoming_process ) {
  process_list.push_back( ProcessLifetime( incoming_process ) );
}

void ScheduleMonitor::response( PROCESS_ID pid, SYSTEM_TIME time ) {
  for( fw_list<ProcessLifetime>::iterator it = process_list.begin();
       it != process_list.end();
       ++ it ) {
    if( it->data.pcb.pid == pid ) {
      it->data.response_time = time;
    }
  }
}

void ScheduleMonitor::context_switch( PROCESS_ID pid ) {
  for( fw_list<ProcessLifetime>::iterator it = process_list.begin();
       it != process_list.end();
       ++ it ) {
    if( it->data.pcb.pid == pid ) {
      it->data.context_switches ++;
    }
  }
}

void ScheduleMonitor::complete( PROCESS_ID pid, SYSTEM_TIME time ) {
  for( fw_list<ProcessLifetime>::iterator it = process_list.begin();
       it != process_list.end();
       ++ it ) {
    if( it->data.pcb.pid == pid ) {
      it->data.completion_time = time;
    }
  }
}

void ScheduleMonitor::print_results() {
  return;
}