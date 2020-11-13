
#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#include <string>


typedef struct
{
	char* input_1_name;
	char* input_2_name;
	char* shift_select;
	char* output_name;
	char* operation_name;
	bool  is_input;
	bool  is_output;
	bool  is_operation;
	bool  is_mux;
	bool  is_wire;
	bool  is_reg;
	bool  is_signed;
	bool  is_assignment;
	int   width;
	float duration;
	std::string color;

} data_type;


#endif
