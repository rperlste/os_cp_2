#ifndef _scheduling_strategy
#define _scheduling_strategy

#include "virtual_pcb.h"
#include "list/list.h"

class SchedulingStrategy
{
  typedef unsigned size_t;
public:
  size_t              size();
  const VirtualPCB&   front();
  void                pop_front();
  virtual void        add( const VirtualPCB& ) = 0;
  virtual void        sort() = 0;

protected:
  fw_list<VirtualPCB> queue;
};

typedef SchedulingStrategy* ( __stdcall *CreateSchedule )( void );

class FCFS_Schedule : public SchedulingStrategy
{
public:
  void add( const VirtualPCB& );
  void sort();

  static SchedulingStrategy* __stdcall create() { return new FCFS_Schedule(); }
};

class RR_Schedule : public SchedulingStrategy
{
public:
  void add( const VirtualPCB& );
  void sort();

  static SchedulingStrategy* __stdcall create() { return new RR_Schedule(); }
};

class SRTF_Schedule : public SchedulingStrategy
{
public:
  void add( const VirtualPCB& );
  void sort();

  static SchedulingStrategy* __stdcall create() { return new SRTF_Schedule(); }
};

#endif