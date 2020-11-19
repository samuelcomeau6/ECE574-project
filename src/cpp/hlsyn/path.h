#include <string>
#include <vector>
#include "graph.h"

#ifndef PATH_H
#define PATH_H

node_t * list_search(Graph * list, std::string name);
void add_data(comp_t component_type, std::string name, int data_width, bool is_signed, Graph * list);
void add_op(comp_t component_type, std::string input1_name, std::string input2_name, std::string output_name, Graph * list);
void add_mux(std::string select_name, std::string is_true, std::string is_false, std::string output_name, Graph * list);
void add_assignment(std::string left, std::string right, Graph * list);
void free_list(Graph * list);
#endif