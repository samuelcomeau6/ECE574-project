#include <iostream>
#include <cstring>
#include <string>
#include "parse.h"
#include "path.h"

std::string comp_toString(comp_t component) {
    std::string output;

    switch (component) {
    case REG:     output = "REG"; break;
    case ADD:     output = "ADD"; break;
    case SUB:     output = "SUB"; break;
    case MUL:     output = "MUL"; break;
    case COMPLT:  output = "COMP<"; break;
    case COMPEQ:  output = "COMP=="; break;
    case COMPGT:  output = "COMP>"; break;
    case COMPLTE: output = "COMP<="; break;
    case COMPGTE: output = "COMP>="; break;
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
    default:      output = "ERROR"; break;
    }
    return output;
}


std::string node_toString(data_t datum){
    std::string out_string = datum.name;
    if(datum.is_signed) out_string = out_string + " signed ";
    else out_string = out_string + " unsigned ";
    out_string = out_string + std::to_string(datum.width) + " bit ";
    out_string = out_string + comp_toString(datum.type);
    out_string = out_string + " Input1:";
    if(datum.input_1==NULL) out_string = out_string + "NULL";
    else if(datum.input_1->name=="inop") out_string = out_string + "INOP";
    else out_string = out_string + datum.input_1->name;
    out_string = out_string + " Input2:";
    if(datum.input_2==NULL) out_string = out_string + "NULL";
    else if(datum.input_2->name=="inop") out_string = out_string + "INOP";
    else out_string = out_string + datum.input_2->name;
    if(datum.type==MUX2X1){
        out_string = out_string + " Select:"+datum.select->name;
    }
    out_string = out_string + " Output:";
    if(datum.output==NULL) out_string = out_string + "NULL";
    else if(datum.output->name=="onop") out_string = out_string + "ONOP";
    else out_string = out_string + datum.output->name;
    return out_string;
}
data_t* list_search(graph_t * list, std::string name){
    for(int i=0;i<=list->count;++i){
        if(list->data_v[i].name == name) {
            return &list->data_v[i];
        }
    }
    return NULL;
}
int max(int a, int b, int c){
    int out=a;
    out = (b>out) ? b : out;
    out = (c>out) ? c : out;
    return out;
}

void add_data(comp_t component_type, std::string name, int data_width, bool is_signed, graph_t * list){

    data_t temp_obj;
    temp_obj.name           = name;
    if(component_type==INPUT) temp_obj.input_1 = &list->inop;
    else temp_obj.input_1        = NULL;
    if(component_type==OUTPUT) temp_obj.output = &list->onop;
    else temp_obj.output         = NULL;
    temp_obj.input_2        = NULL;
    temp_obj.select   = NULL;
    temp_obj.type           = component_type;
    temp_obj.is_signed      = is_signed;
    temp_obj.width          = data_width;
	temp_obj.color 		    = "White";

    list->count++;
    list->data_v.push_back(temp_obj);

    #ifdef DEBUG
        std::cout << "New data: ";
        std::cout << node_toString(temp_obj) << std::endl;
    #endif

}
void add_op(comp_t component_type, std::string input1_name, std::string input2_name, std::string output_name, graph_t * list){
    bool is_signed = 0;
    int data_width = 0;

    data_t temp_obj;
    temp_obj.name           = comp_toString(component_type)+std::to_string(list->count);
    temp_obj.input_1        = list_search(list, input1_name);
    temp_obj.input_2        = list_search(list, input2_name);
    temp_obj.output         = list_search(list, output_name);
    temp_obj.select   = NULL;
    temp_obj.type           = component_type;
    temp_obj.is_signed      = (temp_obj.input_1->is_signed
                               ||temp_obj.input_2->is_signed
                               ||temp_obj.output->is_signed);
    temp_obj.width          = max(temp_obj.input_1->width,
                                  temp_obj.input_1->width,
                                  temp_obj.input_1->width);
	temp_obj.color 		    = "White";

    list->count++;
    list->data_v.push_back(temp_obj);

    #ifdef DEBUG
        std::cout << "New operation: ";
        std::cout << node_toString(temp_obj) << std::endl;
    #endif

}
void add_mux(std::string select_name, std::string is_true, std::string is_false, std::string output_name, graph_t * list){

    data_t temp_obj;
    temp_obj.name           = comp_toString(MUX2X1)+std::to_string(list->count);
    temp_obj.input_1        = list_search(list, is_true);
    temp_obj.input_2        = list_search(list, is_false);
    temp_obj.output         = list_search(list, output_name);
    temp_obj.select   = list_search(list, select_name);
    temp_obj.type           = MUX2X1;
    temp_obj.is_signed      = (temp_obj.input_1->is_signed
                               ||temp_obj.input_2->is_signed
                               ||temp_obj.output->is_signed);
    temp_obj.width          = max(temp_obj.input_1->width,
                                  temp_obj.input_1->width,
                                  temp_obj.input_1->width);
	temp_obj.color 		    = "White";

    list->count++;
    list->data_v.push_back(temp_obj);

    #ifdef DEBUG
        std::cout << "New mux: ";
        std::cout << node_toString(temp_obj) << std::endl;
    #endif

}
void add_assignment(std::string left, std::string right, graph_t * list){
    data_t temp_obj;
    temp_obj.name           = comp_toString(REG)+std::to_string(list->count);
    temp_obj.input_1        = list_search(list, left);
    temp_obj.input_2        = NULL;
    temp_obj.output         = list_search(list, right);
    temp_obj.select   = NULL;
    temp_obj.type           = REG;
    temp_obj.is_signed      = (temp_obj.input_1->is_signed
                               ||temp_obj.input_2->is_signed
                               ||temp_obj.output->is_signed);
    temp_obj.width          = max(temp_obj.input_1->width,
                                  temp_obj.input_1->width,
                                  temp_obj.input_1->width);
	temp_obj.color 		    = "White";

    #ifdef DEBUG
        std::cout << "New register: ";
        std::cout << node_toString(temp_obj) << std::endl;
    #endif

    list->count++;
    list->data_v.push_back(temp_obj);


}
void free_list(graph_t * list){
    for(int i=0;i<list->count;++i){
    }
    list->data_v.clear();
}
