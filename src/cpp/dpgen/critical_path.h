#ifndef CRITICAL_PATH_H
#define CRITICAL_PATH_H


#include "data_list.h"
#include "data_type.h"

int TopSort(data_list Graph, data_list List, data_type vertex);

int TopSortVisit(data_list Graph, data_list List, data_type uVertex);

int LongestPath(data_list Graph);


#endif
