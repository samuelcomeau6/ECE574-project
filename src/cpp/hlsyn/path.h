#include <string>
#include "parse.h"
#include "graph_type.h"

#ifndef PATH_H
#define PATH_H

namespace path{
    enum comp_t {ERR, REG, ADD, SUB, MUL, COMPLT, COMPEQ, COMPGT, COMPLTE, COMPGTE,
             MUX2X1, SHR, SHL, DIV, MOD, INC, DEC, INPUT, OUTPUT, WIRE};

    std::string component_to_string(int data_width, bool data_signed, parse::comp_t component);
    void add_data(parse::comp_t component_type, std::string name, int data_width, bool is_signed);
    void add_op(parse::comp_t component_type, std::string input1, std::string input2, std::string output);
    void add_mux(std::string input, std::string is_true, std::string is_false, std::string output);
    void add_assignment(std::string left, std::string right);
    void free_list();
}
#endif