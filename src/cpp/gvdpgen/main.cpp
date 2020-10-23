#include <iostream>
#include "main.h"
#include "parse.h"

using namespace std;

int main(int argc, char * argv[]){
    std::cout << "digraph{" << std::endl;
    parse::parse(argv[1]);
    std::cout <<"}"<<std::endl;
}