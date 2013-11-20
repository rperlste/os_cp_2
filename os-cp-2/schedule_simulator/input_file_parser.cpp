#include "input_file_parser.h"

InputFileParser::InputFileParser( std::fstream* file ) {
  this->file = file;
}

InputFileParser::~InputFileParser() {}

bool InputFileParser::complete() {
  return file->fail();
}

IncomingProcess InputFileParser::next_process() {
  std::stringstream   input_stream;
  std::string         input_line;
  std::string         input_tokens[3];
  unsigned            input_position = 0;


  std::getline( *file, input_line );

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

  if( input_tokens[0] == "" || input_tokens[1] == "" || input_tokens[2] == "" ) {
    throw std::exception();
  }
  IncomingProcess incoming_process;
  incoming_process.pcb = VirtualPCB( atoi( input_tokens[0].c_str() ),
                                     atoi( input_tokens[2].c_str( ) )*MILLISECOND );
  incoming_process.arrival_time = atoi( input_tokens[1].c_str( ) )*MILLISECOND;

  return incoming_process;
}