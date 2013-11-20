#ifndef _schedule_simulator
#define _schedule_simulator

#include "simulation_macros.h"
#include "../schedule_strategy/schedule_factory.h"
#include "process_arrival_simulator.h"
#include "../virtual_cpu/virtual_cpu.h"
#include "schedule_monitor.h"

// Simulates processes running through a CPU scheduling algorithm
class ScheduleSimulator
{
public:
  ScheduleSimulator( std::fstream* file,
                     ScheduleType schedule_type,
                     TIME_QUANTA time_quanta = MILLISECOND );
  virtual ~ScheduleSimulator();

  void                      run();
  std::string               print_results();

private:
  ProcessArrivalSimulator   proccess_arrival_simulator;
  ScheduleStrategy*         scheduler;
  ScheduleFactory*          schedule_factory;
  VirtualCPU                cpu;
  ScheduleMonitor           monitor;

  void                      execute_burst();
};

#endif