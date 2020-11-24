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
#include <boost/regex.hpp>
#include <stdlib.h>
#include "parse.h"
#include "path.h"

using namespace std;
using namespace boost;
#define TEN_WORD_REGEX "(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?"\
                       "(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?"\
                       "(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?"\
                       "(?:,\\W+(\\w+))?"


namespace parse{
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
        bool data_signed=0;
        comp_t component=ERR;
        //Check for data types
        boost::regex data_regex("(input|output|register|wire)"
                               "\\W+?(Int|UInt)(\\d+)\\W+(\\w+)"
                               TEN_WORD_REGEX);
        std::string::const_iterator start;
        std::string::const_iterator end;
        start = line.begin();
        end = line.end();
        boost::match_results<std::string::const_iterator> matches;
        boost::match_results<std::string::const_iterator> tmatches;
        boost::match_flag_type flags = boost::match_default;
        if(boost::regex_search(start, end, matches, data_regex, flags)){
            if(matches[1]=="input") component=INPUT;
            if(matches[1]=="output") component=OUTPUT;
            if(matches[1]=="register") component=REG;
            if(matches[1]=="wire") component=WIRE;

            if(matches[2]=="Int") data_signed=1;
            if (matches[2] == "UInt") data_signed = 0;
            data_width = stoi(matches[3]);
            if (data_width == 1) data_signed = 0;

            for (size_t i = 4; i < matches.size(); ++i){
                if(matches[i]!=""){
                    path::add_data(component, matches[i], data_width, data_signed);
                }
            }
       }
       //Check for binary operators
       boost::regex biop_regex("(\\w+)\\s*=\\s*(\\w+)\\s*"
                           "([^a-zA-Z0-9_ \\t\\n\\r\\f][=><]?)\\s*(\\w+)\\s*");
        if(boost::regex_search(start, end, matches, biop_regex, flags)){
            component=ERR;
            #ifdef DEBUG
                std::cout << "sign is " << matches[3] << std::endl;
            #endif
            if(matches[3]=="+"){
                if(matches[4]=="1") component=INC;
                else component=ADD;
            }
            if(matches[3]=="-") {
                if(matches[4]=="1") component=DEC;
                else component=SUB;
            }
            if(matches[3]=="*") component=MUL;
            if(matches[3]=="/") component=DIV;
            if(matches[3]=="%") component=MOD;
            if(matches[3]=="<") component=COMPLT;
            if(matches[3]=="<<") component=SHL;
            if(matches[3]==">") component=COMPGT;
            if(matches[3]==">>") component=SHR;
            if(matches[3]=="==") component=COMPEQ;
            //Check for ternary operator
            boost::regex triop_regex("(\\w+)\\s*=\\s*(\\w+)\\s*"
                                   "\\?\\s*(\\w+)\\s*:\\s*(\\w+)\\s*");
            if(boost::regex_search(start, end, tmatches, triop_regex, flags)){
                path::add_mux(tmatches[2],tmatches[3],tmatches[4],tmatches[1]);
            } else {
                if(component!=ERR) path::add_op(component, matches[2], matches[4], matches[1]);
                else{
                    std::cout << "Error" <<endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
       //Check for assignment
       boost::regex noop_regex("(\\w+)\\s*=\\s*(\\w+)\\s*$");
       if(boost::regex_search(start, end, matches, noop_regex, flags)){
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
        ifstream netlist(filename, std::ios::in);
        std::string out;
        while(!netlist.eof()){
            out = parse_line(get_line(&netlist));
            #ifdef DEBUG
                std::cout << out << std::endl;
            #endif
        };
        close(&netlist);
    }
}