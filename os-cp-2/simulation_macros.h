#ifndef _simulation_macros
#define _simulation_macros

#define PROCESS_ID    unsigned
#define SYSTEM_TIME   unsigned
#define TIME_QUANTA   unsigned

#define MAX_SYSTEM_TIME     -1
#define MILLISECOND         100
#define CONTEXT_SWITCH_TIME 50
#define CPU_TICK            50

enum ScheduleType
{
  FCFS = 0,
  SRTF = 1,
  RR = 2
};

#endif