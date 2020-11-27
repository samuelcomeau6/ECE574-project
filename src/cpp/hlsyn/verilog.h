#ifndef VERILOG_H
#define VERILOG_H
    #include <string>
    #include "hlsm.h"

    void print_verilog(std::string output_filename, Hlsm * h);
    std::string parse_module_name(std::string filename);
    std::string print_inputs(Hlsm * h);
    std::string print_outputs(Hlsm * h);
    std::string print_modules(Hlsm * h);
    std::string node_to_V(node_t node);
    std::string type_to_V(comp_t comp);
    std::string sign_extend(edge_t * edge, int datawidth, bool is_signed);
    std::string print_wires(Hlsm *h);
    void print_verilog(std::string output_filename, Hlsm * h);
    std::string print_vars(Hlsm *h);
    std::string print_assignment(Hlsm *h);
    std::string print_states(Hlsm * h);
    std::string print_state_def(Hlsm * h);


#endif
