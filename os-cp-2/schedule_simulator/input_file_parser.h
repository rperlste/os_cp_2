#ifndef _input_file_parser
#define _input_file_parser

#include <fstream>
#include <sstream>
#include <cstdlib>
#include "../virtual_cpu/virtual_pcb.h"

class InputFileParser
{
public:
  InputFileParser( const char* filename );
  virtual ~InputFileParser();
  bool complete();
  IncomingProcess next_process();

private:
  std::fstream* file;

};


#endif // !_input_file_parser

