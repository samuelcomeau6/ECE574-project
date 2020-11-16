#include <string>
#include <vector>

#ifndef PATH_H
#define PATH_H
enum comp_type {ERR, REG, ADD, SUB, MUL, COMPLT, COMPEQ, COMPGT, COMPLTE, COMPGTE,
         MUX2X1, SHR, SHL, DIV, MOD, INC, DEC, INPUT, OUTPUT, WIRE};
typedef enum comp_type comp_t;

struct data_type_struct
{
    std::string name;
	struct data_type_struct *  input_1;
	struct data_type_struct *  input_2;
	struct data_type_struct *  select;
	struct data_type_struct *  output;
	comp_t type;
	bool is_signed;
	int          width;
	float        duration;
	std::string  color;

};
typedef struct data_type_struct data_t;

typedef struct
{
	int count;
	data_t inop;
	data_t onop;
	std::vector<data_t> data_v;

} graph_t;


std::string comp_toString(comp_t component);
std::string node_toString(data_t datum);
data_t * list_search(graph_t * list, std::string name);
int max(int a, int b, int c);
void add_data(comp_t component_type, std::string name, int data_width, bool is_signed, graph_t * list);
void add_op(comp_t component_type, std::string input1_name, std::string input2_name, std::string output_name, graph_t * list);
void add_mux(std::string select_name, std::string is_true, std::string is_false, std::string output_name, graph_t * list);
void add_assignment(std::string left, std::string right, graph_t * list);
void free_list(graph_t * list);
#endif