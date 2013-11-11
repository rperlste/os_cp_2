#ifndef _schedule_factory
#define _schedule_factory

#include "simulation_macros.h"
#include "scheduling_strategy.h"

struct factory_map_node
{
  ScheduleType schedule_type;
  CreateSchedule create_func;

  factory_map_node( ScheduleType schedule_type, CreateSchedule create_func ) {
    this->schedule_type = schedule_type;
    this->create_func = create_func;
  }

};

class ScheduleFactory
{
private:
  ScheduleFactory() {
    Register( ScheduleType( 0 ), &FCFS_Schedule::create );
    Register( ScheduleType( 1 ), &SRTF_Schedule::create );
    Register( ScheduleType( 2 ), &RR_Schedule::create );
  }
  ScheduleFactory( const ScheduleFactory& ) {}
  ScheduleFactory& operator = ( const ScheduleFactory& ) { return *this; }

  // TODO use a real map!!!
  typedef fw_list<factory_map_node> ScheduleMap;
  ScheduleMap schedule_map;

public:
  ~ScheduleFactory() { schedule_map.clear(); }

  static ScheduleFactory* INSTANCE() {
    static ScheduleFactory factory;
    return &factory;
  }

  void Register( ScheduleType schedule_type, CreateSchedule create_func ) {
    schedule_map.push_front( factory_map_node( schedule_type, create_func ) );
  }

  SchedulingStrategy* CreateSchedule( const ScheduleType& schedule_type ) {
    ScheduleMap::iterator it = schedule_map.begin();
    while( it != schedule_map.end() ) {
      if( it->data.schedule_type == schedule_type ) {
        return it->data.create_func();
      }
      ++ it;
    }
    return NULL;
  }

};

#endif