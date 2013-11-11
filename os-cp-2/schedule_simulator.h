#ifndef _schedule_simulator
#define _schedule_simulator

#include "simulation_macros.h"
#include "scheduling_strategy.h"
#include "schedule_factory.h"
#include "process_arrival_simulator.h"

class ScheduleSimulator
{
public:
  ScheduleSimulator();
  ScheduleSimulator( const char* argv );
  virtual ~ScheduleSimulator();

  void load_input( const char* filename );
  void set_scheduling_strategy( ScheduleType, TIME_QUANTA = MILLISECOND );
  void run_algorithm();

private:
  ProcessArrivalSimulator proccess_arrival_simulator;
  SchedulingStrategy*     scheduler;
  ScheduleFactory*        schedule_factory;
};

#endif