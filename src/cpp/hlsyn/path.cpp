#include <iostream>
#include <cstring>
#include <string>
#include "parse.h"
#include "path.h"
#include "graph.h"
#include "hlsm.h"


void add_data(comp_t component_type, std::string name, int data_width, bool is_signed, Graph * list){

    list->add_edge(component_type, name, data_width, is_signed);

    #ifdef DEBUG
        std::cout << "New data: ";
        std::cout << edge_toString(*list->edges[list->edges.size()-1]) << std::endl;
    #endif

}
int add_if(std::string condition, Hlsm * sm){
    cond_t * temp_obj = new cond_t;
    temp_obj->name = "IF" + std::to_string(sm->conditions.size());
    temp_obj->condition = condition;
    sm->conditions.push_back(*temp_obj);
    return sm->conditions.size()-1;
}
node_t * add_op(comp_t component_type, std::string input1_name, std::string input2_name, std::string output_name, Graph * list){

    node_t * new_node = list->add_node(component_type, input1_name, input2_name, "", output_name);

    #ifdef DEBUG
        std::cout << "New operation: ";
        std::cout << node_toString(*list->nodes[list->nodes.size()-1]) << std::endl;
    #endif
    return new_node;
}
void add_mux(std::string select_name, std::string is_true, std::string is_false, std::string output_name, Graph * list){

    list->add_node(MUX2X1, is_true, is_false, select_name, output_name);

    #ifdef DEBUG
        std::cout << "New mux: ";
        std::cout << node_toString(*list->nodes[list->nodes.size()-1]) << select_name << "?" << std::endl;
    #endif

}
void add_assignment(std::string left, std::string right, Graph * list){

    list->add_node(REG, right, "", "", left);

    #ifdef DEBUG
        std::cout << "New register: ";
        std::cout << node_toString(*list->nodes[list->nodes.size()-1]) << std::endl;
    #endif

}
void free_list(Graph * list){
    for(int i=0;i<list->nodes.size();++i){
    }
    list->nodes.clear();
}
