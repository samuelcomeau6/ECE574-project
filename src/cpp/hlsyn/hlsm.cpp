#include "graph.h"
#include "hlsm.h"

Hlsm::Hlsm(Graph * g){
    graph = Graph(*g);
    for(int i=0;i<graph.edges.size();++i){
        if(graph.edges[i]->type == INPUT) graph.edges[i]->from = &graph.inop;
        if(graph.edges[i]->type == OUTPUT) graph.edges[i]->from = &graph.onop;

    }
}