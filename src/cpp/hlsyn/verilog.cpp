#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>

#include "verilog.h"
#include "v_template.h"
#include "hlsm.h"

void print_verilog(std::string output_filename, Hlsm * h){
    std::ofstream outfile(output_filename, std::ios::out);
    outfile << header;
    outfile << "module " << parse_module_name(output_filename) << "(" << std::endl;
    outfile << print_inputs(h);
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
std::string print_inputs(Hlsm * h){
    std::string out="\tinput clk,\n\tinput rst,\n";
    std::cout << h->graph.scheduled_graph_toString();
    for(int i=0;i<h->graph.nodes.size();++i){
        node_t * node = h->graph.nodes[i];
        std::cout << node->name;
        if(node->type == INPUT){
            out = out + "\tinput ";
            if(node->width > 1){
                if(node->is_signed) out = out + "signed ";
                out = out + "[" + std::to_string(node->width - 1);
                out = out + ":0] " + node->name + ",\n";
            }
        }
    }
    return out;
}