#include <iostream>
#include <string>
#include "parse.h"
#include "path.h"

namespace path{
    std::string component_to_string(int data_width, bool data_signed, parse::comp_t component){
        std::string output="";
        if(data_width>0) output = output + std::to_string(data_width);
        switch(component){
             case parse::REG: output = output + "R"; break;
             case parse::ADD: output = output + "+"; break;
             case parse::SUB: output = output + "-"; break;
             case parse::MUL: output = output + "*"; break;
             case parse::COMPLT: output = output + "<"; break;
             case parse::COMPEQ: output = output + "=="; break;
             case parse::COMPGT: output = output + ">"; break;
             case parse::COMPLTE: output = output + "<="; break;
             case parse::COMPGTE: output = output + ">="; break;
             case parse::MUX2X1: output = output + "?"; break;
             case parse::SHR: output = output + ">>"; break;
             case parse::SHL: output = output + "<<"; break;
             case parse::DIV: output = output + "/"; break;
             case parse::MOD: output = output + "%"; break;
             case parse::INC: output = output + "++"; break;
             case parse::DEC: output = output + "--"; break;
             case parse::INPUT: output = output + "IN"; break;
             case parse::OUTPUT: output = output + "OUT"; break;
             case parse::WIRE: output = output + "W"; break;
        }
        return output;
    }
    void add_data(parse::comp_t component_type, std::string name, int data_width, bool is_signed){
        std::cout << name << std::endl;
    }
    void add_op(parse::comp_t component_type, std::string input1, std::string input2, std::string output){
        bool is_signed = 0;
        int data_width = 0;
        std::string name = input1+input2+output;
        std::cout << name << "[label =\""+ component_to_string(data_width, is_signed, component_type) <<"\"]"<<std::endl;
        std::cout << input1 << "->"  << name << std::endl;
        std::cout << input2 << "->" << name << std::endl;
        std::cout << name << "->" << output << std::endl;
    }
    void add_mux(std::string input, std::string is_true, std::string is_false, std::string output){
        bool is_signed = 0;
        int data_width = 0;
        std::string name = input+is_true+is_false+output;
        std::cout << name << "[label =\""<<input << component_to_string(data_width, is_signed, parse::MUX2X1)<<is_true <<":"<<is_false <<"\"]"<<std::endl;
        std::cout << input << "->"  << name << "[headport=w]" << std::endl;
        std::cout << is_true << "->" << name << std::endl;
        std::cout << is_false << "->" << name << std::endl;
        std::cout << name << "->" << output << std::endl;
    }
    void add_assignment(std::string left, std::string right){
        std::cout << right << "->" << left << std::endl;
    }
}