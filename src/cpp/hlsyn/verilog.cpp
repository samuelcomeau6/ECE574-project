#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <cmath>

#include "verilog.h"
#include "v_template.h"
#include "hlsm.h"

void print_verilog(std::string output_filename, Hlsm * h){
//    h->check_assignments();
    h->generate_states();
    std::ofstream outfile(output_filename, std::ios::out);
    outfile << header;
    outfile << "module HLSM (" << std::endl;
    outfile << "\tinput Clk, Rst, Start,\n";
    outfile << "\toutput reg Done,\n";
    outfile << print_inputs(h);
    outfile << print_outputs(h);
    outfile << ");" << std::endl;
    outfile << print_wires(h);
    outfile << print_vars(h);
    outfile << print_state_def(h);
//    outfile << print_modules(h);
//    outfile << print_assignment(h);
    outfile << print_states(h);
    outfile << "\nendmodule\n" << std::endl;
    outfile << footer;
}
std::string print_state_def(Hlsm * h){
    int size = h->states.size();
    int bits = static_cast<int>(std::log2(size))+1;
    std::string out = "\treg [" + std::to_string(bits-1) + ":0] state;\n";
    for(int i=0;i<size;++i){
        out += "\tlocalparam " + h->states[i]->name + " = ";
        out += std::to_string(bits) + "'d" + std::to_string(i) + ";\n";
    }
    return out;
}
std::string print_states(Hlsm * h){
    std::string out = "\talways @(posedge Clk) begin\n";
    out += "\t\tcase (state)\n";
    for(int i=0;i<h->states.size();++i){
        state_t * state = h->states[i];
        out += "\t\t\t" + state->name + ": begin\n";
        out += state->body;
        if(state->condition=="true"){
            out += "\t\t\t\tstate <= ";
            if(state->true_state!=NULL) out += state->true_state->name;
            out += ";\n";
        } else {
            out += "\t\t\t\tif (" +  state->condition + ") state <=";
            if(state->true_state!=NULL) out += state->true_state->name;
            out += ";\n";
            if(state->else_state != NULL) {
                out += "\t\t\t\telse state <= ";
                out += state->else_state->name;
                out += ";\n";
            }
        }
        out += "\t\t\tend\n";
    }
    out += "\t\tendcase\n";
    out += "\tend\n";
    return out;
}
std::string parse_module_name(std::string filename){
    std::regex path_regex("^\\.?.*?(.*?)\\..*$",
                           std::regex_constants::ECMAScript);
    std::smatch matches;
    std::regex_search(filename, matches, path_regex);

    return matches[1];
}
std::string print_vars(Hlsm *h){
    std::string out;
    for(int i=0;i<h->graph.edges.size();++i){
        edge_t * edge = h->graph.edges[i];
        if(edge->type == VAR && !edge->is_copy){
            out = out +"\treg ";
            if(edge->width > 1){
                if(edge->is_signed) out += "signed";
                out += "[" + std::to_string(edge->width - 1);
                out += ":0] " + edge->name + ";\n";
            } else {
                out += edge->name;
                out+= ";\n";
            }
        }
    }
    return out;
}
std::string print_assignment(Hlsm *h){
    std::string out;
    out = "\talways @(posedge Clk) begin\n";
    for(int i=0;i<h->graph.nodes.size();++i){
        node_t * node = h->graph.nodes[i];
        if(node->type == VAR){
            out += "\t\t";
            out += node->output->name;
            out += "<=";
            out += node->input_1->name;
            out += ";\n";
        }
    }
    out += "\tend\n";
    return out;
}

