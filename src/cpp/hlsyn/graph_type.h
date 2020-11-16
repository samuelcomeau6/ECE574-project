
#ifndef GRAPH_TYPE_H
#define GRAPH_TYPE_H

#include "data_type.h"
#include <vector>


typedef struct
{
	int count;
	data_t inop;
	data_t onop;
	std::vector<data_t> data_v;

} graph_t;


#endif