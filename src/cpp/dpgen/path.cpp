#include <iostream>
#include <cstring>
#include <string>
#include "parse.h"
#include "path.h"
#include "data_list.h"
#include "critical_path.h"

namespace path{
    std::string component_to_string(int data_width, bool data_signed, parse::comp_t component){
        std::string output;
        if(data_signed) output = output + "signed ";
        else output = output + "unsigned ";
        output = output + std::to_string(data_width) + " bit ";
        switch(component){
             case parse::ERR: output = output + "ERROR"; break;
             case parse::REG: output = output + "REG"; break;
             case parse::ADD: output = output + "ADD"; break;
             case parse::SUB: output = output + "SUB"; break;
             case parse::MUL: output = output + "MUL"; break;
             case parse::COMPLT: output = output + "COMP<"; break;
             case parse::COMPEQ: output = output + "COMP=="; break;
             case parse::COMPGT: output = output + "COMP>"; break;
             case parse::COMPLTE: output = output + "COMP<="; break;
             case parse::COMPGTE: output = output + "COMP>="; break;
             case parse::MUX2X1: output = output + "MUX2X1"; break;
             case parse::SHR: output = output + "SHR"; break;
             case parse::SHL: output = output + "SHL"; break;
             case parse::DIV: output = output + "DIV"; break;
             case parse::MOD: output = output + "MOD"; break;
             case parse::INC: output = output + "INC"; break;
             case parse::DEC: output = output + "DEC"; break;
             case parse::INPUT: output = output + "INPUT"; break;
             case parse::OUTPUT: output = output + "OUTPUT"; break;
             case parse::WIRE: output = output + "WIRE"; break;
        }
        return output;
    }
    std::string operation_toString(parse::comp_t component) {
        std::string output;
        
        switch (component) {
        case parse::ERR:     output = "ERROR"; break;
        case parse::REG:     output = "REG"; break;
        case parse::ADD:     output = "ADD"; break;
        case parse::SUB:     output = "SUB"; break;
        case parse::MUL:     output = "MUL"; break;
        case parse::COMPLT:  output = "COMP<"; break;
        case parse::COMPEQ:  output = "COMP=="; break;
        case parse::COMPGT:  output = "COMP>"; break;
        case parse::COMPLTE: output = "COMP<="; break;
        case parse::COMPGTE: output = "COMP>="; break;
        case parse::MUX2X1:  output = "MUX2x1"; break;
        case parse::SHR:     output = "SHR"; break;
        case parse::SHL:     output = "SHL"; break;
        case parse::DIV:     output = "DIV"; break;
        case parse::MOD:     output = "MOD"; break;
        case parse::INC:     output = "INC"; break;
        case parse::DEC:     output = "DEC"; break;
        case parse::INPUT:   output = "INPUT"; break;
        case parse::OUTPUT:  output = "OUTPUT"; break;
        case parse::WIRE:    output = "WIRE"; break;
        }
        return output;
    }

