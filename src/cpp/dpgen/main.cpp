#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstring>
#include "parse.h"
#include "path.h"
#include "critical_path.h"



data_list d_list;

char * strip_path(char *);
int create_v_file(const char* template_file, char* output_file, char* module_name);

    
int main(int argc, char* argv[])
{
    char module_name[81];
    d_list.count = 0;

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
    char * name = strip_path(argv[2]);
    strncpy(module_name, name,81);
    free(name);
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

                //loop through all objects
                for (int i = 0; i < d_list.count; i++)
                {
                    int   input_1_width = 0;
                    int   input_2_width = 0;
                    int   output_width = 0;
                    bool  input_1_signed = false;
                    bool  input_2_signed = false;
                    bool  output_signed = false;
                    bool  found_input1 = 0;
                    bool  found_input2 = 0;
                    bool  found_output = 0;
                    bool  op_signed = 0;

                    char* sign_char = new char[2];
                    char* operand_a = new char[81];
                    char* operand_b = new char[81];
                    char* new_line = new char[81];

                    //ignore input/output objects
                    if (d_list.data_v[i].is_input || d_list.data_v[i].is_output)
                        continue;


                    // locally Assign widths to all inputs/outputs
                    for (int y = 0; y < d_list.count; y++)
                    {
                        //we are only looking for objects that are inputs or outputs or wires
                        if (!(d_list.data_v[y].is_input || d_list.data_v[y].is_output || d_list.data_v[y].is_wire))
                            continue;

                        //Width is determined by the size of the outputs only unless comp
                        //Sign is determined by the inputs only
                        if (d_list.data_v[i].input_1_name) //check for null
                        {
                            if (!strcmp(d_list.data_v[i].input_1_name, d_list.data_v[y].input_1_name))
                            {
                                input_1_width = d_list.data_v[y].width;
                                input_1_signed = d_list.data_v[y].is_signed;
                                found_input1 = 1;
                            }
                        }
                        if (d_list.data_v[i].input_2_name) //check for null
                        {
                            if (!strcmp(d_list.data_v[i].input_2_name, d_list.data_v[y].input_1_name))
                            {
                                input_2_width = d_list.data_v[y].width;
                                input_2_signed = d_list.data_v[y].is_signed;
                                found_input2 = 1;
                            }
                        }
                        if (d_list.data_v[i].output_name) //check for null
                        {
                            if (!strcmp(d_list.data_v[i].output_name, d_list.data_v[y].input_1_name))
                            {
                                output_width = d_list.data_v[y].width;
                                output_signed = d_list.data_v[y].is_signed;
                                found_output = 1;
                            }
                        }
                    }


                    // deterine if this operation is signed, only used if this is an operation 
                    op_signed = (input_1_signed || input_2_signed || output_signed);
                    strcpy(sign_char, op_signed ? "S" : "");


                    if (output_width > input_1_width)
                    {
                        if (input_1_signed)
                            sprintf(operand_a, "{{%d{%s[%d]}}, %s}", output_width - input_1_width, d_list.data_v[i].input_1_name, input_1_width - 1, d_list.data_v[i].input_1_name);
                        else
                            sprintf(operand_a, "{{%d{1'b0}}, %s}", output_width - input_1_width, d_list.data_v[i].input_1_name);
                    }
                    else if(output_width < input_1_width)
                    {
                        sprintf(operand_a, "%s[%d:0]", d_list.data_v[i].input_1_name, output_width-1);
                    }
                    else
                    {
                    sprintf(operand_a, "%s", d_list.data_v[i].input_1_name);
                    }

                    if (found_input2)
                    {
                        if (output_width > input_2_width)
                        {
                            if (input_2_signed)
                                sprintf(operand_b, "{{%d{%s[%d]}}, %s}", output_width - input_2_width, d_list.data_v[i].input_1_name, input_2_width - 1, d_list.data_v[i].input_2_name);
                            else
                                sprintf(operand_b, "{{%d{1'b0}}, %s}", output_width - input_2_width, d_list.data_v[i].input_2_name);
                        }
                        else if (output_width < input_2_width)
                        {
                            sprintf(operand_b, "%s[%d:0]", d_list.data_v[i].input_2_name, output_width - 1);
                        }
                        else
                        {
                            sprintf(operand_b, "%s", d_list.data_v[i].input_2_name);
                        }
                    }

                    // The wires to not need to use the operand a/b logic
                    if (d_list.data_v[i].is_wire)
                    {
                        if (d_list.data_v[i].is_signed && d_list.data_v[i].width>1)
                            sprintf(new_line, "\t wire signed [%d:0] %s;\n", d_list.data_v[i].width - 1, d_list.data_v[i].input_1_name);
                        else if (d_list.data_v[i].is_signed)
                            sprintf(new_line, "\t wire %s;\n", d_list.data_v[i].input_1_name);
                        else if (d_list.data_v[i].width > 1)
                            sprintf(new_line, "\t wire [%d:0] %s;\n", d_list.data_v[i].width - 1, d_list.data_v[i].input_1_name);
                        else
                            sprintf(new_line, "\t wire %s;\n", d_list.data_v[i].input_1_name);

                        fputs(new_line, outputfp);
                    }
                    else if (d_list.data_v[i].is_operation)
                    {

                        comp_op = strstr(d_list.data_v[i].operation_name, "COMP");
                        inc_op = strstr(d_list.data_v[i].operation_name, "INC");
                        dec_op = strstr(d_list.data_v[i].operation_name, "DEC");
                        
                        if(!found_input1 || (!found_input2 && !inc_op && !dec_op) || !found_output){
                            printf("INPUT/OUTPUT NOT FOUND\n");
                            exit(EXIT_FAILURE);
                        }
                        #ifdef DEBUG
                            printf("Found: I1:%d I2:%d O:%d\n",found_input1,found_input2,found_output);
                        #endif

                        d_list.data_v[i].width= output_width; // is this needed?
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


                            sprintf(new_line, "\t %sCOMP #(%d) u_COMP%d (%s,%s,.%s(%s));\n",
                                sign_char,
                                output_width,
                                i,
                                operand_a,
                                operand_b,
                                op,
                                d_list.data_v[i].output_name
                            );
                            fputs(new_line, outputfp);

                        }
                        else if (inc_op) // true if this is a INC OP
                        {

                            sprintf(new_line, "\t %sINC #(%d) u_INC%d (%s,%s);\n",
                                sign_char,
                                output_width,
                                i,
                                operand_a,
                                d_list.data_v[i].output_name
                            );
                            fputs(new_line, outputfp);

                        }
                        else if (dec_op) // true if this is a DEC OP
                        {
                            sprintf(new_line, "\t %sDEC #(%d) u_DEC%d (%s,%s);\n",
                                sign_char,
                                output_width,
                                i,
                                operand_a,
                                d_list.data_v[i].output_name
                            );
                            fputs(new_line, outputfp);
                        }
                        else // all other operations
                        {
                            sprintf(new_line, "\t %s%s #(%d) u_%s%d (%s,%s,%s);\n",
                                sign_char,
                                d_list.data_v[i].operation_name,
                                output_width,
                                d_list.data_v[i].operation_name,
                                i,
                                operand_a,
                                operand_b,
                                d_list.data_v[i].output_name
                            );
                            fputs(new_line, outputfp);
                        }
                    }
                    else if (d_list.data_v[i].is_mux){
                        d_list.data_v[i].width= output_width;


                        sprintf(new_line, "\t %sMUX2x1 #(%d) u_MUX2x1%d (%s,%s,%s,%s);\n",
                            sign_char,
                            output_width,
                            i,
                            operand_a,
                            operand_b,
                            d_list.data_v[i].shift_select,
                            d_list.data_v[i].output_name
                        );
                        fputs(new_line, outputfp);

                    }
                    else if (d_list.data_v[i].is_assignment)
                    {

                        d_list.data_v[i].width=output_width;

                        sprintf(new_line, "\t %sREG #(%d) u_REG%d (%s,clk,rst,%s);\n",
                            sign_char,
                            output_width,
                            i,
                            operand_a,
                            d_list.data_v[i].output_name
                        );
                        fputs(new_line, outputfp);
                    }

                    delete[] new_line;
                    delete[] sign_char;
                    delete[] operand_a;
                    delete[] operand_b;
                }
            }
            else
            {
                fputs(line, outputfp);
            }
        }

    }
    assignDuration(&d_list);
    printf("Critical Path : %.3f ns\n",LongestPath(&d_list));
    path::free_list();
    fclose(outputfp);
    fclose(templatefp);
    return 0;
}

char* strip_path(char * path){
    char * temp = (char*)malloc(sizeof(char)*(strlen(path)+1));
    char * ptr = temp;
    char * lastptr = ptr;
    strcpy(temp,path);
    ptr = strtok(temp,"/\\");
    while(ptr!=NULL){
        ptr = strtok(NULL,"/\\");
        if(ptr!=NULL) lastptr=ptr;
    }
    ptr = lastptr;
    strtok(ptr,".");
    char * output = (char*)malloc(sizeof(char)*(strlen(ptr)+1));
    strcpy(output, ptr);
    free(temp);
    return output;
}