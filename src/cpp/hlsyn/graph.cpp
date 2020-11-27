#include "graph.h"
#include <string>
#include <iostream>
Graph::Graph(){
    this->inop.name = "inop";
    this->inop.duration     = 0;
    this->inop.start_time   = 0;
    this->onop.name = "onop";
    this->onop.duration = 0;
    this->onop.start_time=0;
}
Graph::Graph(const Graph &g){
    this->inop.name = "inop";
    this->inop.duration     = g.inop.duration;
    this->inop.start_time   = g.inop.start_time;
    this->onop.name = "onop";
    this->onop.duration = g.onop.duration;
    this->onop.start_time=g.onop.start_time;
    for(int i=0;i<g.edges.size();++i){
        edge_t * edge = g.edges[i];
        edge_t * temp_obj = new edge_t;
        temp_obj->name = edge->name;
        node_t * from_node = NULL;
        if(edge->from->name == "inop") from_node = &this->inop;
        else{
            for(int j=0;j<i;++j){
                if(edge->from->name == this->edges[j]->from->name){
                    from_node = edges[j]->from;
                }
                if(edge->from->name == this->edges[j]->to->name){
                    from_node = edges[j]->to;
                }
            }
        }
        if(from_node == NULL) from_node = new node_t;
        temp_obj->from = from_node;
        from_node->name = edge->from->name;
        node_t * to_node = NULL;
        if(edge->to->name == "onop") to_node = &this->onop;
        else{
            for(int j=0;j<i;++j){
                if(edge->to->name == this->edges[j]->from->name){
                    to_node = edges[j]->from;
                }
                if(edge->to->name == this->edges[j]->to->name){
                    to_node = edges[j]->to;
                }

             }
        }
        if(to_node == NULL) to_node = new node_t;
        temp_obj->to = to_node;
        to_node->name = edge->to->name;
        temp_obj->type = edge->type;
        temp_obj->is_signed = edge->is_signed;
        temp_obj->width = edge->width;
        temp_obj->duration = edge->duration;
        temp_obj->color = "White";
        temp_obj->is_copy = edge->is_copy;
        this->edges.push_back(temp_obj);
    }
    for(int i=0;i<g.nodes.size();++i){
        node_t * node = g.nodes[i];
        node_t * new_node=NULL;
        for(int j=0;j<this->edges.size();++j){
            if(this->edges[j]->from->name == node->name){
                new_node = this->edges[j]->from;
            }
            if(this->edges[j]->to->name == node->name){
                new_node = this->edges[j]->to;
            }
        }
        
        edge_t * in1=NULL;
        edge_t * in2=NULL;
        edge_t * sel=NULL;
        edge_t * out=NULL;
        for(int j=0;j<this->edges.size();++j){
            edge_t * edge = this->edges[j];
            if(node->input_1->name == edge->name) in1=edge;
            if(node->input_2->name == edge->name) in2=edge;
            if(node->type==MUX2X1){
                    if(node->select->name == edge->name) sel=edge;
            }
            if(node->output->name == edge->name) out=edge;
        }
        new_node->input_1 = in1;
        new_node->input_2 = in2;
        new_node->select  = sel;
        new_node->output  = out;
        new_node->type    = node->type;
        new_node->is_signed = node->is_signed;
        new_node->width     = node->width;
        new_node->duration  = node->duration;
        new_node->start_time = node->start_time;
        new_node->interval[0] = node->interval[0];
        new_node->interval[1] = node->interval[1];
        new_node->color     = node->color;
        this->nodes.push_back(new_node);
    }
    /*for(int i=0;i<g.edges.size();++i){
        edge_t * edge = g.edges[i];
        bool duplicate=false;
        for(int j=0;j<i;++j){
            if(edge->name == g.edges[j]->name && i!=j){
                duplicate=true;
            }
        }
            this->add_edge(edge->type, edge->name, edge->width, edge->is_signed);
            this->edges.back()->is_copy = duplicate;
    }
    for(int i=0;i<g.nodes.size();++i){
        node_t * node = g.nodes[i];
        std::string select = "";
        if(node->type == MUX2X1){
            select = node->select->name;
        }
        if(node->type == IF || node->type == REG) {
            /*this->add_if(node->input_1->name);
            this->node->output =
            this->add_node(node->type, node->input_1->name, "", select, node->output->name);
        }
        else this->add_node(node->type, node->input_1->name, node->input_2->name, select, node->output->name);
        this->nodes[i]->color = node->color;
        this->nodes[i]->start_time = node->start_time;
    }*/
}