    void add_data(parse::comp_t component_type, std::string name, int data_width, bool is_signed){
        #ifdef DEBUG
            std::cout << "New DATA ";
            std::cout << component_to_string(data_width, is_signed, component_type);
            std::cout << " named " << name << std::endl;
        #endif

        data_type temp_obj;
        temp_obj.input_1_name = new char[name.size() + 1];
        strcpy(temp_obj.input_1_name, name.c_str());
        temp_obj.input_2_name   = 0;
        temp_obj.output_name    = 0;
        temp_obj.operation_name = 0;
        temp_obj.is_input       = (component_type == parse::INPUT);
        temp_obj.is_output      = (component_type == parse::OUTPUT);
        temp_obj.is_operation   = false;
        temp_obj.is_mux         = false;
        temp_obj.is_wire        = (component_type == parse::WIRE);
        temp_obj.is_reg         = (component_type == parse::REG);
        temp_obj.is_signed      = is_signed;
        temp_obj.is_assignment  = false;
        temp_obj.width          = data_width;

        d_list.count++;
        d_list.data_v.push_back(temp_obj);
    }
    void add_op(parse::comp_t component_type, std::string input1, std::string input2, std::string output){
        bool is_signed = 0;
        int data_width = 0;
        #ifdef DEBUG
            std::cout << "New OP ";
            std::cout << component_to_string(data_width, is_signed, component_type);
            std::cout << " with inputs " << input1 << " and " << input2;
            std::cout << " and output " << output << std::endl;
        #endif

        data_type temp_obj;
        temp_obj.input_1_name = new char[input1.size() + 1];
        temp_obj.input_2_name = new char[input2.size() + 1];
        temp_obj.output_name = new char[output.size() + 1];
        temp_obj.operation_name = new char[operation_toString(component_type).size() + 1];
        strcpy(temp_obj.input_1_name, input1.c_str());
        strcpy(temp_obj.input_2_name, input2.c_str());
        strcpy(temp_obj.output_name, output.c_str());
        strcpy(temp_obj.operation_name, operation_toString(component_type).c_str());
        temp_obj.is_input = false;
        temp_obj.is_output = false;
        temp_obj.is_operation = true;
        temp_obj.is_mux = false;
        temp_obj.is_wire = false;
        temp_obj.is_reg = false;
        temp_obj.is_signed = false;
        temp_obj.is_assignment = false;
        temp_obj.width = 0;
        temp_obj.duration = 0;

        d_list.count++;
        d_list.data_v.push_back(temp_obj);
    }
    void add_mux(std::string input, std::string is_true, std::string is_false, std::string output){
        #ifdef DEBUG
            std::cout << "New ";
            std::cout << "MUX";
            std::cout << " with input " << input << " with options ";
            std::cout << is_true << " if true and " << is_false << " if false";
            std::cout << " and output " << output << std::endl;
        #endif

        data_type temp_obj;
        temp_obj.input_1_name = new char[is_true.size() + 1];
        temp_obj.input_2_name = new char[is_false.size() + 1];
        temp_obj.output_name = new char[output.size() + 1];
        temp_obj.operation_name = new char[input.size() + 1];
        strcpy(temp_obj.input_1_name, is_true.c_str());
        strcpy(temp_obj.input_2_name, is_false.c_str());
        strcpy(temp_obj.output_name, output.c_str());
        strcpy(temp_obj.operation_name, input.c_str());
        temp_obj.is_input = false;
        temp_obj.is_output = false;
        temp_obj.is_operation = false;
        temp_obj.is_mux = true;
        temp_obj.is_wire = false;
        temp_obj.is_reg = false;
        temp_obj.is_signed = false;
        temp_obj.is_assignment = false;
        temp_obj.width = 0;
        temp_obj.duration = 0;
        
        d_list.count++;
        d_list.data_v.push_back(temp_obj);
    }
    void add_assignment(std::string left, std::string right){
        #ifdef DEBUG
            std::cout << "Assign " << right << " to " << left << std::endl;
        #endif
        data_type temp_obj;
        temp_obj.output_name = new char[left.size() + 1];
        temp_obj.input_1_name = new char[right.size() + 1];
        strcpy(temp_obj.output_name, left.c_str());
        strcpy(temp_obj.input_1_name, right.c_str());
        temp_obj.input_2_name = 0;
        temp_obj.operation_name = 0;
        temp_obj.is_input = false;
        temp_obj.is_output = false;
        temp_obj.is_operation = false;
        temp_obj.is_mux = false;
        temp_obj.is_wire = false;
        temp_obj.is_reg = false;
        temp_obj.is_signed = false;
        temp_obj.is_assignment = true;
        temp_obj.width = 0;
        temp_obj.duration = 0;
		temp_obj.color = "none";

        d_list.count++;
        d_list.data_v.push_back(temp_obj);
    }
    void free_list(){
        for(int i=0;i<d_list.count;++i){
            delete[] d_list.data_v[i].output_name;
            delete[] d_list.data_v[i].input_1_name;
            delete[] d_list.data_v[i].input_2_name;
            delete[] d_list.data_v[i].operation_name;
        }
        d_list.data_v.clear();
    }
	void assignDuration(d_list);
}
