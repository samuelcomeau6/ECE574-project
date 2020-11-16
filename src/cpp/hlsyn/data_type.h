
#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#include <string>
#include "path.h"

struct data_type_struct
{
    std::string name;
	struct data_type_struct *  input_1;
	struct data_type_struct *  input_2;
	struct data_type_struct *  shift_select;
	struct data_type_struct *  output;
	path::comp_t type;
	bool is_signed;
	int          width;
	float        duration;
	std::string  color;

};
typedef struct data_type_struct data_t;


#endif
