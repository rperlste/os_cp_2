#ifndef _schedule_simulator
#define _schedule_simulator

#include "simulation_macros.h"
#include "schedule_strategy.h"
#include "schedule_factory.h"
#include "process_arrival_simulator.h"
#include "virtual_cpu.h"

// Simulates processes running through a CPU scheduling algorithm
class ScheduleSimulator
{
public:
  ScheduleSimulator();
  ScheduleSimulator( const char* argv );
  virtual ~ScheduleSimulator();

  void      load_input( const char* filename );
  void      set_scheduling_strategy( ScheduleType, TIME_QUANTA = MILLISECOND );
  void      run_algorithm();
  void      execute_burst();

private:
  ProcessArrivalSimulator proccess_arrival_simulator;
  ScheduleStrategy*       scheduler;
  ScheduleFactory*        schedule_factory;
  VirtualCPU              cpu;
};

#endif