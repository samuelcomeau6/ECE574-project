// parse.h
#include <string>
#include <fstream>
#include "path.h"

#ifndef PARSE_H
#define PARSE_H
std::string get_line(std::ifstream * file);
std::string parse_line(std::string line, Graph * list);
void close(std::ifstream * file);
void parse(std::string filename, Graph * list);
#endif
