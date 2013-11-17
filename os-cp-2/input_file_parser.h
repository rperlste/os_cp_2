#ifndef _input_file_parser
#define __input_file_parser

#include <fstream>
#include <sstream>
#include <cstdlib>
#include "virtual_pcb.h"

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

InputFileParser::InputFileParser( const char* filename ) {
  file = new std::fstream( filename );
}

InputFileParser::~InputFileParser() {
  delete file;
}

bool InputFileParser::complete() {
  return file->eof();
}

IncomingProcess InputFileParser::next_process( ) {
  std::stringstream   input_stream;
  std::string         input_line;
  std::string         input_tokens[3];
  unsigned            input_position = 0;

  input_stream << file;
  input_line = input_stream.str();


  for( int i = 0; i < input_line.size(); ++ i ) {
    if( isalnum( input_line[i] ) ) {
      input_tokens[input_position] += input_line[i];
    } else {
      if( input_tokens[input_position].size() > 0 ) {
        ++ input_position;
      }
      if( input_position > 2 ) {
        break;
      }
    }
  }

  IncomingProcess incoming_process;
  incoming_process.pcb = VirtualPCB(  atoi( input_tokens[0].c_str() ), 
                                      atoi( input_tokens[1].c_str() ));
  incoming_process.arrival_time     = atoi( input_tokens[2].c_str( ) );

  return incoming_process;
}


#endif // !_input_file_parser
