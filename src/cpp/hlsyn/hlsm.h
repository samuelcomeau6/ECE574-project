#ifndef HLSM_H
#define HLSM_H
#include "graph.h"
/** @file
*/
/**
*/
struct state_struct{
    std::string name;
    int index;
    struct state_struct * prev;
    struct state_struct * true_state;
    struct state_struct * else_state;
    bool is_else_state;
    std::string condition;
    std::string body;
};
/**
*/
typedef struct state_struct state_t;
/**
*/
class Hlsm{
    public:
        Graph graph;
        std::vector<state_t *> states;
        /** @brief Default constructor
            @param g - pointer to a graph object that will be copied into new Hlsm object
        */
        Hlsm(Graph * g);
        /** @brief Adds a state
        */
        void add_state(std::string state_name, int index, state_t * previous, std::string cond, std::string logic, bool is_else);
        /** @brief Generates the states
        */
        void generate_states(void);
        /** @brief ??
        */
        void check_assignments(void);
        /** @brief For use in if construct (not implemented)
        */
        void split_edge(edge_t * edge);

};
/** @brief Converts comp_t type to std:string verilog operator (+/- etc)
*/
std::string comp_to_op(comp_t comp);

#endif