#include "graph.h"

#ifndef SCHEDULE_H
#define SCHEDULE_H
#include "graph.h"
#include "scheduling.h"
void fds(Graph * graph, int latency);
void compute_timeframe(Graph * graph, int latency);
void compute_probability(Graph * node, int end);
void compute_type_dist(Graph * graph, int end);
int get_bin(comp_t type);
void compute_forces(Graph * graph, int latency);
void alap(Graph * graph,int latency);
void asap(Graph * graph);
bool alap_schedulable(Graph * graph, int index, int t);
bool is_schedulable(node_t * node, int t);
bool schedule_min_force(Graph * graph, int end);
float get_pred_force(node_t * node, int t);
float get_suc_force(Graph * graph, node_t * node, int t);
#endif
