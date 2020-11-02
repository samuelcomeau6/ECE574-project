
#ifndef DATA_TYPE_H
#define DATA_TYPE_H


typedef struct
{
	char* input_1_name;
	char* input_2_name;
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

} data_type;


#endif