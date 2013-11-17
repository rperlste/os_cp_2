#include "stdafx.h"
#include "CppUnitTest.h"

#include "virtual_cpu.cpp"
#include "schedule_factory.h"
#include "schedule/schedule.cpp"
#include "schedule/fcfs.cpp"
#include "schedule/rr.cpp"
#include "schedule/srtf.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
  TEST_CLASS( test_VirtualPCB )
  {
  public:

    TEST_METHOD( construct_VirtualPCB )
    {
      PROCESS_ID pid = 1;
      SYSTEM_TIME burst_time = 2;
      VirtualPCB pcb( pid, burst_time );
      Assert::AreEqual( pid, pcb.pid );
      Assert::AreEqual( burst_time, pcb.burst_time );
    }

  };

  TEST_CLASS( test_VirtualCPU ) {
  public:
    
    TEST_METHOD( construction ) {
      PROCESS_ID pid = 0;
      SYSTEM_TIME burst_time = 0;
      SYSTEM_TIME system_time = 0;

      VirtualCPU cpu;
      Assert::AreEqual( pid, cpu.pid );
      Assert::AreEqual( burst_time, cpu.burst_time );
      Assert::AreEqual( system_time, cpu.system_time );

      pid = 5;
      burst_time = 800;
      system_time = 0;

      VirtualPCB pcb1( pid, burst_time );
      VirtualCPU cpu3( pcb1 );
      Assert::AreEqual( pid, cpu3.pid );
      Assert::AreEqual( burst_time, cpu3.burst_time );
      Assert::AreEqual( system_time, cpu3.system_time );

      pid = 5;
      burst_time = 800;
      system_time = 500;

      VirtualPCB pcb2( pid, burst_time );
      VirtualCPU cpu4( pcb2, system_time );
      Assert::AreEqual( pid, cpu4.pid );
      Assert::AreEqual( burst_time, cpu4.burst_time );
      Assert::AreEqual( system_time, cpu4.system_time );
    }

    TEST_METHOD( get_PCB ) {
      PROCESS_ID pid = 1;
      SYSTEM_TIME burst_time = 1000;

      VirtualPCB pcb( pid, burst_time );
      VirtualCPU cpu( pcb );
      VirtualPCB pcb2 = cpu.get_PCB();
      Assert::IsTrue( pcb == pcb2 );
    }

    TEST_METHOD( load_process ) {
      PROCESS_ID pid = 1;
      SYSTEM_TIME burst_time = 1000;

      VirtualPCB pcb( pid, burst_time );
      VirtualCPU cpu;
      cpu.load_process( pcb );
      Assert::AreEqual( pid, cpu.pid );
      Assert::AreEqual( burst_time, cpu.burst_time );


      pid = 2;
      burst_time = 500;

      VirtualPCB pcb2( pid, burst_time );
      VirtualPCB pcb3 = cpu.load_process( pcb2 );
      Assert::IsTrue( pcb == pcb3 );

    }

    TEST_METHOD( increment_system_clock ) {
      VirtualCPU cpu;
      SYSTEM_TIME t = cpu.increment_system_clock();
      Assert::AreEqual( (SYSTEM_TIME) 100, t );
      t = cpu.increment_system_clock( 400 );
      Assert::AreEqual( (SYSTEM_TIME) 500, t );
    }

    TEST_METHOD( execute_process ) {
      PROCESS_ID pid = 1;
      SYSTEM_TIME burst_time = 1000;

      VirtualPCB pcb( pid, burst_time );
      VirtualCPU cpu;
      cpu.load_process( pcb );

      // Execute for 1 ms
      SYSTEM_TIME duration = cpu.execute_process();
      Assert::AreEqual( (SYSTEM_TIME) 100, cpu.system_time );
      Assert::AreEqual( (SYSTEM_TIME) 100, duration );
      Assert::AreEqual( burst_time - 100, cpu.burst_time );

      // Execute for 5 more ms
      duration = cpu.execute_process( 500 );
      Assert::AreEqual( (SYSTEM_TIME) 600, cpu.system_time );
      Assert::AreEqual( (SYSTEM_TIME) 500, duration );
      Assert::AreEqual( burst_time - 600, cpu.burst_time );

      // Execute for 5 more ms, should have left over CPU time remaining.
      duration = cpu.execute_process( 500 );
      Assert::AreEqual( (SYSTEM_TIME) 1000, cpu.system_time );
      Assert::AreEqual( (SYSTEM_TIME) 400, duration );
      Assert::AreEqual( burst_time - 1000, cpu.burst_time );
    }

    TEST_METHOD( execute_process_with_context_switching ) {

    }

  };

  TEST_CLASS( TEST_SchedulingStrategy ) {

    TEST_METHOD( construct_FCFS_Schedule ) {
      FCFS_Schedule fcfs;
    }

  };
}