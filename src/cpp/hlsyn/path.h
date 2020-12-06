#ifndef PATH_H
#define PATH_H
#include <string>
#include <vector>
#include "graph.h"
#include "hlsm.h"
/** @file
*/
/** @brief Calls add_node() after a variable has been parsed
*/
void add_data(comp_t component_type, std::string name, int data_width, bool is_signed, Graph * list);
/** @brief Adds an if construct after if has been parsed (not implemented)
*/
int add_if(std::string condition, Hlsm * sm);
/** @brief Calls add_node() after an operation has been parsed
*/
node_t * add_op(comp_t component_type, std::string input1_name, std::string input2_name, std::string output_name, Graph * list);
/** @brief Calls add_node() after a MUX has been parsed
*/
void add_mux(std::string select_name, std::string is_true, std::string is_false, std::string output_name, Graph * list);
/** @brief Calls add_node() after a REG has been parsed
*/
void add_assignment(std::string left, std::string right, Graph * list);
/** @brief --Not Used--
*/
void free_list(Graph * list);
#endif