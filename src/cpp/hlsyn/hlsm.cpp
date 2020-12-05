#include "graph.h"
#include "hlsm.h"

Hlsm::Hlsm(Graph * g){
    graph = Graph(*g);
    for(int i=0;i<graph.edges.size();++i){
        if(graph.edges[i]->type == INPUT) graph.edges[i]->from = &graph.inop;
        if(graph.edges[i]->type == OUTPUT) graph.edges[i]->from = &graph.onop;

    }
}
void Hlsm::add_state(std::string state_name, int index, state_t * previous, std::string cond, std::string logic, bool is_else){
    state_t * temp_obj = new state_t;
    temp_obj->name = state_name;
    temp_obj->index = index;
    temp_obj->prev = previous;
    temp_obj->true_state = NULL;
    temp_obj->else_state = NULL;
    temp_obj->is_else_state = is_else;
    temp_obj->condition = cond;
    temp_obj->body = logic;
    this->states.push_back(temp_obj);
}
void Hlsm::generate_states(){
    std::string name = "WAIT";
    int index = 0;
    bool is_else = false;
    std::string cond  = "Start";
    std::string logic = "\t\t\t\t Done <= 0;\n";
    add_state(name, index, NULL, cond, logic, false);
    this->states.back()->else_state = this->states.back();
    int t=0;
    while(t<this->graph.onop.start_time-1){
        ++t;
        index = this->states.size();
        name = "T" + std::to_string(t) + "i" + std::to_string(index);
        logic = "";
        cond = "true";
        for(int i=0;i<this->graph.nodes.size();++i){
            node_t * node = this->graph.nodes[i];
            if(node->start_time == t){
                if(node->type == MUX2X1){
                    logic += "\t\t\t\t" + node->output->name + " <= " + node->select->name + " ? ";
                    logic += node->input_1->name + " : " + node->input_2->name + ";\n";
                } else {
                    logic += "\t\t\t\t" + node->output->name + " <= ";
                    logic += node->input_1->name + " " + comp_to_op(node->type) + " " + node->input_2->name  + ";\n";
                }
            }
        }
        add_state(name, index, this->states.back(), cond, logic, is_else);
    }
    index = this->states.size();
    name = "FINAL";
    cond = "true";
    logic = "\t\t\t\tDone <= 1'd1;\n";
    add_state(name, index, this->states.back(), cond, logic, false);
    this->states.back()->true_state = this->states[0];
    for(int i=this->states.size()-1;i>0;--i){
        state_t * state = this->states[i];
        if(!state->is_else_state) {
            state->prev->true_state = state;
        } else {
            state->prev->else_state = state;
        }
    }
}
std::string comp_to_op(comp_t comp){
    std::string output;
    switch (comp) {
        case ADD:     output = "+"; break;
        case SUB:     output = "-"; break;
        case MUL:     output = "*"; break;
        case COMPLT:  output = "<"; break;
        case COMPEQ:  output = "=="; break;
        case COMPGT:  output = ">"; break;
        case COMPLTE: output = "<="; break;
        case COMPGTE: output = ">="; break;
        case MUX2X1:  output = "?"; break;
        case SHR:     output = ">>"; break;
        case SHL:     output = "<<"; break;
        case DIV:     output = "/"; break;
        case MOD:     output = "%"; break;
        case INC:     output = "++"; break;
        case DEC:     output = "--"; break;
        default:
            fprintf(stderr, "Could not convert %s into a proper module\n",comp_toString(comp).c_str());
            exit(EXIT_FAILURE);
            break;
    }
    return output;
}

void Hlsm::check_assignments(){
    for(int i=0;i<this->graph.nodes.size();++i){
        node_t * node = this->graph.nodes[i];
        if(node->type != VAR && node->output->type != WIRE){
            this->split_edge(node->output);
        }

    }
}
void Hlsm::split_edge(edge_t * edge){
    std::string new_name = edge->name;
    this->graph.add_edge(VAR, new_name, edge->width, edge->is_signed);
    edge_t * new_edge = this->graph.edges.back();
    node_t * temp_obj = new node_t;
    temp_obj->name           = edge->name + "R" + std::to_string(this->graph.nodes.size());
    temp_obj->input_1        = edge;
    temp_obj->output         = new_edge;
    temp_obj->type           = VAR;
    temp_obj->is_signed      = edge->is_signed;
    temp_obj->width          = edge->width;
    temp_obj->duration       = 0;
	temp_obj->color 		 = "White";
    this->graph.nodes.push_back(temp_obj);
    node_t * node = this->graph.nodes.back();
    new_edge->to = edge->to;
    if(new_edge->to->input_1 == edge) new_edge->to->input_1 = new_edge;
    if(new_edge->to->input_2 == edge) new_edge->to->input_2 = new_edge;
    if(new_edge->to->select == edge) new_edge->to->select = new_edge;
    edge->to = node;
    new_edge->from = node;
    if(edge->type == VAR){
        edge->type = WIRE;
        edge->name = new_edge->name + "w";
    }
    if(edge->type == OUTPUT){
        edge->type = WIRE;
        edge->name = new_edge->name + "w";
        new_edge->type = OUTPUT;
    }
}
