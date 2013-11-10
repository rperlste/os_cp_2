#ifndef _virtual_cpu
#define _virtual_cpu

class VirtualCPU
{
public:
  VirtualCPU();
  ~VirtualCPU();

  unsigned get_system_time();
  unsigned get_pid();

private:
  unsigned system_time;
  unsigned pid;
};

#endif