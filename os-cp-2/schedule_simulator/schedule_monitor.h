#ifndef _schedule_monitor
#define _schedule_monitor

#include <iostream>
#include "../schedule_simulator/simulation_macros.h"
#include "../virtual_cpu/virtual_pcb.h"
#include "../list/list.h"

class ScheduleMonitor {
public:
  void      add( const IncomingProcess& incoming_process );
  void      response( PROCESS_ID, SYSTEM_TIME );
  void      context_switch( PROCESS_ID );
  void      complete( PROCESS_ID, SYSTEM_TIME );
  void      print_results();

private:
  fw_list<ProcessLifetime>  process_list;

};

#endif