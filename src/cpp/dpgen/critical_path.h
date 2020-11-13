#ifndef CRITICAL_PATH_H
#define CRITICAL_PATH_H

#include <string>
#include "data_list.h"
#include "data_type.h"

void TopSort(data_list Graph, data_list * List, data_type vertex);

void TopSortVisit(data_list Graph, data_list * List, data_type uVertex);

bool nodeCompare(data_type graphNode, data_type listNode);

float LongestPath(data_list Graph);

void assignDuration(data_list * Graph);

#endif
