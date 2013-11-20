#ifndef _schedule_monitor
#define _schedule_monitor

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "../schedule_simulator/simulation_macros.h"
#include "../virtual_cpu/virtual_pcb.h"
#include "../list/list.h"

class ScheduleMonitor {
public:
  ScheduleMonitor();
  void              set_type( ScheduleType schedule_type );
  void              set_quanta( SYSTEM_TIME quanta );
  void              add( const IncomingProcess& incoming_process );
  void              response( PROCESS_ID, SYSTEM_TIME );
  void              context_switch( PROCESS_ID );
  void              complete( PROCESS_ID, SYSTEM_TIME );
  void              cpu_burst( PROCESS_ID );
  std::string       print_results();

private:
  fw_list<ProcessLifetime>    process_list;
  fw_list<VirtualPCB>         cpu_burst_times;
  fw_list<SYSTEM_TIME>        waiting_times;
  fw_list<SYSTEM_TIME>        turnaround_times;
  unsigned                    context_switches;
  ScheduleType                schedule_type;
  SYSTEM_TIME                 time_quanta;

  SYSTEM_TIME       turnaround_time( ProcessLifetime lifetime );
  SYSTEM_TIME       waiting_time( ProcessLifetime lifetime );
  float             cpu_burst_average();
  float             process_burst_average();
  float             waiting_time_average();
  float             turnaround_time_average();
  float             response_time_average();

};

#endif