#include "./../header/pearce.h"

//STL
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
//Boost
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list_io.hpp>
#include <boost/graph/property_iter_range.hpp>
#include <boost/graph/copy.hpp>
#include <boost/property_map/property_map.hpp>

void Pearce::print_graph(){
    GraphComponent::print_graph_file(p);
}

void Pearce::DFS() {
    int index = 0;
    v_p id = get(&VertexProperty::index ,p);
    typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    int sizeOfGraph = num_vertices(p);
    std::vector<int> visited(sizeOfGraph,666);
    for(vp = vertices(p); vp.first != vp.second; vp.first++){
        Vertex_t v = *vp.first;
        if(visited[id[v]]){
            visit(v,visited,index);
        }
    }
}

void Pearce::visit(Vertex_t &v,std::vector<int> &visited,int &index) {
    v_p id = get(&VertexProperty::index, p);
    visited[id[v]] = index++;
    typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
    boost::graph_traits<theGraph>::out_edge_iterator out_i, out_end;
    for (boost::tie(out_i, out_end) = out_edges(v, p); out_i != out_end; ++out_i){
        Edge e = *out_i;
        Vertex_t w = target(e, p);
        if (visited[id[w]] == 666){
            visit(w, visited,index);
        }
    }
}

void Pearce::Pea_Find_SCC1() {
    int index = 0;
    int c= 0;
    int sizeOfGraph = num_vertices(p);
    std::vector<bool> root(sizeOfGraph,false);
    std::vector<bool> visited(sizeOfGraph,666);
    std::vector<int> rindex (sizeOfGraph,-1);
    std::vector<bool> inComponent(sizeOfGraph,false);
    std::vector<Vertex_t> Stack;
    v_p id = get(&VertexProperty::index, p);
    typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;

    for(vp=vertices(p); vp.first != vp.second; vp.first++){
        Vertex_t v = *vp.first;
        if(visited[id[v]]){
            visit_scc1(v,root,visited,rindex,inComponent,Stack,index,c);
        }
    }

    //process rindex
}

void Pearce::visit_scc1(Vertex_t &v,
                        std::vector<bool> &root,
                        std::vector<bool> &visited,
                        std::vector<int> &rindex,
                        std::vector<bool> &inComponent,
                        std::vector<Vertex_t> &Stack,
                        int &index,
                        int &c){

    v_p id = get(&VertexProperty::index, p);
    root[id[v]] = true;
    visited[id[v]] = true;
    rindex[id[v]] = index++;
    inComponent[id[v]] = false;

    typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
    boost::graph_traits<theGraph>::out_edge_iterator out_i, out_end;

    for (boost::tie(out_i, out_end) = out_edges(v, p); out_i != out_end; ++out_i){
        Edge e = *out_i;
        Vertex_t w = target(e, p);
        if (visited[id[w]] == false){
            visit_scc1(w,root, visited,rindex,inComponent,Stack, index,c);
        }
        if(! inComponent[id[w]] && (rindex[id[w]] < rindex[id[v]])){
            rindex[id[v]] = rindex[id[w]]; 
            root[id[v]] = false;
        }
    }
    if(root[id[v]]){
        inComponent[id[v]] = true ;
        if(!Stack.empty()){
            while(!Stack.empty() && (rindex[id[v]] < rindex[id[Stack.back()]])){
                Vertex_t w = Stack.back();
                Stack.pop_back();
                rindex[id[w]] = c;
                inComponent[id[w]] = true;
            }
            rindex[id[v]] = c++;     
        }
    }else{
        Stack.push_back(v);
    }
}

void Pearce::Pea_Find_SCC2() {
    int index = 1;
    int sizeOfGraph = num_vertices(p);
    int c = sizeOfGraph -1;
    std::vector<bool> root(sizeOfGraph, false);
    std::vector<int> rindex(sizeOfGraph, 0);
    std::vector<Vertex_t> Stack;
    v_p id = get(&VertexProperty::index, p);
    typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;

    for (vp = vertices(p); vp.first != vp.second; vp.first++)
    {
        Vertex_t v = *vp.first;
        if (rindex[id[v]] == 0){
            visit_scc2(v, root, rindex, Stack, index, c);
        }
    }

    //Process rindex
}

void Pearce::visit_scc2(Vertex_t &v,
                        std::vector<bool> &root,
                        std::vector<int> &rindex,
                        std::vector<Vertex_t> &Stack,
                        int &index,
                        int &c) {

    v_p id = get(&VertexProperty::index, p);
    root[id[v]] = true;
    rindex[id[v]] = index++;

    typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
    boost::graph_traits<theGraph>::out_edge_iterator out_i, out_end;

    for (boost::tie(out_i, out_end) = out_edges(v, p); out_i != out_end; ++out_i){
        Edge e = *out_i;
        Vertex_t w = target(e, p);
        if (rindex[id[v]] == 0){
            visit_scc2(v, root, rindex, Stack, index, c);
        }
        if(rindex[id[w]] < rindex[id[v]]){
            rindex[id[v]] = rindex[id[w]] ;
            root[id[v]] = false;
        }
    }

    if(root[id[v]]){
        index--;
        if(!Stack.empty()){
            while(! Stack.empty() && (rindex[id[v]] < rindex[id[Stack.back()]])){
                Vertex_t w = Stack.back();
                Stack.pop_back();
                rindex[id[w]] = c;
                index--; 
            }
        }
        rindex[id[v]] = c--;
    }else{
        Stack.push_back(v);
    }
}

void Pearce::Pea_Find_SCC3() {
    int index = 1;
    int sizeOfGraph = num_vertices(p);
    int c = sizeOfGraph -1;
    std::vector<bool> root(sizeOfGraph,false);
    std::vector<int> rindex(sizeOfGraph,0);
    std::vector<Vertex_t> vStack;
    std::vector<int> iStack;
    v_p id = get(&VertexProperty::index,p);

    typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;

    for (vp = vertices(p); vp.first != vp.second; vp.first++){
        Vertex_t v = *vp.first;
        if (rindex[id[v]] == 0){
            visit_scc3(v, root,rindex,vStack,iStack,index,c);
        }
    }

    //Process rindex

}

void Pearce::visit_scc3(Vertex_t &v,
                        std::vector<bool> &root,
                        std::vector<int> &rindex,
                        std::vector<Vertex_t> &vStack,
                        std::vector<int> &iStack,
                        int &index,
                        int &c) {

    beginVisiting(v,root,rindex,vStack,iStack,index);
    while(!vStack.empty()){
        visitLoop();

    }
}

void Pearce::visitLoop() {

}

void Pearce::beginVisiting(Vertex_t &v,
                           std::vector<bool> &root,
                           std::vector<int> &rindex,
                           std::vector<Vertex_t> &vStack,
                           std::vector<int> &iStack,
                           int &index){
    
    vStack.push_back(v);
    iStack.push_back(0);
    v_p id = get(&VertexProperty::index, p);
    root[id[v]] = true;
    rindex[id[v]] = index++
}

void Pearce::finishVisiting(Vertex_t &v) {

}

void Pearce::beginEdge(Vertex_t &v) {

}

void Pearce::finishEdge(Vertex_t &v) {

}

