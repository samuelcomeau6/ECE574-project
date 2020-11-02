#include <string>
#include "data_list.h"


extern data_list d_list;

namespace path{
    std::string component_to_string(int data_width, bool data_signed, parse::comp_t component);
    void add_data(parse::comp_t component_type, std::string name, int data_width, bool is_signed);
    void add_op(parse::comp_t component_type, std::string input1, std::string input2, std::string output);
    void add_mux(std::string input, std::string is_true, std::string is_false, std::string output);
    void add_assignment(std::string left, std::string right);
}
