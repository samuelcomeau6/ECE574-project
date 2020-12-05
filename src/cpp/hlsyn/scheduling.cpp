#include "graph.h"
#include "scheduling.h"
#include <cassert>
#include <iostream>
#include <fstream>
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
    #ifdef DEBUG3
        std::cout << g_alap.scheduled_graph_toString();
        std::cout << g_asap.scheduled_graph_toString();
    #endif
    for(int i=0;i<graph->nodes.size();++i){
        if(graph->nodes[i]->color!="scheduled"){
            //Time frame is [asap, alap]
            graph->nodes[i]->interval[0] = g_asap.nodes[i]->start_time;
            graph->nodes[i]->interval[1] = g_alap.nodes[i]->start_time;
        }
    }
    #ifdef DEBUG
        for(int i=0;i<graph->nodes.size();++i){
            std::cout << "node " << i << ": "  << graph->nodes[i]->name;
            std::cout << " interval:[" << graph->nodes[i]->interval[0] << "," << graph->nodes[i]->interval[1] << "]" << std::endl;
        }
    #endif

}

void compute_probability(Graph * graph, int end){
    for(int i=0;i<graph->nodes.size();++i){
        node_t * node = graph->nodes[i];
        node->prb.resize(end+1);
        for(int j=0;j<=end;++j){
            node->prb[j]=0; //Initialize but can't do in next step because additive
        }
        for(int j=0;j<=end;++j){
            //if j is outside time frame prb=0
            if(j<node->interval[0] || j>node->interval[1]){
                continue;
            }
            //else prb=1/(width timeframe) through duration
            else {
                int width=node->interval[1] - node->interval[0] + 1;
                if(width!=0){
                    for(int l=0;l<node->duration;++l){
                        node->prb[j+l] += 1.0/width;
                    }
                }
            }
        }
    }
}
void compute_type_dist(Graph * graph, int end){
    graph->q.resize(5);
    for(int i=0;i<graph->q.size();++i){
        graph->q[i].resize(end+1);
        for(int j=0;j<end+1;++j){
            graph->q[i][j] = 0;
        }
    }
    //for each node, v
    for(int i=0;i<graph->nodes.size();++i){
        node_t * node = graph->nodes[i];
        //if type=k qk(t)=qk(t)+v.prb(t)
        for(int t=0;t<=end;++t){
            int k = get_bin(node->type);
            graph->q[k][t] = graph->q[k][t] + node->prb[t];
        }
    }
    #ifdef DEBUG
        printf("TypeDistr:\n");
        for(int k=0;k<graph->q.size();++k){
            printf("[k=%d]:",k);
            for(int t=1;t<=end;++t){
                printf("[t=%d]:%.2f",t,graph->q[k][t]);
            }
            printf("\n");
        }
    #endif
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
        default:
            k=4;
            break;
    }
    return k;
}
void compute_forces(Graph * graph, int end){
    for(int i=0;i<graph->nodes.size();++i){
        node_t * node = graph->nodes[i];
        node->self_force.resize(end+1);
        node->total_force.resize(end+1);
        for(int j=node->interval[0];j<=node->interval[1];++j){
            node->self_force[j]=0;
            //v.selfforce = sigma( v.force(l), intervalStart, intervalEnd + duration)
            for(int l=node->interval[0];l<=node->interval[1]+node->duration;++l){
                //x(l)=window[j,t+duration](l)-v.prob(l)
                float kdelta = 0.0;
                if(l>=j && l < j + node->duration) kdelta = 1.0;
                float x = (kdelta - node->prb[l]);
                //v.force(l)=qk(j)*x(l)
                #ifdef DEBUG3
                    printf("\tself_force%d[j%d][l%d] = %.2f + %.2f * (%.2f - %.2f) = ",
                           l,j,l,node->self_force[j],graph->q[get_bin(node->type)][l],kdelta,node->prb[l]);
                #endif
                node->self_force[j] += graph->q[get_bin(node->type)][l]*x;
                #ifdef DEBUG3
                    printf("%.2f\n",node->self_force[j]);
                #endif
            }
        }
    }
    //pred_suc force = sum of forces of ALL implictly scheduled
    //total forces=self_force+pred_suc force
    for(int i=0;i<graph->nodes.size();++i){
        node_t * node = graph->nodes[i];
        for(int t=node->interval[0];t<=node->interval[1];++t){
            node->total_force[t] = node->self_force[t] + get_predsuc_force(graph, node, t);
        }
    }
    #ifdef DEBUG
        for(int i=0;i<graph->nodes.size();++i){
            std::cout << "node " << i << ": "  << graph->nodes[i]->name << " ";
            for(int t=graph->nodes[i]->interval[0];t<=graph->nodes[i]->interval[1];++t){
                std::cout <<"@"<< t<<":" << graph->nodes[i]->self_force[t] << "+"
                          << get_predsuc_force(graph, graph->nodes[i], t) << "="
                          << graph->nodes[i]->total_force[t] << " ";
            }
            std::cout << std::endl;
        }
    #endif

}

