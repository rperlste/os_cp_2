#include "schedule_monitor.h"

ScheduleMonitor::ScheduleMonitor() {
  context_switches = 0;
}

void ScheduleMonitor::set_type( ScheduleType schedule_type ) {
  this->schedule_type = schedule_type;
}

void ScheduleMonitor::add( const IncomingProcess& incoming_process ) {
  process_list.push_back( ProcessLifetime( incoming_process ) );
}

void ScheduleMonitor::response( PROCESS_ID pid, SYSTEM_TIME time ) {
  for( fw_list<ProcessLifetime>::iterator it = process_list.begin();
       it != process_list.end();
       ++ it ) {
    if( it->data.pcb.pid == pid && it->data.response_time > time-it->data.arrival_time){
      it->data.response_time = time-it->data.arrival_time;
    }
  }
}

void ScheduleMonitor::context_switch( PROCESS_ID pid ) {
  for( fw_list<ProcessLifetime>::iterator it = process_list.begin();
       it != process_list.end();
       ++ it ) {
    if( it->data.pcb.pid == pid ) {
      it->data.context_switches ++;
      context_switches ++;
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

std::string ScheduleMonitor::print_results() {
  std::string ScheduleTypeValues[3] = {
    "First Come First Serve",
    "Shortest Remaining Time First",
    "Round Robin"
  };

  std::stringstream ss;
  ss << "*******************************************************************************\n";
  if( schedule_type == RR ) {
    ss << "**** Scheduling Algorithm: " << ScheduleTypeValues[schedule_type] << " Time Quanta: " 
	  << time_quanta << "\n";
  } else {
    ss << "**** Scheduling Algorithm: " << ScheduleTypeValues[schedule_type] << "\n";
  }
  ss << "**** Number of tasks: " << process_list.size() << "\n";
  ss << "*******************************************************************************\n";
  ss << "PID     Arrival       CPU     Finish    Waiting       Turn   Response   Context\n";
  ss << "           Time     Burst       Time       Time     Around       Time  Switches\n";
  ss << "                                                      Time                     \n";
  ss << "-------------------------------------------------------------------------------\n";
  for( fw_list<ProcessLifetime>::iterator it = process_list.begin();
       it != process_list.end();
       ++ it ) {
    ss << std::setw( 3 ) << it->data.pcb.pid;
    ss << std::setw( 11 ) << float( it->data.arrival_time )      /MILLISECOND;
    ss << std::setw( 11 ) << float( it->data.pcb.burst_time )    /MILLISECOND;
    ss << std::setw( 11 ) << float( it->data.completion_time )    /MILLISECOND;
    ss << std::setw( 11 ) << float( waiting_time( it->data ) )    /MILLISECOND;
    ss << std::setw( 11 ) << float( turnaround_time( it->data ) ) /MILLISECOND;
    ss << std::setw( 11 ) << float( it->data.response_time )      /MILLISECOND;
    ss << std::setw( 10 ) << it->data.context_switches;
    ss << "\n";
  }
  ss << "\n";
  ss << "Average actual CPU burst time = " << cpu_burst_average() << "\n";
  ss << "Average CPU burst time needed = " << process_burst_average() << "\n";
  ss << "Average waiting time = " << waiting_time_average() << "\n";
  ss << "Average turnaround time = " << turnaround_time_average() << "\n";
  ss << "Average response time = " << response_time_average() << "\n";
  ss << "Average context switches = " << context_switches << "\n";
  std::cout << ss.str();
  return ss.str();
}

SYSTEM_TIME ScheduleMonitor::waiting_time( ProcessLifetime lifetime ) {
  SYSTEM_TIME time = lifetime.completion_time - lifetime.arrival_time - lifetime.pcb.burst_time;
  waiting_times.push_back( time );
  return time;
}

SYSTEM_TIME ScheduleMonitor::turnaround_time( ProcessLifetime lifetime ) {
  SYSTEM_TIME time = lifetime.completion_time - lifetime.arrival_time;
  turnaround_times.push_back( time );
  return time;
}

void ScheduleMonitor::cpu_burst( PROCESS_ID pid ) {
  if( cpu_burst_times.size() ) {
    if( cpu_burst_times.front().pid == pid ) {
      cpu_burst_times.front().burst_time += CPU_TICK;
    } else {
      cpu_burst_times.push_front( VirtualPCB( pid, CPU_TICK ) );
    }
  } else {
    cpu_burst_times.push_front( VirtualPCB( pid, CPU_TICK ) );
  }
}

float ScheduleMonitor::cpu_burst_average() {
  SYSTEM_TIME total = 0;
  for( fw_list<VirtualPCB>::iterator it = cpu_burst_times.begin();
       it != cpu_burst_times.end();
       ++ it ) {
    total += it->data.burst_time;
  }
  return float( total )/(cpu_burst_times.size( )*MILLISECOND);
}

float ScheduleMonitor::waiting_time_average() {
  SYSTEM_TIME total = 0;
  for( fw_list<SYSTEM_TIME>::iterator it = waiting_times.begin();
       it != waiting_times.end( );
       ++ it ) {
    total += it->data;
  }
  return float( total )/(waiting_times.size( )*MILLISECOND);
}

float ScheduleMonitor::turnaround_time_average() {
  SYSTEM_TIME total = 0;
  for( fw_list<SYSTEM_TIME>::iterator it = turnaround_times.begin();
       it != turnaround_times.end( );
       ++ it ) {
    total += it->data;
  }
  return float( total )/(turnaround_times.size( )*MILLISECOND);
}

float ScheduleMonitor::response_time_average() {
  SYSTEM_TIME total = 0;
  for( fw_list<ProcessLifetime>::iterator it = process_list.begin();
       it != process_list.end( );
       ++ it ) {
    total += it->data.response_time;
  }
  return float( total )/( process_list.size( )*MILLISECOND );
}

float ScheduleMonitor::process_burst_average() {
  SYSTEM_TIME total = 0;
  for( fw_list<ProcessLifetime>::iterator it = process_list.begin();
       it != process_list.end();
       ++ it ) {
    total += it->data.pcb.burst_time;
  }
  return float( total )/( process_list.size()*MILLISECOND );
}

void ScheduleMonitor::set_quanta( SYSTEM_TIME quanta ){
  time_quanta = quanta;
}