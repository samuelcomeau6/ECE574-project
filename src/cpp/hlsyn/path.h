#include <string>
#include <vector>
#include "graph.h"

#ifndef PATH_H
#define PATH_H

std::string comp_toString(comp_t component);
std::string node_toString(node_t datum);
node_t * list_search(graph_t * list, std::string name);
int max(int a, int b, int c);
void add_data(comp_t component_type, std::string name, int data_width, bool is_signed, graph_t * list);
void add_op(comp_t component_type, std::string input1_name, std::string input2_name, std::string output_name, graph_t * list);
void add_mux(std::string select_name, std::string is_true, std::string is_false, std::string output_name, graph_t * list);
void add_assignment(std::string left, std::string right, graph_t * list);
void free_list(graph_t * list);
#endif