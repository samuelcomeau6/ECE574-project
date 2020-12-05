#ifndef PARSE_H
#define PARSE_H
#include <string>
#include <fstream>
#include "path.h"
/** @file
*/

/** @brief Gets a line from the input file
*/
std::string get_line(std::ifstream * file);
/** @brief Parses the line from input file and calls path function
*/
std::string parse_line(std::string line, Graph * list);
/** @brief Closes file
*/
void close(std::ifstream * file);
/** @brief Calls get_line() and parse_line() to parse input file
*/
void parse(std::string filename, Graph * list);
#endif
