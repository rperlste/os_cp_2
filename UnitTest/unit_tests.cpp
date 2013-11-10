#include "stdafx.h"
#include "CppUnitTest.h"

#include "virtual_cpu.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
  TEST_CLASS( test_VirtualPCB )
	{
	public:

		TEST_METHOD( construct_VirtualPCB )
		{
      PROCESS_ID pid = 1;
      BURST_TIME burst_time = 2;
      VirtualPCB pcb( pid, burst_time );
      Assert::AreEqual( pid, pcb.pid );
      Assert::AreEqual( burst_time, pcb.burst_time );
		}

	};

  TEST_CLASS( test_VirtualCPU ) {
  public:
    
    TEST_METHOD( construction ) {
      PROCESS_ID pid = 0;
      BURST_TIME burst_time = 0;
      SYSTEM_TIME system_time = 0;

      VirtualCPU cpu;
      Assert::AreEqual( pid, cpu.pid );
      Assert::AreEqual( burst_time, cpu.burst_time );
      Assert::AreEqual( system_time, cpu.system_time );

      pid = 5;
      burst_time = 8;
      system_time = 0;

      VirtualPCB pcb1( pid, burst_time );
      VirtualCPU cpu3( pcb1 );
      Assert::AreEqual( pid, cpu3.pid );
      Assert::AreEqual( burst_time, cpu3.burst_time );
      Assert::AreEqual( system_time, cpu3.system_time );

      pid = 5;
      burst_time = 8;
      system_time = 5;

      VirtualPCB pcb2( pid, burst_time );
      VirtualCPU cpu4( pcb2, system_time );
      Assert::AreEqual( pid, cpu4.pid );
      Assert::AreEqual( burst_time, cpu4.burst_time );
      Assert::AreEqual( system_time, cpu4.system_time );
    }

    TEST_METHOD( get_PCB ) {
      PROCESS_ID pid = 1;
      BURST_TIME burst_time = 10;

      VirtualPCB pcb( pid, burst_time );
      VirtualCPU cpu( pcb );
      VirtualPCB pcb2 = cpu.get_PCB();
      Assert::IsTrue( pcb == pcb2 );
    }

    TEST_METHOD( load_process ) {
      PROCESS_ID pid = 1;
      BURST_TIME burst_time = 10;

      VirtualPCB pcb( pid, burst_time );
      VirtualCPU cpu;
      cpu.load_process( pcb );
      Assert::AreEqual( pid, cpu.pid );
      Assert::AreEqual( burst_time, cpu.burst_time );


      pid = 2;
      burst_time = 5;

      VirtualPCB pcb2( pid, burst_time );
      VirtualPCB pcb3 = cpu.load_process( pcb2 );
      Assert::IsTrue( pcb == pcb3 );

    }

    TEST_METHOD( increment_system_clock ) {
      VirtualCPU cpu;
      SYSTEM_TIME t = cpu.increment_system_clock();
      Assert::AreEqual( (SYSTEM_TIME) 1, t );
      t = cpu.increment_system_clock( 4 );
      Assert::AreEqual( (SYSTEM_TIME) 5, t );
    }

    TEST_METHOD( execute_process ) {
      PROCESS_ID pid = 1;
      BURST_TIME burst_time = 10;

      VirtualPCB pcb( pid, burst_time );
      VirtualCPU cpu;
    }

  };
}