#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "parse.h"
#include "path.h"

int main(int argc, char * argv[]){
    if(argc!=3){
        fprintf(stderr,"Usage ./hlysn <inputfile> <outputfile>\n");
        exit(EXIT_FAILURE);
    }
    std::string input_filename(argv[1]);
    std::string output_filename(argv[2]);
    graph_t graph;
    graph.inop.name = "inop";
    graph.onop.name = "onop";
    parse(input_filename, &graph);
}