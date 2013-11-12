#ifndef _scheduling_strategy
#define _scheduling_strategy

#include "virtual_pcb.h"
#include "virtual_cpu.h"
#include "list/list.h"

class ScheduleStrategy
{
public:
  typedef unsigned        size_t;
  size_t                  size();
  VirtualPCB              front();
  void                    pop_front();
  virtual void            add( const VirtualPCB& ) = 0;
  virtual SYSTEM_TIME     execute_burst() = 0;

protected:
  fw_list<VirtualPCB>     queue;
  VirtualCPU              cpu;
};

typedef ScheduleStrategy* ( __stdcall *CreateSchedule )( void );

class FCFS_Schedule : public ScheduleStrategy
{
public:
  void            add( const VirtualPCB& );
  SYSTEM_TIME     execute_burst();

  static ScheduleStrategy* __stdcall create() { return new FCFS_Schedule(); }
};

class RR_Schedule : public ScheduleStrategy
{
public:
  // Defaults to millisecond time_quanta defaults, must override manually! 
  RR_Schedule(){
    time_quanta = MILLISECOND;
  }
  void            add( const VirtualPCB& );
  SYSTEM_TIME     execute_burst();

  SYSTEM_TIME     time_quanta;


  static ScheduleStrategy* __stdcall create() { return new RR_Schedule(); }
};

class SRTF_Schedule : public ScheduleStrategy
{
public:
  void            add( const VirtualPCB& );
  void            sort();
  SYSTEM_TIME     execute_burst();

  static ScheduleStrategy* __stdcall create() { return new SRTF_Schedule(); }
};

#endif