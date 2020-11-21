#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "parse.h"
#include "path.h"
#include "scheduling.h"

int main(int argc, char * argv[]){
    if(argc!=4){
        fprintf(stderr,"Usage ./hlysn <inputfile> <cyleLatency> <outputfile>\n");
        exit(EXIT_FAILURE);
    }
    std::string input_filename(argv[1]);
    int latency = atoi(argv[2]); //TODO error checking
    std::string output_filename(argv[3]);
    Graph g;
    g.inop.name = "inop";
    g.onop.name = "onop";
    parse(input_filename, &g);
    //asap(&g);
    //alap(&g,latency);
    fds(&g, latency);
    std::ofstream outfile(output_filename, std::ios::out);
    outfile << g.scheduled_graph_toString();
}