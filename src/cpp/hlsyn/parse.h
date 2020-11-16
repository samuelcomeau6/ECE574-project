// parse.h
#include <string>
#include <fstream>
#include "path.h"

#ifndef PARSE_H
#define PARSE_H
std::string get_line(std::ifstream * file);
std::string parse_line(std::string line, graph_t * list);
void close(std::ifstream * file);
void parse(std::string filename, graph_t * list);
#endif
