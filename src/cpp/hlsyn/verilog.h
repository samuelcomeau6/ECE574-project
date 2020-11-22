#ifndef VERILOG_H
#define VERILOG_H
    #include <string>
    #include "hlsm.h"

    void print_verilog(std::string output_filename, Hlsm * h);
    std::string parse_module_name(std::string filename);
    std::string print_inputs(Hlsm * h);

#endif
