#ifndef _schedule_factory
#define _schedule_factory

#include "../schedule_simulator/simulation_macros.h"
#include "schedule_strategy.h"

class ScheduleFactory
{
private:
  ScheduleFactory() { }
  ScheduleFactory( const ScheduleFactory& ) {}
  ScheduleFactory& operator = ( const ScheduleFactory& ) { return *this; }

public:
  ~ScheduleFactory() { }

  static ScheduleFactory* INSTANCE() {
    static ScheduleFactory factory;
    return &factory;
  }

  ScheduleStrategy* CreateSchedule( const ScheduleType& schedule_type ) {
    if( schedule_type == FCFS ){
      return new FCFS_Schedule();
	} else if ( schedule_type == RR ){
	  return new RR_Schedule();
	} else if ( schedule_type == SRTF ){
	  return new SRTF_Schedule();
	} else {
		return NULL;
	}
  }

};

#endif