#include "graph.h"
#include "scheduling.h"
void fds(Graph * graph, int latency){
    bool unscheduled_nodes=true;
    while(unscheduled_nodes){
        bool unscheduled_nodes=false;
        compute_timeframe(graph, latency);
        compute_probability(graph, latency);
        compute_type_dist(graph, latency);
        compute_forces(graph);
        //schedule node with least force update timeframe
    }
}
void compute_timeframe(Graph * graph, int latency){
    //make copies
    Graph g_asap(*graph);
    Graph g_alap(*graph);
    //Compute asap
    asap(&g_asap);
    //Compute alap
    alap(&g_alap, latency);
    for(int i=0;i<graph->nodes.size();++i){
        if(graph->nodes[i]->color!="scheduled"){
            //Time frame is [asap, alap]
            graph->nodes[i]->interval[0] = g_asap.nodes[i]->start_time;
            graph->nodes[i]->interval[1] = g_alap.nodes[i]->start_time;
        }
    }
}
void compute_probability(Graph * graph, int end){
    for(int i=0;i<graph->nodes.size();++i){
        node_t * node = graph->nodes[i];
        node->prb.resize(end);
        for(int t=0;t<=end;++t){
            //if t is outside time frame prb=0
            if(t<node->interval[0] || t>node->interval[1]){
                node->prb[t] = 0.0;
            }
            //else prb=1/(width timeframe)
            else {
                int width=node->interval[1] - node->interval[0] + 1;
                node->prb[t] = 1.0/width;
            }
        }
    }
}
void compute_type_dist(Graph * graph, int end){
    graph->q.resize(end);
    //for each node, v
    for(int i=0;i<graph->nodes.size();++i){
        node_t * node = graph->nodes[i];
        //if type=k qk(t)=qk(t)+v.prb(t)
        for(int t=0;t<end;++t){
            int k = get_bin(node->type);
            graph->q[k][t] = graph->q[k][t] + node->prb[t];
        }
    }
}
int get_bin(comp_t type){
    int k=0;
    switch(type){
        case MUL:
            k=1;
            break;
        case MOD:
        case DIV:
            k=2;
            break;
        case ADD:
        case SUB:
            k=3;
            break;
    }
    return k;
}
void compute_forces(Graph * graph){
    //x(i)=kdelta(i-t)-v.prob
    //v.force(i)=qk(t)*x(i)
    //v.selfforce = sigma( v.force(i), intervalStart, intervalEnd)
    //pred_suc force = sum of forces of implictly scheduled
    //total forces=self_force+pred_suc force
}
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

