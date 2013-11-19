#include "schedule_simulator.h"


ScheduleSimulator::ScheduleSimulator( std::fstream* file,
                                      ScheduleType schedule_type,
                                      TIME_QUANTA time_quanta /* = MILLISECOND */ ) {
  proccess_arrival_simulator.parse_file( file );
  schedule_factory = ScheduleFactory::INSTANCE();
  scheduler = schedule_factory->CreateSchedule( schedule_type );
  if( schedule_type == ScheduleType::RR ) {
    scheduler->time_quanta = time_quanta;
  }
}

ScheduleSimulator::~ScheduleSimulator() {
  delete scheduler;
  delete schedule_factory;
}

void ScheduleSimulator::run() {
  SYSTEM_TIME idle_duration = 0;
  while( idle_duration < 10000 ) {
    while( proccess_arrival_simulator.process_ready( cpu.system_time ) ) {
      IncomingProcess next_process = proccess_arrival_simulator.next_process();
      monitor.add( next_process );
      scheduler->add( next_process.pcb );
    }
    if( scheduler->size() > 0 ) {
      scheduler->execute_burst( cpu );
      idle_duration = 0;
    } else {
      cpu.increment_system_clock( CPU_TICK );
      idle_duration += CPU_TICK;
    }
  }
}