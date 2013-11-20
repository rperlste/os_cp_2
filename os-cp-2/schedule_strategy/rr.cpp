#include "../schedule_strategy/schedule_strategy.h"

void RR_Schedule::execute_burst( VirtualCPU& cpu, ScheduleMonitor& monitor ) {

  if( cpu.burst_time == 0 ) {
    cpu.load_process( pop_front() );
    monitor.response( cpu.pid, cpu.system_time );
    remaining_time = time_quanta;
  }

  cpu.execute_process();
  monitor.cpu_burst( cpu.pid );
  if( cpu.pid > 0 && cpu.burst_time == 0 ) {
    monitor.complete( cpu.pid, cpu.system_time );
  }
  remaining_time -= CPU_TICK;
  if( remaining_time == 0 && cpu.burst_time > 0 ) {
    add( cpu.get_PCB() );
    monitor.context_switch( cpu.pid );
    cpu.increment_system_clock( CONTEXT_SWITCH_TIME );
    cpu.pid = 0;
    cpu.burst_time = 0;
  }

}