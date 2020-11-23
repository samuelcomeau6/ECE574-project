#include "graph.h"
#include "hlsm.h"

Hlsm::Hlsm(Graph * g){
    Graph new_g(*g);
    graph = new_g;
}