std::string print_wires(Hlsm *h){
    std::string out;
    for(int i=0;i<h->graph.edges.size();++i){
        edge_t * edge = h->graph.edges[i];
        if(edge->type == WIRE && !edge->is_copy){
            out = out +"\twire ";
            if(edge->width > 1){
                if(edge->is_signed) out += "signed";
                out += "[" + std::to_string(edge->width - 1);
                out += ":0] " + edge->name + ";\n";
            } else {
                out += edge->name;
                out+= ";\n";
            }
        }
    }
    return out;
}
std::string print_inputs(Hlsm * h){
    std::string out;
    for(int i=0;i<h->graph.edges.size();++i){
        edge_t * edge = h->graph.edges[i];
        if(edge->type == INPUT && !edge->is_copy){
            out = out + "\tinput ";
            if(edge->width > 1){
                if(edge->is_signed) out = out + "signed ";
                out = out + "[" + std::to_string(edge->width - 1);
                out = out + ":0] " + edge->name + ",\n";
            } else {
                out += edge->name;
                out += ",\n";
            }
        }
    }
    return out;
}
std::string print_outputs(Hlsm * h){
    std::string out;
    for(int i=0;i<h->graph.edges.size();++i){
        edge_t * edge = h->graph.edges[i];
        if(edge->type == OUTPUT && !edge->is_copy){
            out = out + "\toutput reg ";
            if(edge->width > 1){
                if(edge->is_signed) out = out + "signed ";
                out = out + "[" + std::to_string(edge->width - 1);
                out = out + ":0] " + edge->name;
            } else {
                out += edge->name;
                out += ",\n";
            }
            out += ",\n";
        }
    }
    out.erase(out.end()-2,out.end());
    out += "\n";
    return out;
}
std::string print_modules(Hlsm * h){
    std::string out;
    for(int i=0;i<h->graph.nodes.size();++i){
        node_t * node = h->graph.nodes[i];
        if(node->type != VAR) out = out + node_to_V(*node);
    }
    return out;
}
std::string node_to_V(node_t node){
    std::string output;
    output += "\t";
    if(node.is_signed) output = output + "S";
    output += type_to_V(node.type);
    output += " #(.DATAWIDTH(" + std::to_string(node.width) + ")) ";
    if(node.is_signed) output = output + "s_";
    else output = output + "u_";
    output += node.name;
    output += " (";
    switch(node.type){
        case REG:
            output += sign_extend(node.input_1, node.width, node.is_signed) + ", Clk, Rst, q";
            break;
        case ADD:
        case SUB:
        case MUL:
        case DIV:
        case MOD:
            output += sign_extend(node.input_1, node.width, node.is_signed) + ", ";
            output += sign_extend(node.input_2, node.width, node.is_signed) + ", ";
            output += node.output->name;
            break;
        case SHR:
        case SHL:
            output += sign_extend(node.input_1, node.width, node.is_signed) + ", ";
            output += node.input_2->name + ", ";
            output += node.output->name;
            break;
        case MUX2X1:
            output += sign_extend(node.input_1, node.width, node.is_signed) + ", ";
            output += sign_extend(node.input_2, node.width, node.is_signed) + ", ";
            output += sign_extend(node.select, 1, false) + ", ";
            output += node.output->name;
            break;
        case COMPLT:
            output += ".a(" +sign_extend(node.input_1, node.width, node.is_signed) + "), ";
            output += ".b(" + sign_extend(node.input_2, node.width, node.is_signed) + "), ";
            output += ".lt(" + node.output->name + ")";
            break;
        case COMPEQ:
            output += ".a(" +sign_extend(node.input_1, node.width, node.is_signed) + "), ";
            output += ".b(" + sign_extend(node.input_2, node.width, node.is_signed) + "), ";
            output += ".eq(" + node.output->name + ")";
            break;
        case COMPGT:
            output += ".a(" +sign_extend(node.input_1, node.width, node.is_signed) + "), ";
            output += ".b(" + sign_extend(node.input_2, node.width, node.is_signed) + "), ";
            output += ".gt(" + sign_extend(node.output, 1, false) + ")";
            break;
        default:
            fprintf(stderr, " Could not convert %s into a proper module\n",node.name.c_str());
            exit(EXIT_FAILURE);
            break;
    }
    output += ");\n";
    return output;
}
std::string type_to_V(comp_t comp){
    std::string output;
    switch (comp) {
        case REG:     output = "REG"; break;
        case ADD:     output = "ADD"; break;
        case SUB:     output = "SUB"; break;
        case MUL:     output = "MUL"; break;
        case COMPLT:  output = "COMP"; break;
        case COMPEQ:  output = "COMP"; break;
        case COMPGT:  output = "COMP"; break;
        case COMPLTE: output = "COMP"; break;
        case COMPGTE: output = "COMP"; break;
        case MUX2X1:  output = "MUX2x1"; break;
        case SHR:     output = "SHR"; break;
        case SHL:     output = "SHL"; break;
        case DIV:     output = "DIV"; break;
        case MOD:     output = "MOD"; break;
        case INC:     output = "INC"; break;
        case DEC:     output = "DEC"; break;
        default:
            fprintf(stderr, "Could not convert %s into a proper module\n",comp_toString(comp).c_str());
            exit(EXIT_FAILURE);
            break;
    }
    return output;
}
std::string sign_extend(edge_t * edge, int datawidth, bool is_signed){
    std::string output;
    if(edge->width == datawidth){
        if(edge->is_signed == is_signed){
            return edge->name;
        } else if(!edge->is_signed) {
            output = "{1'd0," + edge->name + " [" + std::to_string(edge->width-2) + ":0]}";
            return output;
        } else {
            output = edge->name + "[" + std::to_string(edge->width-1) + ":0]";
            return output;
        }
    }
    if(edge->width > datawidth){
        //Truncate
        if(edge->is_signed && is_signed){
            //Keep sign
            output  = "{" +edge->name + "[" + std::to_string(edge->width-1) +"]," + edge->name;
            output += "[" + std::to_string(datawidth) + ":0]" +"}";
        } else {
            output = edge->name + "[" + std::to_string(datawidth-1) + ":0]";
        }
    }
    if(edge->width < datawidth){
        //Extend
        if(edge->is_signed && is_signed){
            output = "{{" + std::to_string(datawidth - edge->width) + "{" + edge->name + "[" + std::to_string(edge->width - 1);
            output += "]}}, " + edge->name + "}";
        } else {
            output = "{{" + std::to_string(datawidth - edge->width) + "{1'd0}}, " + edge->name +"}";
        }
    }
    return output;
}