#ifndef _process_arrival_simulator
#define _process_arrival_simulator

struct incoming_process
{
  VirtualPCB pcb;
  SYSTEM_TIME arrival_time;
};

class ProcessArrivalSimulator
{
public:
  typedef unsigned size_t;

  ProcessArrivalSimulator();
  virtual ~ProcessArrivalSimulator();

  void    parse_file( const char* filename );
  const   incoming_process& pop_front();
  size_t  size();

private:
  fw_list<incoming_process> processes;
};

#endif // !_process_arrival_simulator
