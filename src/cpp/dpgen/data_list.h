
#ifndef DATA_LIST_H
#define DATA_LIST_H

#include "data_type.h"
#include <vector>


typedef struct
{
	int count;
	std::vector<data_type> data_v;

} data_list;


#endif