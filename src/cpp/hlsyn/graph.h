#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <vector>
#include <cfloat>

/** @file
*/
/**
*/
enum comp_type {ERR, REG, ADD, SUB, MUL, COMPLT, COMPEQ, COMPGT, COMPLTE, COMPGTE,
         MUX2X1, SHR, SHL, DIV, MOD, INC, DEC, INPUT, OUTPUT, WIRE, VAR, IF, THEN, ELSE};
/**
*/
typedef enum comp_type comp_t;
/**
*/
struct edge_struct{
    std::string name;
    struct node_struct * from;
    struct node_struct * to;
   	comp_t type;
	bool is_signed;
	int          width;
	int        duration;
	std::string  color;
	bool is_copy;

};
/**
*/
typedef struct edge_struct edge_t;
/**
*/
struct node_struct{
    std::string name;
	struct edge_struct *  input_1;
	struct edge_struct *  input_2;
	struct edge_struct *  select;
	struct edge_struct *  output;
	struct edge_srtuct * output_2;
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
/**
*/
typedef struct node_struct node_t;
/** @brief Class consisting of node_t and edge_t objects
*/
class Graph{
    public:
        /** @brief The input no-operation node, always scheduled at time=0
        */
        node_t inop;
        /** @brief The output no-operation node, always scheduled at time= latency+1
        */
        node_t onop;
        /** @brief The type distribution of the graph. Used in fds() populated by compute_type_dist()*/
        std::vector<std::vector<float>> q;
    	std::vector<node_t *> nodes;
    	std::vector<edge_t *> edges;
    	/** @brief Default constructor
    	*/
        Graph();
        /** @brief Copy constructor
        */
    	Graph(const Graph &g);
    	/** @brief Adds a node
    	*/
        node_t * add_node(comp_t component_type, std::string input1_name, std::string input2_name, std::string select, std::string output_name);
        /** @brief Adds and if construct (not implemented)
        */
        node_t * add_if(std::string cond);
        /** @brief Adds an unconnected edge based on name
        */
        edge_t * add_edge(comp_t component_type, std::string name, int data_width, bool is_signed);
        /** @brief Adds a fully connected edge
        */
        edge_t * add_edge(comp_t component_type, std::string name, node_t * from, node_t* to, int data_width, bool is_signed);
        /** @brief Returns graph as a dot compatible string
        */
        std::string graph_toString();
        /** @brief Returns graph as a dot compatible string with timing
        */
        std::string scheduled_graph_toString();
        /** @brief Changes color of all nodes in graph
            @param Color - the color to paint all nodes, default should be white
        */
        void paint(std::string Color);
    private:
        /** @brief Private function used by graph_toString() and scheduled_graph_toString()
        */
        std::string start_graph_toString();

};
/** @brief Returns a human readable node_t
*/
std::string node_toString(node_t datum);
/** @brief Returns a human-readable edge_t
*/
std::string edge_toString(edge_t datum);
/** @brief Searches for an edge based on its name and returns its pointer to link it to a node
*/
edge_t* edge_search(Graph * list, std::string name,bool is_from);
/** @brief Returns a human-readable comp_t
*/
std::string comp_toString(comp_t component);
/** @brief Get the duration of a module based on its type
*/
int get_duration(comp_t type, int width);
#endif
