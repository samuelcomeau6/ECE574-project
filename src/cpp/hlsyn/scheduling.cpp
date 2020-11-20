#include "graph.h"
#include "scheduling.h"
void alap(Graph * graph,int latency){
    graph->onop.start_time=latency+1;
    graph->onop.color="scheduled";
    int t=latency;
    bool unscheduled_nodes = true;
    while(unscheduled_nodes && t>0){
        unscheduled_nodes = false;
        for(int i=0;i<graph->nodes.size();++i){
            if(graph->nodes[i]->color!="scheduled"){
                unscheduled_nodes=true;
                if(graph->nodes[i]->output->to->color=="scheduled" && t<=(graph->nodes[i]->output->to->start_time - graph->nodes[i]->duration)){
//                    printf("%d\n",t);
                    graph->nodes[i]->start_time = t;
                    graph->nodes[i]->color = "scheduled";
                }
            }
        }
        --t;
    }
}
void asap(Graph * graph){
    graph->inop.color="scheduled";
    bool unscheduled_nodes = true;
    int t=1;
    while(unscheduled_nodes){
        unscheduled_nodes=false;
        for(int i=0;i<graph->nodes.size();++i){
            if(graph->nodes[i]->color!="scheduled"){
                unscheduled_nodes=true;
                if(is_schedulable(graph->nodes[i],t)){
                    graph->nodes[i]->start_time=t;
                    graph->nodes[i]->color="scheduled";
                }
            }
        }
        ++t;
    }
    graph->onop.start_time=t;
}
bool is_schedulable(node_t * node, int t){
    bool input_1_ok=false;
    bool input_2_ok=false;
    bool select_ok=false;
    if(node->type!=MUX2X1){
        select_ok=true;
    }
    else{
        if(node->select->from->color=="scheduled"
           && t>=(node->select->from->start_time+node->select->from->duration)){
            select_ok = true;
        }
    }
    if(node->input_1->from->color=="scheduled"
       && t>=(node->input_1->from->start_time+node->input_1->from->duration)){
        input_1_ok = true;
    }
    if(node->input_2!=NULL){
        if(node->input_2->from->color=="scheduled"
           && t>=(node->input_2->from->start_time+node->input_2->from->duration)){
            input_2_ok=true;
        }
    }
    return (input_1_ok && input_2_ok && select_ok);
}