std::string comp_toString(comp_t component) {
    std::string output;

    switch (component) {
    case REG:     output = "REG"; break;
    case ADD:     output = "ADD"; break;
    case SUB:     output = "SUB"; break;
    case MUL:     output = "MUL"; break;
    case COMPLT:  output = "COMPLT"; break;
    case COMPEQ:  output = "COMPEQ"; break;
    case COMPGT:  output = "COMPGT"; break;
    case COMPLTE: output = "COMPLTE"; break;
    case COMPGTE: output = "COMPGTE"; break;
    case MUX2X1:  output = "MUX2x1"; break;
    case SHR:     output = "SHR"; break;
    case SHL:     output = "SHL"; break;
    case DIV:     output = "DIV"; break;
    case MOD:     output = "MOD"; break;
    case INC:     output = "INC"; break;
    case DEC:     output = "DEC"; break;
    case INPUT:   output = "INPUT"; break;
    case OUTPUT:  output = "OUTPUT"; break;
    case WIRE:    output = "WIRE"; break;
    case VAR:    output = "VAR"; break;
    case IF:     output = "IF"; break;
    default:      output = "ERROR"; break;
    }
    return output;
}

node_t * Graph::add_node(comp_t component_type, std::string input1_name, std::string input2_name, std::string select, std::string output_name){
    bool is_signed = 0;
    int data_width = 0;

    node_t * temp_obj = new node_t;
    temp_obj->name           = comp_toString(component_type)+std::to_string(this->nodes.size());
    temp_obj->input_1        = edge_search(this, input1_name, false);
    if(component_type != REG && component_type != IF) temp_obj->input_2        = edge_search(this, input2_name, false);
    temp_obj->output         = edge_search(this, output_name, true);
    if(component_type == MUX2X1) {temp_obj->select         = edge_search(this, select, false);}
    else {temp_obj->select = NULL;}
    temp_obj->type           = component_type;
    temp_obj->is_signed      = (temp_obj->input_1->is_signed
                               ||temp_obj->input_2->is_signed
                               ||temp_obj->output->is_signed);
    temp_obj->width          = temp_obj->output->width;
    temp_obj->duration       = get_duration(component_type,temp_obj->width);
    temp_obj->start_time    =0;
	temp_obj->color 		    = "White";
    this->nodes.push_back(temp_obj);
    node_t * this_node = this->nodes.back();
    if(this_node->input_1->to == NULL){
        this_node->input_1->to = this_node;
    }
    if(component_type != REG && component_type != IF){
        if(this_node->input_2->to == NULL){
            this_node->input_2->to = this_node;
        }
    }
    if(this_node->output->from == NULL){
        this_node->output->from = this_node;
    }
    if(component_type==MUX2X1 && this_node->select->to == NULL){
        this_node->select->to = this_node;
    }
    return this_node;
}
node_t * Graph::add_if(std::string cond){
    node_t * temp_obj = new node_t;
    temp_obj->name           = comp_toString(IF)+std::to_string(this->nodes.size());
    temp_obj->input_1        = edge_search(this, cond, false);
    temp_obj->input_2 = NULL;
    temp_obj->output = NULL;
    temp_obj->select = NULL;
    temp_obj->type           = IF;
    temp_obj->is_signed      = false;
    temp_obj->width          = 0;
    temp_obj->duration       = 0;
	temp_obj->color 		    = "White";
    this->nodes.push_back(temp_obj);
    node_t * this_node = this->nodes.back();
    if(this_node->input_1->to == NULL){
        this_node->input_1->to = this_node;
    }
    return this_node;

}
edge_t * Graph::add_edge(comp_t component_type, std::string name, int data_width, bool is_signed){

    edge_t * temp_obj = new edge_t;
    temp_obj->name           = name;
    if(component_type==INPUT) temp_obj->from = &(this->inop);
    else temp_obj->from        = NULL;
    if(component_type==OUTPUT || component_type == THEN || component_type == ELSE) temp_obj->to = &(this->onop);
    else temp_obj->to         = NULL;
    temp_obj->type           = component_type;
    temp_obj->is_signed      = is_signed;
    temp_obj->width          = data_width;
	temp_obj->color 		    = "White";
	temp_obj->is_copy       = false;

    this->edges.push_back(temp_obj);
    return this->edges.back();
}
edge_t * Graph::add_edge(comp_t component_type, std::string name, node_t * from, node_t * to, int data_width, bool is_signed){
    edge_t * temp_obj = new edge_t;
    temp_obj->name           = name;
    temp_obj->from           = from;
    temp_obj->to             = to;
    temp_obj->type           = component_type;
    temp_obj->is_signed      = is_signed;
    temp_obj->width          = data_width;
	temp_obj->color 		 = "White";
	temp_obj->is_copy        = false;

    this->edges.push_back(temp_obj);
    return this->edges.back();
}

int max(int a, int b, int c){
    int out=a;
    out = (b>out) ? b : out;
    out = (c>out) ? c : out;
    return out;
}

