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
	int        duration;
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
	int width;
	int duration;
	int start_time;
	int interval[2];
	std::string color;
	std::vector<float> prb;
    std::vector<float> self_force;
    std::vector<float> total_force;

};
typedef struct node_struct node_t;

class Graph{
    public:
        node_t inop;
        node_t onop;
        std::vector<std::vector<float>> q;
    	std::vector<node_t *> nodes;
    	std::vector<edge_t *> edges;
        Graph();
    	Graph(const Graph &g);
        void add_node(comp_t component_type, std::string input1_name, std::string input2_name, std::string select, std::string output_name);
        void add_edge(comp_t component_type, std::string name, int data_width, bool is_signed);
        edge_t * copy_edge(edge_t edge);
        std::string graph_toString();
        std::string scheduled_graph_toString();
        void paint(std::string);
    private:
        std::string start_graph_toString();

};

std::string node_toString(node_t datum);
std::string edge_toString(edge_t datum);
edge_t* edge_search(Graph * list, std::string name,bool is_from);
int max(int a, int b, int c);
std::string comp_toString(comp_t component);
int get_duration(comp_t type, int width);
#endif
