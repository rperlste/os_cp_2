#include "../schedule_strategy/schedule_strategy.h"


void FCFS_Schedule::execute_burst( VirtualCPU& cpu, ScheduleMonitor& monitor ) {
  if( cpu.burst_time == 0 ) {
    cpu.load_process( pop_front() );
    monitor.response( cpu.pid, cpu.system_time );
  }
  cpu.execute_process();
  monitor.cpu_burst( cpu.pid );
  if( cpu.pid > 0 && cpu.burst_time == 0 ) {
    monitor.complete( cpu.pid, cpu.system_time );
  }
}