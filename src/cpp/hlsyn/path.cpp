#include <iostream>
#include <cstring>
#include <string>
#include "parse.h"
#include "path.h"
#include "graph_type.h"

namespace path{
    std::string comp_toString(comp_t component) {
        std::string output;

        switch (component) {
        case ERR:     output = "ERROR"; break;
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
        }
        return output;
    }


    std::string node_toString(data_t datum){
        std::string output;
        if(datum.is_signed) output = output + "signed ";
        else output = output + "unsigned ";
        output = output + std::to_string(datum.width) + " bit ";
        output = output + comp_toString(datum.type);
        output = output + "Input1:";
        if(datum.input_1==NULL) output = output = "NULL";
        else output = output = datum.input_1->name;
        if(datum.input_2==NULL) output = output = "NULL";
        else output = output = datum.input_2->name;
        if(datum.output==NULL) output = output = "NULL";
        else output = output = datum.output->name;
        return output;
    }

    void add_data(comp_t component_type, std::string name, int data_width, bool is_signed, graph_t * list){

        data_t temp_obj;
        temp_obj.name           = name;
        if(component_type==INPUT) temp_obj.input_1 = &list->inop;
        else temp_obj.input_1        = NULL;
        if(component_type==OUTPUT) temp_obj.input_1 = &list->onop;
        else temp_obj.output         = NULL;
        temp_obj.input_2        = NULL;
        temp_obj.shift_select   = NULL;
        temp_obj.is_signed      = is_signed;
        temp_obj.width          = data_width;
    	temp_obj.color 		    = "White";

        list->count++;
        list->data_v.push_back(temp_obj);


    }
    void add_op(comp_t component_type, std::string input1_name, std::string input2_name, std::string output_name, graph_t * list){
        bool is_signed = 0;
        int data_width = 0;

        data_t temp_obj;
        temp_obj.name           = comp_toString(component_type)+std::to_string(list->count);
        temp_obj.input_1        = list_search(list, input1_name);
        temp_obj.input_2        = list_search(list, input2_name);
        temp_obj.output         = list_search(list, output_name);
        temp_obj.shift_select   = NULL;
        temp_obj.is_signed      = (temp.obj->input_1->is_signed
                                   ||temp.obj->input_2->is_signed
                                   ||temp.obj->output->is_signed)
        temp_obj.width          = max(temp.obj->input_1->is_signed,
                                      temp.obj->input_1->is_signed,
                                      temp.obj->input_1->is_signed);
    	temp_obj.color 		    = "White";

        list->count++;
        list->data_v.push_back(temp_obj);

        #ifdef DEBUG
            std::cout << "New OP ";
            std::cout << node_toString(temp_obj) << std::endl;
        #endif

    }
    void add_mux(std::string select_name, std::string is_true, std::string is_false, std::string output_name){

        data_t temp_obj;
        temp_obj.name           = comp_toString(component_type)+std::to_string(list->count);
        temp_obj.input_1        = list_search(list, is_true);
        temp_obj.input_2        = list_search(list, is_false);
        temp_obj.output         = list_search(list, output_name);
        temp_obj.shift_select   = list_search(list, select_name);
        temp_obj.is_signed      = (temp.obj->input_1->is_signed
                                   ||temp.obj->input_2->is_signed
                                   ||temp.obj->output->is_signed)
        temp_obj.width          = max(temp.obj->input_1->is_signed,
                                      temp.obj->input_1->is_signed,
                                      temp.obj->input_1->is_signed);
    	temp_obj.color 		    = "White";

        list->count++;
        list->data_v.push_back(temp_obj);

        #ifdef DEBUG
            std::cout << "New OP ";
            std::cout << node_toString(temp_obj) << std::endl;
        #endif

    }
    void add_assignment(std::string left, std::string right){
        data_t temp_obj;
        temp_obj.name           = comp_toString(component_type)+std::to_string(list->count);
        temp_obj.input_1        = list_search(list, is_true);
        temp_obj.input_2        = list_search(list, is_false);
        temp_obj.output         = list_search(list, output_name);
        temp_obj.shift_select   = list_search(list, select_name);
        temp_obj.is_signed      = (temp.obj->input_1->is_signed
                                   ||temp.obj->input_2->is_signed
                                   ||temp.obj->output->is_signed)
        temp_obj.width          = max(temp.obj->input_1->is_signed,
                                      temp.obj->input_1->is_signed,
                                      temp.obj->input_1->is_signed);
    	temp_obj.color 		    = "White";

        list->count++;
        list->data_v.push_back(temp_obj);

        #ifdef DEBUG
            std::cout << "New ASSIGN ";
            std::cout << node_toString(temp_obj) << std::endl;
        #endif

    }
    void free_list(){
        for(int i=0;i<list->count;++i){
            delete[] list->data_v[i].output_name;
            delete[] list->data_v[i].input_1_name;
            delete[] list->data_v[i].input_2_name;
            delete[] list->data_v[i].operation_name;
        }
        list->data_v.clear();
    }
}
