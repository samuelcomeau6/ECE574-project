/*
    parse.cpp

    This is the circuit parser for ece574 project assignment2 u of arizona.

    Created by Samuel Comeau

    Input:
        a file of c like statements with the following conventions:

        -all empty lines are ignored
        -all lines beginning with "//" are ignored
        -netlist file is fully space/tab delimited
        -circuit input and outputs are declared on a line using:
            input datatType inputName1, inputName2
            output dataType outputName1, outputName2
        -valid datatType:
            Int1,Int2,Int8,Int32,Int64
            Uint1,
        -all outputs are implicitly associated with a register component
        -interal registers are explicityly declared:
            register dataType regName1, regName2
        -wires are explicitly declared:
            wire dataType wireName1, wireName2
        -width of components should be determined by the size of the output
        -signed integer inputs should be sign extended
        -unsigned integer inputs should be 0 padded
        -width of comparators should be deteremined by the size of the largest input
        -assignment to a register is input to register
        -operations on  a register use the register output
        -all names should be unique
        -all names are case sensitive
        -input, output, wires, reg declarations should come before components
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "parse.h"
#include "path.h"

using namespace std;
#define TEN_WORD_REGEX "(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?"\
                       "(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?"\
                       "(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?"\
                       "(?:,\\W+(\\w+))?"


namespace parse{
    /* open_netlist
        Recieves the name of an input file as a string and appropriately opens it
    */
    ifstream open_netlist(std::string filename){
        ifstream netlist(filename, std::ios::in);
        if(!netlist.is_open()){
            cout << "error" << "\n";
        }
        return netlist;
    }

    /* get_line
        Recieves an opened netlist file and returns the next line as a string
    */
    std::string get_line(ifstream * file){
        std::string nextline;
        getline(*file, nextline);
        return nextline;
    }


    /* parse_line
    */
    std::string parse_line(string line){
        int data_width;
        bool data_signed;
        comp_t component;
        //Check for data types
        std::regex data_regex("(input|output|register|wire)"
                               "\\W+?(Int|UInt)(\\d+)\\W+(\\w+)"
                               TEN_WORD_REGEX,
                               std::regex_constants::ECMAScript);
        std::smatch matches;
        if(std::regex_search(line, matches, data_regex)){
            if(matches[1]=="input") component=INPUT;
            if(matches[1]=="output") component=OUTPUT;
            if(matches[1]=="register") component=REG;
            if(matches[1]=="wire") component=WIRE;

            if(matches[2]=="Int") data_signed=0;
            if(matches[2]=="Uint") data_signed=1;
            data_width = stoi(matches[3]);

            for (size_t i = 4; i < matches.size(); ++i){
                if(matches[i]!=""){
                    path::add_data(component, matches[i], data_width, data_signed);
                }
            }
       }
       //Check for binary operators
       std::regex biop_regex("(\\w+)\\W*=\\W*(\\w+)\\W*"
                           "(\\+|-|\\*|\\/|%|<<|>>|<|==|>|<=|>=)\\W*(\\w+)\\W*",
                           std::regex_constants::ECMAScript);
       if(std::regex_search(line, matches, biop_regex)){
            if(matches[3]=="+") component=ADD;
            if(matches[3]=="-") component=SUB;
            if(matches[3]=="*") component=MUL;
            if(matches[3]=="/") component=DIV;
            if(matches[3]=="%") component=MOD;
            if(matches[3]=="<<") component=SHL;
            if(matches[3]==">>") component=SHR;
            if(matches[3]=="<") component=COMPLT;
            if(matches[3]=="==") component=COMPEQ;
            if(matches[3]==">") component=COMPGT;
            if(matches[3]=="<=") component=COMPLTE;
            if(matches[3]==">=") component=COMPGTE;
            path::add_op(component, matches[2], matches[4], matches[1]);
       }
       //Check for ternary operator
       std::regex triop_regex("(\\w+)\\W*=\\W*(\\w+)\\W*"
                           "\\?\\W*(\\w+)\\W*:\\W*(\\w+)\\W*",
                           std::regex_constants::ECMAScript);
       if(std::regex_search(line, matches, triop_regex)){
            path::add_mux(matches[2],matches[3],matches[4],matches[1]);
       }
       std::regex noop_regex("(\\w+)\\W*=\\W*(\\w+)\\W*$",
                             std::regex_constants::ECMAScript);
       if(std::regex_search(line, matches, noop_regex)){
            path::add_assignment(matches[1], matches[2]);
       }
       return line;
    }

    /* close
        appropriately closes an open file
    */
    void close(ifstream * file){
        file->close();
    }

    /* parse
        implements other functions to return a completed netlist type
    */
    void parse(std::string filename){
        ifstream netlist = open_netlist(filename);
        std::string out;
        while(!netlist.eof()){
            out = parse_line(get_line(&netlist));
            //std::cout << out << std::endl;
        };
        close(&netlist);
    }
}