std::string Graph::start_graph_toString(void){
    std::string out = "digraph{\nrankdir=TB\n";
    out = out + "inop[label = \""+inop.name+"\"]\n";
    out = out + "onop[label = \""+onop.name+"\"]\n";
    for(int i=0;i<this->nodes.size();++i){
         out = out + nodes[i]->name + "[label =\"" + node_toString(*this->nodes[i])+ "t:"
         + std::to_string(this->nodes[i]->start_time)+"+"+std::to_string(this->nodes[i]->duration)+ "\"]\n";
    }
    for(int i=0;i<this->edges.size();++i){
        if(this->edges[i]->from != NULL) out = out + this->edges[i]->from->name;
        else out = out + "NULL";
        out = out + "->";
        if(this->edges[i]->to != NULL) out = out + this->edges[i]->to->name;
        else out = out + "NULL";
        out = out + "[label =\"" + this->edges[i]->name + "\"]\n";
    }
    return out;
}
std::string Graph::graph_toString(void){
    std::string out = this->start_graph_toString() + "}\n";
    return out;
}
std::string Graph::scheduled_graph_toString(void){
    std::string out = this->start_graph_toString();
    for(int t=0;t<this->onop.start_time;++t){
        out = out + std::to_string(t) +"\n" + std::to_string(t) +"->"+ std::to_string(t+1);
        out = out + "\n{rank = same; "+std::to_string(t)+";";
        for(int i=0;i<this->nodes.size();++i){
            if(this->nodes[i]->start_time==t){
                out = out + this->nodes[i]->name +"; ";
            }
        }
        out = out + "}\n";
    }
    out = out + "}\n";
    out = out + "/" + "/" + std::to_string(this->edges.size()) + "edges\n";
    out = out + "/" + "/" + std::to_string(this->nodes.size()) + "nodes\n";
    return out;
}


std::string node_toString(node_t datum){
    std::string out_string = datum.name;
    if(datum.is_signed) out_string = out_string + " S ";
    else out_string = out_string + " U ";
    out_string = out_string + std::to_string(datum.width) + "' ";
    return out_string;
}


std::string edge_toString(edge_t datum){
    std::string out_string = datum.name;
    if(datum.is_signed) out_string = out_string + " signed ";
    else out_string = out_string + " unsigned ";
    out_string = out_string + std::to_string(datum.width) + " bit ";
    out_string = out_string + comp_toString(datum.type);
    out_string = out_string + " From:";
    if(datum.from==NULL) out_string = out_string + "NULL";
    else out_string = out_string + datum.from->name;
    out_string = out_string + " To:";
    if(datum.to==NULL) out_string = out_string + "NULL";
    else out_string = out_string + datum.to->name;
    return out_string;
}
edge_t* edge_search(Graph * list, std::string name,bool is_from){
    bool addable=false;
    int add_index=0;
    for(int i=0;i<=list->edges.size()-1;++i){
        if(list->edges[i]->name == name) {
            if(is_from){
                if(list->edges[i]->from != NULL){
                    if(list->edges[i]->from->type == WIRE){
                        fprintf(stderr,"Signal %s is driven from multiple sources\n",
                                list->edges[i]->name.c_str());
                        exit(EXIT_FAILURE);
                    } else{
                        addable=true;
                        add_index=i;
                    }
                } else {
                    return list->edges[i];
                }
            } else {
                if(list->edges[i]->to!=NULL){
                    addable=true;
                    add_index=i;
                } else {
                    if(list->edges[i]->from == NULL){
                        //Repair copied edge
                        for(int j=0;j<list->edges.size();++j){
                            if(list->edges[j]->name == name && list->edges[j]->from != NULL) {
                                list->edges[i]->from = list->edges[j]->from;
                                list->edges[i]->is_copy = true;
                            }
                        }
                    }
                    return list->edges[i];
                }
            }
        }
    }
    if(addable){
        list->add_edge(list->edges[add_index]->type, list->edges[add_index]->name, list->edges[add_index]->width, list->edges[add_index]->is_signed);
        if(!is_from) list->edges.back()->from = list->edges[add_index]->from;
        if(is_from) list->edges.back()->to = list->edges[add_index]->to;
        list->edges[list->edges.size()-1]->is_copy = true;
        return list->edges[list->edges.size()-1];
    }
    fprintf(stderr,"Failed to locate variable %s\n",
        name.c_str());
    exit(EXIT_FAILURE);
    return NULL;
}
int get_duration(comp_t type, int width){
    switch(type){
        case MUL:
            return 2;
            break;
        case DIV:
        case MOD:
            return 3;
            break;
        default:
            return 1;
            break;
    }
}
void Graph::paint(std::string color){
    for(int i=0;i<this->nodes.size();++i){
        this->nodes[i]->color = color;
    }
    for(int i=0;i<this->edges.size();++i){
        this->edges[i]->color = color;
    }
}