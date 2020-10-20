#include <iostream>
#include <string>
#include "parse.h"
#include "path.h"

namespace path{
    std::string component_to_string(int data_width, bool data_signed, parse::comp_t component){
        std::string output;
        if(data_signed) output = output + "signed ";
        else output = output + "unsigned ";
        output = output + std::to_string(data_width) + " bit ";
        switch(component){
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
    void add_data(parse::comp_t component_type, std::string name, int data_width, bool is_signed){
        std::cout << "New ";
        std::cout << component_to_string(data_width, is_signed, component_type);
        std::cout << " named " << name << std::endl;
    }
    void add_op(parse::comp_t component_type, std::string input1, std::string input2, std::string output){
        bool is_signed = 0;
        int data_width = 0;
        std::cout << "New ";
        std::cout << component_to_string(data_width, is_signed, component_type);
        std::cout << " with inputs " << input1 << " and " << input2;
        std::cout << " and output " << output << std::endl;
    }
    void add_mux(std::string input, std::string is_true, std::string is_false, std::string output){
        std::cout << "New ";
        std::cout << "MUX";
        std::cout << " with input " << input << " with options ";
        std::cout << is_true << " if true and " << is_false << " if false";
        std::cout << " and output " << output << std::endl;
    }
    void add_assignment(std::string left, std::string right){
        std::cout << "Assign " << right << " to " << left << std::endl;
    }
}