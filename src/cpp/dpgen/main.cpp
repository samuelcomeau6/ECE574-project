#include <stdlib.h>
#include <cstring>
#include "parse.h"
#include "path.h"



data_list d_list;

int create_v_file(const char* template_file, char* output_file, char* module_name);

	
int main(int argc, char* argv[])
{
	char temp_name[81];
	char temp_name2[81];
	char module_name[81];
	char* ptr;

	// Error if user does not supply 2 arguments
	if (argc != 3)
	{
		printf("ERROR: Requires 2 arguments. Actual: %d\n", argc - 1);
		return 1;
	}

	// Verify input file exists
	if (FILE* file = fopen(argv[1], "r"))
	{
		fclose(file);
	}
	else
	{
		printf("ERROR: Cannot open input file %s.\n", argv[1]);
		return 1;
	}

	//remove file extension/path from output filename
	strcpy(module_name, argv[2]);
	ptr = strstr(module_name, ".");
	*ptr = 0;
	#ifdef DEBUG
	    printf("Module name:%s\n",module_name);
    #endif


	parse::parse((std::string)argv[1]);

	create_v_file("verilog_template.vh", argv[2], module_name);

	return 0;


}

int create_v_file(const char* template_file, char* output_file, char* module_name)
{
	char line[256];
	// template file pointer
	FILE* templatefp = fopen(template_file, "r");
	if (!templatefp)
	{
		printf("ERROR2: Cannot open output file %s.\n", template_file);
		return 1;
	}

	// output file pointer
	FILE* outputfp = fopen(output_file, "w");
	if (!outputfp)
	{
		printf("ERROR2: Cannot open file %s.\n", output_file);
		return 1;
	}




	// Read template file one line at a time
	while (fgets(line, 255, templatefp) != 0)
	{
		char* delimit;
		delimit = strstr(line, "$$");

		//search for delimiter
		if (delimit == 0) //delimiter not found
			fputs(line, outputfp);
		else //delimiter found
		{
			//advance position
			delimit += strlen("$$");

			if (strncmp(delimit, "MODULE_NAME", strlen("MODULE_NAME")) == 0)
			{ // Found module name
				char* new_line = new char[strlen(line) + 50];

				int length = strstr(line, "$$") - line;
				strncpy(new_line, line, length);
				new_line[length] = 0; // set null char
				strcat(new_line, module_name);
				fputs(new_line, outputfp);
				delete[] new_line;

			}
			else if (strncmp(delimit, "BEGIN_INPUT", strlen("BEGIN_INPUT")) == 0)
			{
				int count = 0;
				int total_count = 0;
				#ifdef DEBUG
				    printf("input list count:%d\n", d_list.count);
			    #endif
				for (int i = 0; i < d_list.count; i++)
				{
					if (d_list.data_v[i].is_input)
						count++;
				}
				for (int i = 0; i < d_list.count; i++)
				{
					if (!d_list.data_v[i].is_input)
						continue;

					total_count++;
					char* new_line = new char[81];
					if(d_list.data_v[i].is_signed)
						sprintf(new_line, "\t input signed [%d:0] %s,\n", d_list.data_v[i].width - 1, d_list.data_v[i].input_1_name);
					else
						sprintf(new_line, "\t input [%d:0] %s,\n", d_list.data_v[i].width - 1, d_list.data_v[i].input_1_name);

					fputs(new_line, outputfp);
					delete[] new_line;
				}
				fputs("\n", outputfp);
			}
			else if (strncmp(delimit, "BEGIN_OUTPUT", strlen("BEGIN_OUTPUT")) == 0)
			{
				int count = 0;
				int total_count = 0;
                #ifdef DEBUG
    				printf("output list count:%d\n", d_list.count);
				#endif
				for (int i = 0; i < d_list.count; i++)
				{
					if (d_list.data_v[i].is_output)
						count++;
				}
				for (int i = 0; i < d_list.count; i++)
				{
					if (!d_list.data_v[i].is_output)
						continue;

					total_count++;
					char* new_line = new char[81];
					if (d_list.data_v[i].is_signed)
						sprintf(new_line, "\t output signed [%d:0] %s", d_list.data_v[i].width - 1, d_list.data_v[i].input_1_name);
					else
						sprintf(new_line, "\t output [%d:0] %s", d_list.data_v[i].width - 1, d_list.data_v[i].input_1_name);

					if (total_count != count)
						strcat(new_line, ",\n");
					fputs(new_line, outputfp);
					delete[] new_line;
				}
			}
			else if (strncmp(delimit, "BEGIN_LOGIC", strlen("BEGIN_LOGIC")) == 0)
			{
			    #ifdef DEBUG
    				printf("logic list count:%d\n", d_list.count);
				#endif
				char* comp_op;
				char* inc_op;
				char* dec_op;
				for (int i = 0; i < d_list.count; i++)
				{
					if (d_list.data_v[i].is_wire)
					{
						char* new_line = new char[81];
						if (d_list.data_v[i].is_signed && d_list.data_v[i].width>1)
							sprintf(new_line, "\t wire signed [%d:0] %s;\n", d_list.data_v[i].width - 1, d_list.data_v[i].input_1_name);
						else if (d_list.data_v[i].is_signed)
							sprintf(new_line, "\t wire signed %s;\n", d_list.data_v[i].input_1_name);
						else if (d_list.data_v[i].width > 1)
							sprintf(new_line, "\t wire [%d:0] %s;\n", d_list.data_v[i].width - 1, d_list.data_v[i].input_1_name);
						else
							sprintf(new_line, "\t wire %s;\n", d_list.data_v[i].input_1_name);

						fputs(new_line, outputfp);
						delete[] new_line;
					}
					else if (d_list.data_v[i].is_operation)
					{
						int max_width = 0;
						// Search for maximum width
						for (int y = 0; y < d_list.count; y++)
						{
							if (!strcmp(d_list.data_v[i].input_1_name, d_list.data_v[y].input_1_name))
							{
								if (d_list.data_v[y].width > max_width)
									max_width = d_list.data_v[y].width;
							}
							if (!strcmp(d_list.data_v[i].input_2_name, d_list.data_v[y].input_1_name))
							{
								if (d_list.data_v[y].width > max_width)
									max_width = d_list.data_v[y].width;
							}
							if (!strcmp(d_list.data_v[i].output_name, d_list.data_v[y].input_1_name))
							{
								if (d_list.data_v[y].width > max_width)
									max_width = d_list.data_v[y].width;
							}
						}
						comp_op = strstr(d_list.data_v[i].operation_name, "COMP");
						inc_op = strstr(d_list.data_v[i].operation_name, "INC");
						dec_op = strstr(d_list.data_v[i].operation_name, "DEC");

						if(comp_op) // true if this is a compare OP
						{
							char op[] = "00";
							//Find compare operation
							if (strstr(comp_op, "=="))
								strcpy(op, "eq");
							if (strstr(comp_op, "<"))
								strcpy(op, "lt");
							if (strstr(comp_op, ">"))
								strcpy(op, "gt");

							char* new_line = new char[81];
							sprintf(new_line, "\t COMP #(%d) u_COMP%d (%s,%s,.%s(%s));\n",
								max_width,
								i,
								d_list.data_v[i].input_1_name,
								d_list.data_v[i].input_2_name,
								op,
								d_list.data_v[i].output_name
							);
							fputs(new_line, outputfp);
							delete[] new_line;

						}
						else if (inc_op) // true if this is a INC OP
						{
							char* new_line = new char[81];
							sprintf(new_line, "\t INC #(%d) u_INC%d (%s,%s);\n",
								max_width,
								i,
								d_list.data_v[i].input_1_name,
								d_list.data_v[i].output_name
							);
							fputs(new_line, outputfp);
							delete[] new_line;
						}
						else if (dec_op) // true if this is a INC OP
						{
							char* new_line = new char[81];
							sprintf(new_line, "\t DEC #(%d) u_DEC%d (%s,%s);\n",
								max_width,
								i,
								d_list.data_v[i].input_1_name,
								d_list.data_v[i].output_name
							);
							fputs(new_line, outputfp);
							delete[] new_line;
						}
						else
						{
							char* new_line = new char[81];
							sprintf(new_line, "\t %s #(%d) u_%s%d (%s,%s,%s);\n",
								d_list.data_v[i].operation_name,
								max_width,
								d_list.data_v[i].operation_name,
								i,
								d_list.data_v[i].input_1_name,
								d_list.data_v[i].input_2_name,
								d_list.data_v[i].output_name
							);
							fputs(new_line, outputfp);
							delete[] new_line;
						}
					}
					else if (d_list.data_v[i].is_assignment)
					{
						int max_width = 0;
						// Search for maximum width
						for (int y = 0; y < d_list.count; y++)
						{
							if (!strcmp(d_list.data_v[i].input_1_name, d_list.data_v[y].input_1_name))
							{
								if (d_list.data_v[y].width > max_width)
									max_width = d_list.data_v[y].width;
							}
							if (!strcmp(d_list.data_v[i].output_name, d_list.data_v[y].input_1_name))
							{
								if (d_list.data_v[y].width > max_width)
									max_width = d_list.data_v[y].width;
							}
						}

						char* new_line = new char[81];
						sprintf(new_line, "\t REG #(%d) u_REG%d (%s,clk,rst,%s);\n",
							max_width,
							i,
							d_list.data_v[i].input_1_name,
							d_list.data_v[i].output_name
						);
						fputs(new_line, outputfp);
						delete[] new_line;
					}
				}
			}
			else
			{
				fputs(line, outputfp);
			}
		}

	}

	fclose(outputfp);
	return 0;
}