#ifndef _scheduling_strategy
#define _scheduling_strategy

#include <exception>
#include "../virtual_cpu/virtual_cpu.h"
#include "../list/list.h"
#include "../schedule_simulator/schedule_monitor.h"

class ScheduleStrategy
{
public:
  ScheduleStrategy() { time_quanta = 0; }
  typedef unsigned        size_t;
  size_t                  size();
  VirtualPCB              front();
  VirtualPCB              pop_front();
  virtual void            add( const VirtualPCB& );
  virtual void            execute_burst( VirtualCPU& ) = 0;

  SYSTEM_TIME             time_quanta;

protected:
  fw_list<VirtualPCB>     queue;
};

typedef ScheduleStrategy* ( __stdcall *CreateSchedule )( void );


/////////////////////////////////////////////////////////////////////////////////
class FCFS_Schedule : public ScheduleStrategy
{
public:
  void     execute_burst( VirtualCPU& cpu );

  static ScheduleStrategy* __stdcall create() { return new FCFS_Schedule(); }
};


/////////////////////////////////////////////////////////////////////////////////
class RR_Schedule : public ScheduleStrategy
{
public:
  RR_Schedule() { time_quanta = MILLISECOND; }
  void     execute_burst( VirtualCPU& cpu );

  SYSTEM_TIME remaining_time;

  static ScheduleStrategy* __stdcall create() { return new RR_Schedule(); }
};


////////////////////////////////////////////////////////////////////////////////
class SRTF_Schedule : public ScheduleStrategy
{
public:
  void            add( const VirtualPCB& );
  void            sort();
  void            execute_burst( VirtualCPU& cpu );

  static ScheduleStrategy* __stdcall create() { return new SRTF_Schedule(); }
};

#endif