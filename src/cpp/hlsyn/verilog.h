#ifndef VERILOG_H
#define VERILOG_H
/** @file
*/
#include <string>
#include "hlsm.h"

/** @brief Prints verilog to file
*/
void print_verilog(std::string output_filename, Hlsm * h);
/** @brief Parses the module name from the output file name --not used
*/
std::string parse_module_name(std::string filename);
/** @brief Returns verilog implementation of all input types
*/
std::string print_inputs(Hlsm * h);
/** @brief Returns verilog implementation of all output types
*/
std::string print_outputs(Hlsm * h);
/** @brief Returns verilog implementation of all modules
*/
std::string print_modules(Hlsm * h);
/** @brief Converts a node to verilog implementation
*/
std::string node_to_V(node_t node);
/** @brief Converts a comp_t to verilog implementation
*/
std::string type_to_V(comp_t comp);
/** @brief Sign extends an input or output
*/
std::string sign_extend(edge_t * edge, int datawidth, bool is_signed);
/** @brief Returns verilog implementation of all wires
*/
std::string print_wires(Hlsm *h);
/** @brief Returns verilog implementation of all reg varibles
*/
std::string print_vars(Hlsm *h);
/** @brief Returns verilog implementation of ??
*/
std::string print_assignment(Hlsm *h);
/** @brief Returns verilog implemntation of HLSM states
*/
std::string print_states(Hlsm * h);
/** @brief Returns a human readable verilog param list for HLSM state definitions
*/
std::string print_state_def(Hlsm * h);


#endif
