#ifndef CRITICAL_PATH_H
#define CRITICAL_PATH_H

#include "data_list.h"
#include "data_type.h"

void TopSort(data_list, data_list, data_type);

void TopSortVisit(data_list, data_list, data_type);

void LongestPath(data_list);

void assignDuration(data_list);

#endif
