README

Robert Perlstein
101130094
Fall 2013
Operating Systems
Lab 2 -  CPU Scheduling Algorithms

This is a CPU Scheduler Simulator, which can utilize First Come First Serve, 
Round Robin, and Shortest Remaining Time First scheduling algorithms.

Install:  
Extract the .tar file, "cd os-cp-2" and execute the command "make" in the working
directory. 

Execution: 
The program requires atleast 2 arguments, and when utilizing
Round Robin it is suggested to include a time quanta ( where "1"=1ms ).

To run enter "./lab2 input_file algorithm_id time_quanta", where "input_file"
is the filename for the input, "algorithm_id" is the identifier for the
algorithm to be used, and "time_quanta" is the execution period for a
Round Robin scheduling algorithm.

Algorithm IDs:
  0 - First Come First Serve
  1 - Shortest Remaining Time First
  2 - Round Robin
  
Sample execution -> "./lab2 input10.txt 0"
                 -> "./lab2 input100.txt 1"
				 -> "./lab2 input1000.txt 2 2"
				 
Notes:
This program was developed using common design patterns, specifically the 
Strategy pattern for setting the algorithm type, and the Factory pattern
for building scheduling algorithms. It was built as modular as posible
to ensure extension will be easy and that seperation of concepts occurs.

The CPU has a clock tick of 0.5ms, which is represented as 50 in the system.

There is a CPU class and a struct for PCBs. When a PCB is loaded into the CPU
it is removed from the ready queue. Only algorithms that allow preemption
will return a PCB to the ready queue.

The queue is managed using a list I have created with iterators, which in 
retrospect was a poor choice in some regards, specifically for sorting SRTF PCBs.

There is also a test suite available for use with Visual Studio, which can
be found at https://github.com/rperlste/os_cp_2/tree/master/UnitTest.

