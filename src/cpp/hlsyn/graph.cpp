#include "graph.h"
#include <string>
#include <iostream>

std::string comp_toString(comp_t component) {
    std::string output;

    switch (component) {
    case REG:     output = "REG"; break;
    case ADD:     output = "ADD"; break;
    case SUB:     output = "SUB"; break;
    case MUL:     output = "MUL"; break;
    case COMPLT:  output = "COMPLT"; break;
    case COMPEQ:  output = "COMPEQ"; break;
    case COMPGT:  output = "COMPGT"; break;
    case COMPLTE: output = "COMPLTE"; break;
    case COMPGTE: output = "COMPGTE"; break;
    case MUX2X1:  output = "MUX2x1"; break;
    case SHR:     output = "SHR"; break;
    case SHL:     output = "SHL"; break;
    case DIV:     output = "DIV"; break;
    case MOD:     output = "MOD"; break;
    case INC:     output = "INC"; break;
    case DEC:     output = "DEC"; break;
    case INPUT:   output = "INPUT"; break;
    case OUTPUT:  output = "OUTPUT"; break;
    case WIRE:    output = "WIRE"; break;
    case VAR:    output = "VAR"; break;
    default:      output = "ERROR"; break;
    }
    return output;
}

void Graph::add_node(comp_t component_type, std::string input1_name, std::string input2_name, std::string select, std::string output_name){
    bool is_signed = 0;
    int data_width = 0;

    node_t * temp_obj = new node_t;
    temp_obj->name           = comp_toString(component_type)+std::to_string(this->nodes.size());
    temp_obj->input_1        = edge_search(this, input1_name, false);
    temp_obj->input_2        = edge_search(this, input2_name, false);
    temp_obj->output         = edge_search(this, output_name, true);
    if(component_type == MUX2X1) {temp_obj->select         = edge_search(this, select, false);}
    else {temp_obj->select = NULL;}
    temp_obj->type           = component_type;
    temp_obj->is_signed      = (temp_obj->input_1->is_signed
                               ||temp_obj->input_2->is_signed
                               ||temp_obj->output->is_signed);
    temp_obj->width          = max(temp_obj->input_1->width,
                                  temp_obj->input_1->width,
                                  temp_obj->input_1->width);
    temp_obj->duration       = 0;
	temp_obj->color 		    = "White";
    nodes.push_back(temp_obj);
    if(nodes[nodes.size()-1]->input_1->to == NULL){
        nodes[nodes.size()-1]->input_1->to = nodes[nodes.size()-1];
    }
    if(nodes[nodes.size()-1]->input_2->to == NULL){
        nodes[nodes.size()-1]->input_2->to = nodes[nodes.size()-1];
    }
    if(nodes[nodes.size()-1]->output->from == NULL){
        nodes[nodes.size()-1]->output->from = nodes[nodes.size()-1];
    }
    if(component_type==MUX2X1 && nodes[nodes.size()-1]->select->to == NULL){
        nodes[nodes.size()-1]->select->to = nodes[nodes.size()-1];
    }
}
void Graph::add_edge(comp_t component_type, std::string name, int data_width, bool is_signed){

    edge_t * temp_obj = new edge_t;
    temp_obj->name           = name;
    if(component_type==INPUT) temp_obj->from = &this->inop;
    else temp_obj->from        = NULL;
    if(component_type==OUTPUT) temp_obj->to = &this->onop;
    else temp_obj->to         = NULL;
    temp_obj->type           = component_type;
    temp_obj->is_signed      = is_signed;
    temp_obj->width          = data_width;
	temp_obj->color 		    = "White";

    this->edges.push_back(temp_obj);
}

int max(int a, int b, int c){
    int out=a;
    out = (b>out) ? b : out;
    out = (c>out) ? c : out;
    return out;
}

std::string Graph::graph_toString(void){
    std::string out = "digraph{\n";
    out = out + "inop[label = \"inop\"]\n";
    out = out + "onop[label = \"onop\"]\n";
    for(int i=0;i<this->nodes.size();++i){
         out = out + nodes[i]->name + "[label =\"" + node_toString(*this->nodes[i]) + "\"]\n";
    }
    for(int i=0;i<this->edges.size();++i){
        if(this->edges[i]->from != NULL) out = out + this->edges[i]->from->name;
        out = out + "->";
        if(this->edges[i]->to != NULL) out = out + this->edges[i]->to->name;
        out = out + "[label =\"" + this->edges[i]->name + "\"]\n";
    }
    out = out + "}";
    return out;
}


std::string node_toString(node_t datum){
    std::string out_string = datum.name;
    if(datum.is_signed) out_string = out_string + " S ";
    else out_string = out_string + " U ";
    out_string = out_string + std::to_string(datum.width) + "' ";
    return out_string;
}


std::string edge_toString(edge_t datum){
    std::string out_string = datum.name;
    if(datum.is_signed) out_string = out_string + " signed ";
    else out_string = out_string + " unsigned ";
    out_string = out_string + std::to_string(datum.width) + " bit ";
    out_string = out_string + comp_toString(datum.type);
    out_string = out_string + " From:";
    if(datum.from==NULL) out_string = out_string + "NULL";
    else out_string = out_string + datum.from->name;
    out_string = out_string + " To:";
    if(datum.to==NULL) out_string = out_string + "NULL";
    else out_string = out_string + datum.to->name;
    return out_string;
}
edge_t* edge_search(Graph * list, std::string name,bool is_from){
    for(int i=0;i<=list->edges.size();++i){
        if(list->edges[i]->name == name) {
            if(is_from){
                if(list->edges[i]->from != NULL){
                    fprintf(stderr,"Signal %s is driven from multiple sources",
                            list->edges[i]->name.c_str());
                    exit(EXIT_FAILURE);
                } else {
                    return list->edges[i];
                }
            } else {
                if(list->edges[i]->to!=NULL){
                    list->add_edge(list->edges[i]->type, list->edges[i]->name, list->edges[i]->width, list->edges[i]->is_signed);
                    list->edges[list->edges.size()-1]->from = list->edges[i]->from;
                    return list->edges[list->edges.size()-1];
                } else {
                    return list->edges[i];
                }
            }
        }
    }
    fprintf(stderr,"Failed to locate variable %s\n",
        name.c_str());
    exit(EXIT_FAILURE);
    return NULL;
}
