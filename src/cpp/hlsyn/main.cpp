#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "graph_type.h"
#include "data_type.h"
#include "parse.h"
#include "path.h"

int main(int argc, char * argv[]){
    if(argc!=2){
        fprintf(stderr,"Usage ./hlysn <inputfile> <outputfile>");
        exit(EXIT_FAILURE);
    }
    std::string input_filename(argv[1]);
    std::string output_filename(argv[2]);
    std::cout << input_filename << output_filename;
}