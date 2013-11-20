#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>

#include "virtual_cpu/virtual_cpu.cpp"
#include "schedule_strategy/schedule_factory.h"
#include "schedule_strategy/schedule.cpp"
#include "schedule_strategy/rr.cpp"
#include "schedule_strategy/fcfs.cpp"
#include "schedule_strategy/srtf.cpp"
#include "schedule_simulator/input_file_parser.cpp"
#include "schedule_simulator/process_arrival_simulator.cpp"
#include "schedule_simulator/schedule_simulator.cpp"
#include "schedule_simulator/schedule_monitor.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
  TEST_CLASS( TEST1_VirtualPCB ) {
public:

  TEST_METHOD( construct_VirtualPCB ) {
    PROCESS_ID pid = 1;
    SYSTEM_TIME burst_time = 2;
    VirtualPCB pcb( pid, burst_time );
    Assert::AreEqual( pid, pcb.pid );
    Assert::AreEqual( burst_time, pcb.burst_time );
  }

  };

  TEST_CLASS( TEST2_VirtualCPU ) {
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
    Assert::AreEqual( (SYSTEM_TIME) 50, t );
    t = cpu.increment_system_clock( 400 );
    Assert::AreEqual( (SYSTEM_TIME) 450, t );
  }

  TEST_METHOD( execute_process ) {
    PROCESS_ID pid = 1;
    SYSTEM_TIME burst_time = 1000;

    VirtualPCB pcb( pid, burst_time );
    VirtualCPU cpu;
    cpu.load_process( pcb );

    // Execute for 1 ms
    SYSTEM_TIME duration = cpu.execute_process( 100 );
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
    PROCESS_ID pid = 1;
    SYSTEM_TIME burst_time = 1000;

    VirtualPCB pcb( pid, burst_time );
    VirtualCPU cpu;
    cpu.load_process( pcb );

    // Execute for 1 ms
    SYSTEM_TIME duration = cpu.execute_process( 100 );
    Assert::AreEqual( (SYSTEM_TIME) 100, cpu.system_time );
    Assert::AreEqual( (SYSTEM_TIME) 100, duration );
    Assert::AreEqual( burst_time - 100, cpu.burst_time );

    // Execute for 5 more ms
    duration = cpu.execute_process( 500 );
    Assert::AreEqual( (SYSTEM_TIME) 600, cpu.system_time );
    Assert::AreEqual( (SYSTEM_TIME) 500, duration );
    Assert::AreEqual( burst_time - 600, cpu.burst_time );

    pid = 2;
    burst_time = 200;
    VirtualPCB pcb2( pid, burst_time );

    pcb = cpu.load_process( pcb2 );
    duration = cpu.execute_process( 500 );
    Assert::AreEqual( (SYSTEM_TIME) 850, cpu.system_time );
    Assert::AreEqual( (SYSTEM_TIME) 200, duration );
    Assert::AreEqual( (SYSTEM_TIME) 0, cpu.burst_time );

    cpu.load_process( pcb );
    duration = cpu.execute_process( 500 );
    Assert::AreEqual( (SYSTEM_TIME) 1250, cpu.system_time );
    Assert::AreEqual( (SYSTEM_TIME) 400, duration );
    Assert::AreEqual( (SYSTEM_TIME) 0, cpu.burst_time );
  }

  };

  TEST_CLASS( TEST3_List ) {

    TEST_METHOD( construction ) {
      fw_list<int> f;
    }

    TEST_METHOD( back ) {
      fw_list<int> f;
      f.push_back( 1 );
      Assert::AreEqual( 1, f.back() );
      f.push_back( 2 );
      Assert::AreEqual( 2, f.back() );
      Assert::AreEqual( 1, f.front() );
      f.pop_back();
      Assert::AreEqual( 1, f.back() );
      f.pop_back();
      Assert::AreEqual( (unsigned) 0, f.size() );
      f.push_back( 1 );
      Assert::AreEqual( 1, f.back() );
      f.push_back( 2 );
      Assert::AreEqual( 2, f.back() );
      Assert::AreEqual( 1, f.front() );
      f.pop_back();
      Assert::AreEqual( 1, f.back() );
      f.pop_back();
      Assert::AreEqual( (unsigned) 0, f.size() );
    }

    TEST_METHOD( front ) {
      fw_list<int> f;
      f.push_front( 1 );
      Assert::AreEqual( 1, f.front() );
      f.push_front( 2 );
      Assert::AreEqual( 2, f.front() );
      Assert::AreEqual( 1, f.back() );
      f.pop_front();
      Assert::AreEqual( 1, f.front() );
      f.pop_front();
      Assert::AreEqual( (unsigned) 0, f.size() );
    }

    TEST_METHOD( iterator ) {
      fw_list<int> f;
      f.push_front( 1 );
      f.push_front( 2 );
      fw_list<int>::iterator it = f.begin();
      Assert::AreEqual( 2, it->data );
      ++ it;
      Assert::AreEqual( 1, it->data );
      ++ it;
      Assert::IsTrue( f.end() == it );
    }

    TEST_METHOD( sort ) {
      fw_list<int> f;
      f.push_front( 1 );
      f.push_front( 2 );
      f.push_front( 1 );
      f.push_front( 5 );
      f.push_front( 1 );
      f.push_front( 4 );
      f.push_front( 1 );
      f.push_front( 100 );
      f.sort();
      fw_list<int>::iterator it = f.begin();
      Assert::AreEqual( 1, it->data );
      ++ it;
      Assert::AreEqual( 1, it->data );
      ++ it;
      Assert::AreEqual( 1, it->data );
      ++ it;
      Assert::AreEqual( 1, it->data );
      ++ it;
      Assert::AreEqual( 2, it->data );
      ++ it;
      Assert::AreEqual( 4, it->data );
      ++ it;
      Assert::AreEqual( 5, it->data );
      ++ it;
      Assert::AreEqual( 100, it->data );
      ++ it;
      Assert::IsTrue( f.end() == it );
    }

    TEST_METHOD( process_lifetime ) {

      fw_list<ProcessLifetime> list;
      list.push_back( IncomingProcess( (SYSTEM_TIME) 1, (SYSTEM_TIME) 100 ) );
      fw_list<ProcessLifetime>::iterator it = list.begin();
      Assert::AreEqual( (SYSTEM_TIME)1, it->data.pcb.pid );
    }
  };

  TEST_CLASS( TEST4_ScheduleStrategy ) {

    TEST_METHOD( construct_FCFS_Schedule ) {
      FCFS_Schedule fcfs;
    }

    TEST_METHOD( construct_RR_Schedule ) {
      RR_Schedule rr;
    }

    TEST_METHOD( construct_SRTF_Schedule ) {
      SRTF_Schedule srtf;
    }

  };

  TEST_CLASS( TEST5_ScheduleFactory ) {

    TEST_METHOD( singleton_constructor ) {
      ScheduleFactory* factory1 = ScheduleFactory::INSTANCE();
      ScheduleFactory* factory2 = ScheduleFactory::INSTANCE();

      Assert::IsTrue( factory1 == factory2 );
    }

    TEST_METHOD( FCFS ) {
      ScheduleFactory* factory = ScheduleFactory::INSTANCE();
      ScheduleStrategy* fcfs = factory->CreateSchedule( ScheduleType::FCFS );
      fcfs->add( VirtualPCB( 1, 100 ) );
      fcfs->pop_front();
    }

    TEST_METHOD( RR ) {
      ScheduleFactory* factory = ScheduleFactory::INSTANCE();
      ScheduleStrategy* rr = factory->CreateSchedule( ScheduleType::RR );
      rr->add( VirtualPCB( 1, 100 ) );
      Assert::AreEqual( (SYSTEM_TIME) 100, rr->time_quanta );
      rr->pop_front();
    }

    TEST_METHOD( SRTF ) {
      ScheduleFactory* factory = ScheduleFactory::INSTANCE();
      ScheduleStrategy* srtf = factory->CreateSchedule( ScheduleType::SRTF );
      srtf->add( VirtualPCB( 1, 100 ) );
      srtf->pop_front();
    }
  };

  TEST_CLASS( TEST6_InputFileParser ) {
    TEST_METHOD( construction ) {
      std::fstream file( "../os-cp-2/input/input10.dat" );
      InputFileParser parser( &file );
    }

    TEST_METHOD( read_file ) {

      std::fstream file( "../os-cp-2/input/input10.dat" );
      InputFileParser parser( &file );

      IncomingProcess ip = parser.next_process();
      Assert::AreEqual( (PROCESS_ID) 1, ip.pcb.pid );
      Assert::AreEqual( (SYSTEM_TIME) 100, ip.pcb.burst_time );
      Assert::AreEqual( (SYSTEM_TIME) 0, ip.arrival_time );

      ip = parser.next_process();
      Assert::AreEqual( (PROCESS_ID) 2, ip.pcb.pid );
      Assert::AreEqual( (SYSTEM_TIME) 700, ip.pcb.burst_time );
      Assert::AreEqual( (SYSTEM_TIME) 200, ip.arrival_time );

      ip = parser.next_process();
      Assert::AreEqual( (PROCESS_ID) 3, ip.pcb.pid );
      Assert::AreEqual( (SYSTEM_TIME) 600, ip.pcb.burst_time );
      Assert::AreEqual( (SYSTEM_TIME) 300, ip.arrival_time );

      // if infinite loop this is broken!
      while( !parser.complete() ) {
        try {
          parser.next_process();
        } catch( std::exception e ) {
          break;
        }
      }
    }
  };

  TEST_CLASS( TEST7_ProcessArrivalSimulator ) {
    TEST_METHOD( construction ) {
      ProcessArrivalSimulator p;
    }

    TEST_METHOD( parse_processes ) {
      ProcessArrivalSimulator parser;
      std::fstream file( "../os-cp-2/input/input10.dat" );
      parser.parse_file( &file );

      IncomingProcess ip = parser.next_process();
      Assert::AreEqual( (PROCESS_ID) 1, ip.pcb.pid );
      Assert::AreEqual( (SYSTEM_TIME) 100, ip.pcb.burst_time );
      Assert::AreEqual( (SYSTEM_TIME) 0, ip.arrival_time );

      ip = parser.next_process();
      Assert::AreEqual( (PROCESS_ID) 2, ip.pcb.pid );
      Assert::AreEqual( (SYSTEM_TIME) 700, ip.pcb.burst_time );
      Assert::AreEqual( (SYSTEM_TIME) 200, ip.arrival_time );

      ip = parser.next_process();
      Assert::AreEqual( (PROCESS_ID) 3, ip.pcb.pid );
      Assert::AreEqual( (SYSTEM_TIME) 600, ip.pcb.burst_time );
      Assert::AreEqual( (SYSTEM_TIME) 300, ip.arrival_time );

      // if infinite loop this is broken!
      while( !parser.size() ) {
        parser.next_process();
      }
    }

    TEST_METHOD( process_ready ) {
      ProcessArrivalSimulator parser;
      std::fstream file( "../os-cp-2/input/input10.dat" );
      parser.parse_file( &file );
      Assert::IsTrue( parser.process_ready( 0 ) );
      parser.next_process();
      Assert::IsFalse( parser.process_ready( 100 ) );
      Assert::IsTrue( parser.process_ready( 200 ) );
      parser.next_process();
      Assert::IsFalse( parser.process_ready( 200 ) );
      Assert::IsFalse( parser.process_ready( 250 ) );
      Assert::IsFalse( parser.process_ready( 299 ) );
      Assert::IsTrue( parser.process_ready( 300 ) );
      parser.next_process();
      Assert::IsFalse( parser.process_ready( 299 ) );
      Assert::IsFalse( parser.process_ready( 300 ) );
      Assert::IsFalse( parser.process_ready( 301 ) );
      Assert::IsTrue( parser.process_ready( 10000 ) );
      while( parser.size() ) {
        parser.next_process();
      }
      Assert::IsFalse( parser.process_ready( 100000000 ) );
    }
  };

  TEST_CLASS( TEST8_SIMULATOR ) {
    TEST_METHOD( construction_FCFS ) {
      std::fstream file( "../os-cp-2/input/input10.dat" );
      ScheduleSimulator s( &file, ScheduleType::FCFS );
    }

    TEST_METHOD( run_FCFS ) {
      std::fstream file( "../os-cp-2/input/input10.dat" );
      ScheduleSimulator s( &file, ScheduleType::FCFS );
      s.run();
      Logger::WriteMessage( s.print_results().c_str() );
    }

    TEST_METHOD( run_RR ) {
      std::fstream file( "../os-cp-2/input/input10.dat" );
      ScheduleSimulator s( &file, ScheduleType::RR, 2 );
      s.run();
    }

    TEST_METHOD( construction_RR ) {
      std::fstream file( "../os-cp-2/input/input10.dat" );
      ScheduleSimulator s( &file, ScheduleType::RR, 1000 );
    }

    TEST_METHOD( construction_SRTF ) {
      std::fstream file( "../os-cp-2/input/input10.dat" );
      ScheduleSimulator s( &file, ScheduleType::SRTF );
    }
  };

  TEST_CLASS( TEST9_MONITOR ) {

  };

  TEST_CLASS( TEST10_IMPLEMENTATION ) {

  };
}