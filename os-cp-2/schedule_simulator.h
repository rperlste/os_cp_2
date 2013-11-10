#ifndef _schedule_simulator
#define _schedule_simulator

#include "scheduling_strategy.h";
#include "schedule_factory.h"

class ScheduleSimulator
{
public:
  ScheduleSimulator();
  virtual ~ScheduleSimulator();

  void run_algorithm( ScheduleType );

private:
  SchedulingStrategy scheduling_strategy;

  void set_scheduling_strategy( ScheduleType );
  void print_
};

#endif