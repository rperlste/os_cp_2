#include "schedule_simulator.h"


ScheduleSimulator::ScheduleSimulator( std::fstream* file,
                                      ScheduleType schedule_type,
                                      TIME_QUANTA time_quanta /* = MILLISECOND */ ) {
  monitor.set_type( schedule_type );
  proccess_arrival_simulator.parse_file( file );
  schedule_factory = ScheduleFactory::INSTANCE();
  scheduler = schedule_factory->CreateSchedule( schedule_type );
  if( schedule_type == RR ) {
    scheduler->time_quanta = time_quanta*MILLISECOND;
  }
  monitor.set_quanta( time_quanta );
}

ScheduleSimulator::~ScheduleSimulator() {
  delete scheduler;
}

void ScheduleSimulator::run() {
  while( proccess_arrival_simulator.size() || scheduler->size() || cpu.burst_time > 0 ) {
    while( proccess_arrival_simulator.process_ready( cpu.system_time ) ) {
      IncomingProcess next_process = proccess_arrival_simulator.next_process();
      monitor.add( next_process );
      scheduler->add( next_process.pcb );
    }
    if( cpu.burst_time > 0 || scheduler->size() > 0 ) {
      scheduler->execute_burst( cpu, monitor );
    } else {
      cpu.increment_system_clock( CPU_TICK );
    }
  }
}

std::string ScheduleSimulator::print_results() {
  return monitor.print_results();
}