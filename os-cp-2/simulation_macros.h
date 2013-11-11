#ifndef _simulation_macros
#define _simulation_macros

#define PROCESS_ID    unsigned
#define SYSTEM_TIME   unsigned
#define TIME_QUANTA   unsigned

#define MILLISECOND         100
#define CONTEXT_SWITCH_TIME 50

enum ScheduleType
{
  FCFS = 0,
  SRTF = 1,
  RR = 2
};

#endif