
#include <cstring>
#include "parse.h"
#include "path.h"



data_list d_list;

int create_v_file(const char* template_file, char* output_file, char* module_name);

	
int main(int argc, char* argv[])
{
	char temp_name[81];
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
		printf("ERROR: Cannot open file %s.\n", argv[1]);
		return 1;
	}

	//remove file extension/path from input filename
	strcpy(temp_name, argv[1]);
	ptr = strstr(temp_name, ".");
	*ptr = 0;
	for(int i = strlen(temp_name); i != 0; i--)
	{
		if ((temp_name[i] == '/') || (temp_name[i] == '\\'))
		{
			int y = 0;
			do 
			{
				i++;
				module_name[y] = temp_name[i];
				y++;
			}while (temp_name[i] != '\0');
			break;
		}
	}


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
		printf("ERROR2: Cannot open file %s.\n", template_file);
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

			}
			else if (strncmp(delimit, "BEGIN_INPUT", strlen("BEGIN_INPUT")) == 0)
			{
				#ifdef DEBUG
				    printf("input list count:%d\n", d_list.count);
			    #endif
				for (int i = 0; i < d_list.count; i++)
				{
					if (!d_list.data_v[i].is_input)
						continue;

					char* new_line = new char[81];
					strcpy(new_line, "\t input ");
					strcat(new_line, d_list.data_v[i].input_1_name);
					strcat(new_line, ",\n");
					fputs(new_line, outputfp);
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
					strcpy(new_line, "\t output ");
					strcat(new_line, d_list.data_v[i].input_1_name);
					if (total_count != count)
						strcat(new_line, ";\n");
					fputs(new_line, outputfp);
				}
			}
			else if (strncmp(delimit, "BEGIN_LOGIC", strlen("BEGIN_LOGIC")) == 0)
			{
			    #ifdef DEBUG
    				printf("logic list count:%d\n", d_list.count);
				#endif

				for (int i = 0; i < d_list.count; i++)
				{
					if (d_list.data_v[i].is_wire)
					{
						char* new_line = new char[81];
						sprintf(new_line, "\t wire [%d:0] %s;\n", d_list.data_v[i].width - 1, d_list.data_v[i].input_1_name);
						fputs(new_line, outputfp);
					}
					else if (d_list.data_v[i].is_operation)
					{
						char* new_line = new char[81];
						sprintf(new_line, "\t %s #(0) u_%s%d (%s,%s,%s);\n",
							d_list.data_v[i].operation_name,
							d_list.data_v[i].operation_name,
							i,
							d_list.data_v[i].input_1_name,
							d_list.data_v[i].input_2_name,
							d_list.data_v[i].output_name
						);
						fputs(new_line, outputfp);
					}
					else if (d_list.data_v[i].is_assignment)
					{
						char* new_line = new char[81];
						sprintf(new_line, "\t assign %s = %s;\n", d_list.data_v[i].output_name, d_list.data_v[i].input_1_name);
						fputs(new_line, outputfp);
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