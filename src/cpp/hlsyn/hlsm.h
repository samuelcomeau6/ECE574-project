#ifndef HLSM_H
#define HLSM_H
#include "graph.h"

class Hlsm{
    public:
        Graph graph;
        Hlsm(Graph * g);
        void check_assignments(void);
        void split_edge(edge_t * edge);

};

#endif