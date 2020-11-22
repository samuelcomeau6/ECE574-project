#include "graph.h"
#include "scheduling.h"
#include <iostream>
void fds(Graph * graph, int latency){
    graph->paint("White");
    graph->onop.start_time = latency+1;
    bool unscheduled_nodes=true;
    while(unscheduled_nodes){
        compute_timeframe(graph, latency);
        compute_probability(graph, latency);
        compute_type_dist(graph, latency);
        compute_forces(graph, latency);
        unscheduled_nodes = schedule_min_force(graph, latency);
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
    #ifdef DEBUG
        for(int i=0;i<graph->nodes.size();++i){
            std::cout << "node " << i << " :"  << graph->nodes[i]->name;
            std::cout << " interval:[" << graph->nodes[i]->interval[0] << "," << graph->nodes[i]->interval[1] << "]" << std::endl;
        }
    #endif

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
    graph->q.resize(5);
    for(int i=0;i<graph->q.size();++i){
        graph->q[i].resize(end);
    }
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
void compute_forces(Graph * graph, int end){
    for(int j=0;j<graph->nodes.size();++j){
        node_t * node = graph->nodes[j];
        node->self_force.resize(end);
        node->total_force.resize(end);
        for(int t=node->interval[0];t<=node->interval[1];++t){
            //v.selfforce = sigma( v.force(i), intervalStart, intervalEnd)
            for(int i=node->interval[0];i<=node->interval[1];++i){
                //x(i)=kdelta(i-t)-v.prob
                float kdelta = (i==t)?1.0:0.0;
                float x = (kdelta - node->prb[t]);
                //v.force(i)=qk(t)*x(i)
                node->self_force[t] = node->self_force[t] + graph->q[get_bin(node->type)][i]*x;
            }
        }
    }
    //pred_suc force = sum of forces of implictly scheduled
    //total forces=self_force+pred_suc force
    for(int j=0;j<graph->nodes.size();++j){
        node_t * node = graph->nodes[j];
        for(int t=node->interval[0];t<=node->interval[1];++t){
            node->total_force[t] = node->self_force[t] + get_pred_force(node, t) + get_suc_force(graph, node, t);
        }
    }
}

float get_pred_force(node_t * node, int t){
    float pred_force=0.0;
    if(t<=node->input_1->from->interval[1]){
        //In the interval for input1
        pred_force+=node->input_1->from->self_force[t];
    }
    if(t<=node->input_2->from->interval[1]){
        //In the interval for input2
        pred_force+=node->input_2->from->self_force[t];
    }
    if(node->type == MUX2X1 && t < node->select->from->interval[1]){
        //In the interval for select
        pred_force+=node->select->from->self_force[t];
    }
    return pred_force;
}
float get_suc_force(Graph * graph, node_t * node, int t){
    float suc_force = 0.0;
    for(int i=0;i<graph->nodes.size();++i){
        if(graph->nodes[i]->type != MUX2X1){ //Since select = Null if not mux, checking name will cause segfault
            if(graph->nodes[i]->input_1->name == node->output->name || graph->nodes[i]->input_2->name == node->output->name){
                //Node[i] is a successor of node
                if(t>=graph->nodes[i]->interval[0]){
                    //in the interval
                    suc_force+=graph->nodes[i]->self_force[t];
                }
            }
        }
        else {
            if(graph->nodes[i]->input_1->name == node->output->name || graph->nodes[i]->input_2->name == node->output->name || graph->nodes[i]->select->name == node->output->name){
                //Node[i] is a successor of node
                if(t>=graph->nodes[i]->interval[0]){
                    //in the interval
                    suc_force+=graph->nodes[i]->self_force[t];
                }
            }
        }

    }
    return suc_force;
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
    graph->inop.start_time=0;
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
bool schedule_min_force(Graph * graph, int end){
    bool unscheduled_nodes = false;
    int min_index = 0;
    int min_time = 0;
    float min_force = graph->nodes[0]->total_force[0];
    for(int i=0;i<graph->nodes.size();++i){
        for(int t=graph->nodes[i]->interval[0];t<=graph->nodes[i]->interval[1];++t){
            if(graph->nodes[i]->total_force[t] < min_force && graph->nodes[i]->color!="scheduled"){ //TODO and is schedulable!!
                min_index = i;
                min_time = t;
                min_force = graph->nodes[i]->total_force[t];
            }
        }
    }
    if(graph->nodes[min_index]->color!="scheduled"){
        graph->nodes[min_index]->start_time = min_time;
        graph->nodes[min_index]->interval[0] = min_time;
        graph->nodes[min_index]->interval[1] = min_time;
        graph->nodes[min_index]->color = "scheduled";
        unscheduled_nodes=true;
    }
    return unscheduled_nodes;
}
