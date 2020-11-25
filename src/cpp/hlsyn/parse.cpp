/*
parse.cpp

Created by Samuel Comeau
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
#define TEN_WORD_REGEX "(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?"\
                   "(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?"\
                   "(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?(?:,\\W+(\\w+))?"\
                   "(?:,\\W+(\\w+))?"
#define HUNDRED_WORD_REGEX TEN_WORD_REGEX TEN_WORD_REGEX TEN_WORD_REGEX TEN_WORD_REGEX TEN_WORD_REGEX TEN_WORD_REGEX TEN_WORD_REGEX TEN_WORD_REGEX TEN_WORD_REGEX TEN_WORD_REGEX

/* parse_line
*/
std::string parse_line(string line, Graph * list){
    int data_width;
    bool data_signed=0;
    comp_t component=ERR;
    //Check for data types
    boost::regex data_regex("(input|output|variable|wire)"
                           "\\W+?(Int|UInt)(\\d+)\\W+(\\w+)"
                           HUNDRED_WORD_REGEX );
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
        if(matches[1]=="wire") component=VAR;
        if(matches[1]=="variable") component=VAR;

        if(matches[2]=="Int") data_signed=1;
        if (matches[2] == "UInt") data_signed = 0;
        data_width = stoi(matches[3]);
        if (data_width == 1) data_signed = 0;

        for (size_t i = 4; i < matches.size(); ++i){
            if(matches[i]!=""){
                add_data(component, matches[i], data_width, data_signed, list);
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
            add_mux(tmatches[2],tmatches[3],tmatches[4],tmatches[1], list);
        } else {
            if(component!=ERR) add_op(component, matches[2], matches[4], matches[1], list);
            else{
                std::cout << "Error" <<endl;
                exit(EXIT_FAILURE);
            }
        }
    }
   //Check for assignment
   boost::regex noop_regex("(\\w+)\\s*=\\s*(\\w+)\\s*$");
   if(boost::regex_search(start, end, matches, noop_regex, flags)){
        add_assignment(matches[1], matches[2], list);
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
void parse(std::string filename, Graph * list){
    ifstream netlist(filename, std::ios::in);
    if(!netlist.is_open()){
        perror("Could not open input file");
        exit(EXIT_FAILURE);
    }
    std::string out;
    while(!netlist.eof()){
        std::string nextline;
        getline(netlist, nextline);
        out = parse_line(nextline, list);
        #ifdef DEBUG
            std::cout << out << std::endl;
        #endif
    };
    close(&netlist);
}
