#ifndef HLSM_H
#define HLSM_H
#include "graph.h"

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
typedef struct state_struct state_t;

class Hlsm{
    public:
        Graph graph;
        std::vector<state_t *> states;
        Hlsm(Graph * g);
        void add_state(std::string state_name, int index, state_t * previous, std::string cond, std::string logic, bool is_else);
        void generate_states(void);
        void check_assignments(void);
        void split_edge(edge_t * edge);

};
std::string comp_to_op(comp_t comp);

#endif