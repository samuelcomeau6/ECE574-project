#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>

#include "verilog.h"
#include "v_template.h"

void print_verilog(std::string output_filename){
    std::ofstream outfile(output_filename, std::ios::out);
    outfile << header;
    outgile << "module " << parse_module_name(output_filename) << "(" << std::endl;
//    outfile << print_inputs(h);
//    outfile << print_outputs(h);
//    outfile << ");" << std::endl;
//    outfile << print_wires(h);
//    outfile << print_regs(h);
//    outfile << print_modules(h);
//    outfile << print_states(h);
//    outfile << "endmodule" << std::endl;
//    outfile << footer;
}
std::string parse_module_name(std::string filename){
    std::regex path_regex("^\\.?.*?(.*?)\\..*$",
                           std::regex_constants::ECMAScript);
    std::smatch matches;
    std::regex_search(filename, matches, path_regex);

    return matches[1];
}
