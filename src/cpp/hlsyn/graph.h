#include <string>
#include <vector>

#ifndef GRAPH_H
#define GRAPH_H

enum comp_type {ERR, REG, ADD, SUB, MUL, COMPLT, COMPEQ, COMPGT, COMPLTE, COMPGTE,
         MUX2X1, SHR, SHL, DIV, MOD, INC, DEC, INPUT, OUTPUT, WIRE, VAR};
typedef enum comp_type comp_t;
struct edge_struct{
    std::string name;
    struct node_struct * from;
    struct node_struct * to;
   	comp_t type;
	bool is_signed;
	int          width;
	float        duration;
	std::string  color;

};
typedef struct edge_struct edge_t;

struct node_struct{
    std::string name;
	struct edge_struct *  input_1;
	struct edge_struct  *  input_2;
	struct edge_struct  *  select;
	struct edge_struct  *  output;
	comp_t type;
	bool is_signed;
	int          width;
	float        duration;
	std::string  color;

};
typedef struct node_struct node_t;

typedef struct
{
	node_t inop;
	node_t onop;
	std::vector<node_t> nodes;
	std::vector<edge_t> edges;

} graph_t;

#endif