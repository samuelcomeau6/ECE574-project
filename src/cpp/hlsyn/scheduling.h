#include "graph.h"

#ifndef SCHEDULE_H
#define SCHEDULE_H
void alap(Graph * graph,int latency);
void asap(Graph * graph);
bool is_schedulable(node_t * node, int t);
#endif
