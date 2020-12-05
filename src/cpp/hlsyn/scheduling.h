#ifndef SCHEDULE_H
#define SCHEDULE_H
#include "graph.h"

/**
    @file
    @brief Functions to take a graph and schedule it

    @author Samuel Comeau
    @date December 2020
*/
/** Uses the force-directed scheduling algorithm to schedule graph
    @param graph - pointer to the Graph class object to schedule
    @param latency - the time in integer cycles allowed for the graph to complete
*/
void fds(Graph * graph, int latency);
/** Function called by fds() computes the time frame for all nodes in a graph.
    @param graph - pointer to the Graph object
    @param latency - latency constraint
*/
void compute_timeframe(Graph * graph, int latency);
/** Function called by fds() computes the probability of any node to be scheduled at a particular time
*/
void compute_probability(Graph * node, int end);
/** Function called by fds() computes the probabilty of any time to be scheduled at a particular time
*/
void compute_type_dist(Graph * graph, int end);
/** Function called by fds() gets the name of the bin that a type has been assigned. Bins can accept multiple types
*/
int get_bin(comp_t type);
/** @brief Function called by fds() computes the forces on all nodes at all times
    @param graph - pointer to Graph object
    @param latency - latency constraint
    The self force for a node is given as:
    \f[ SF_{ij} = \sum\limits_{l=t}^{t+\Delta} \f]
*/
void compute_forces(Graph * graph, int latency);
/** @brief Schedules the graph according to the As Late As Possible algorithm
*/
void alap(Graph * graph,int latency);
/** @brief Schedules the graph according to the As Soon As Possible algorithm
*/
void asap(Graph * graph);
/** @brief Determines if the node is schedulable during alap()
*/
bool alap_schedulable(Graph * graph, int index, int t);
/** @brief Determines if the node is schedulable during asap()
*/
bool is_schedulable(node_t * node, int t);
/** @brief Schedules next node during fds()
*/
bool schedule_min_force(Graph * graph, int end);
/** @brief Determines predessor/successor forces during fds()
*/
float get_predsuc_force(Graph * graph, node_t * node, int t);
#endif
