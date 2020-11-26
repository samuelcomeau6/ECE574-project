#include "graph.h"
#include "hlsm.h"

Hlsm::Hlsm(Graph * g){
    graph = Graph(*g);
    for(int i=0;i<graph.edges.size();++i){
        if(graph.edges[i]->type == INPUT) graph.edges[i]->from = &graph.inop;
        if(graph.edges[i]->type == OUTPUT) graph.edges[i]->from = &graph.onop;

    }
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
    std::string new_name = edge->name + "R";
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
    if(edge->type == VAR) edge->type = WIRE;
    new_edge->from = node;
}