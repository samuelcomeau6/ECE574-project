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
    int latency = std::stoi(argv[2]);
    std::string output_filename(argv[3]);
    Graph g;
    Hlsm h(&g);
    h.graph.inop.name = "inop";
    h.graph.onop.name = "onop";
    parse(input_filename, &h);
    Graph g_asap(h.graph);
    asap(&g_asap);
    Graph g_alap(h.graph);
    alap(&g_alap,latency);
    fds(&h.graph, latency);
    if(output_filename == "-fds"){
        std::cout << h.graph.scheduled_graph_toString();
    } else if(output_filename == "-alap"){
        std::cout << g_alap.scheduled_graph_toString();
    } else if(output_filename == "-asap"){
        std::cout << g_asap.scheduled_graph_toString();
    } else {
        print_verilog(output_filename, &h);
    }
}