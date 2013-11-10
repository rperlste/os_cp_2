#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
  TEST_CLASS( test_VirtualPCB )
	{
	public:

		TEST_METHOD( construct_VirtualPCB )
		{
      unsigned pid = 1;
      unsigned burst_time = 2;
      VirtualPCB pcb( pid, burst_time );
      Assert::AreEqual( pid, pcb.pid );
      Assert::AreEqual( burst_time, pcb.burst_time );
		}

	};

  TEST_CLASS( test_VirtualCPU ) {
  public:
    
    TEST_METHOD( construct_VirtualCPU ) {

    }
  }
}