float get_predsuc_force(Graph * graph, node_t * node, int t){
    float ps_force = 0.0;
    if(node->name == "onop" || node->name == "inop" || t<=0){
        return 0.0;
    }
    for(int i=0;i<graph->nodes.size();++i){
        node_t * ps_node = graph->nodes[i];
        bool is_pred = false;
        bool is_succ = false;
        //Test if sucessor
        is_succ = (is_succ
                   || ps_node->input_1->name == node->output->name
                   || ps_node->input_2->name == node->output->name);
        if(ps_node->type == MUX2X1){ //Since select = Null if not mux, checking name will cause segfault
            is_succ = (is_succ || ps_node->select->name == node->output->name);
        }
        //Test is predessor
        is_pred = (is_pred
                    || ps_node->name == node->input_1->from->name
                    || ps_node->name == node->input_2->from->name);
        if(node->type == MUX2X1){
            is_pred = (is_pred || ps_node->name == node->select->from->name);
        }
        assert(!(is_pred && is_succ));
        float sum1=0;
        float sum2=0;
        if(is_pred || is_succ){
            int ts=ps_node->interval[0];
            int tl=ps_node->interval[1];
            if(is_pred && t < tl) tl = t;
            if(is_succ && t > ts) ts = t;
            std::vector<float> mod_prob;
            mod_prob.resize(tl+ps_node->duration+1);
            for(int j=0;j<tl;++j){
                for(int l=0;l<node->duration;++l){
                    if(ts<=j && j<=tl) mod_prob[j+l] += 1.0/(tl-ts+1);
                }
            }
            for(int l=ts;l<=tl+ps_node->duration;++l){
                sum1 += graph->q[get_bin(ps_node->type)][l]*mod_prob[l];
            }
            for(int l=ps_node->interval[0]; l<=ps_node->interval[1]+ps_node->duration;++l){
                sum2 += graph->q[get_bin(ps_node->type)][l]*ps_node->prb[l];
            }
        }
        ps_force += (sum1 - sum2);
    }
    return ps_force;
}

void alap(Graph * graph,int latency){
    graph->onop.start_time=latency+1;
    graph->onop.color="scheduled";
    int t=latency;
    bool unscheduled_nodes = true;
    while(unscheduled_nodes){
        if(t<0) {
            fprintf(stderr, "Datapath does not fit with latency constraint of:%d, relax constraint.\n",latency);
            exit(EXIT_FAILURE);
        }
        unscheduled_nodes = false;
        for(int i=0;i<graph->nodes.size();++i){
            if(graph->nodes[i]->color!="scheduled"){
                unscheduled_nodes=true;
                if(alap_schedulable(graph, i, t)){
                    #ifdef DEBUG3
                        printf("%s is alap @ %d\n",graph->nodes[i]->name.c_str(),t);
                    #endif
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
    } else {
        input_2_ok = true;
    }
    return (input_1_ok && input_2_ok && select_ok);
}
bool alap_schedulable(Graph * graph, int index, int t){
    bool ok=true;
    std::string out = graph->nodes[index]->output->name;
    for(int i=0;i<graph->edges.size();++i){
        edge_t * edge = graph->edges[i];
        if(out == edge->name){
            ok = ok && edge->to->color=="scheduled";
            ok = ok && t<=(edge->to->start_time - graph->nodes[index]->duration);
        }
    }
    return ok;
}
bool schedule_min_force(Graph * graph, int end){
    bool unscheduled_nodes = false;
    int min_index = 0;
    int min_time = 0;
    float min_force = FLT_MAX;
    for(int i=0;i<graph->nodes.size();++i){
        for(int t=graph->nodes[i]->interval[0];t<=graph->nodes[i]->interval[1];++t){
            if(graph->nodes[i]->total_force[t] < min_force && graph->nodes[i]->color!="scheduled"){
                min_index = i;
                min_time = t;
                min_force = graph->nodes[i]->total_force[t];
            }
        }
    }
    #ifdef DEBUG
        printf("Scheduling %s @ %d. Had interval of [%d,%d]\n",graph->nodes[min_index]->name.c_str(),min_time,
                graph->nodes[min_index]->interval[0], graph->nodes[min_index]->interval[1]);
    #endif
    if(graph->nodes[min_index]->color!="scheduled"){
        graph->nodes[min_index]->start_time = min_time;
        graph->nodes[min_index]->interval[0] = min_time;
        graph->nodes[min_index]->interval[1] = min_time;
        graph->nodes[min_index]->color = "scheduled";
        unscheduled_nodes=true;
    }
        
    return unscheduled_nodes;
}
