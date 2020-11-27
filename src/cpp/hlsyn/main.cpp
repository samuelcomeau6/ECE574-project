#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "parse.h"
#include "path.h"
#include "scheduling.h"
#include "verilog.h"

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
    Graph g_asap(g);
    asap(&g_asap);
    Graph g_alap(g);
    alap(&g_alap,latency);
    fds(&g, latency);
    if(output_filename == "-fds"){
        std::cout << g.scheduled_graph_toString();
    } else if(output_filename == "-alap"){
        std::cout << g_alap.scheduled_graph_toString();
    } else if(output_filename == "-asap"){
        std::cout << g_asap.scheduled_graph_toString();
    } else {
        Hlsm h(&g);
        print_verilog(output_filename, &h);
    }
}