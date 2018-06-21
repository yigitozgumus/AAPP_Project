#include "./../header/pearce.h"
#include "./../header/analyzer.h"

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

using namespace std;
using namespace boost;

void Pearce::print_graph(){
    GraphComponent::print_graph_file(p);
}

void Pearce::print_result_max(std::vector<int> &rindex){
    int sizeOfGraph = num_vertices(p);
    typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    v_p id = get(&VertexProperty::index ,p);
    
    int max = *max_element(std::begin(rindex), std::end(rindex));
    for(int i = 0; i <= max; i++){
         int count_component = 0;
          std::cout << "Strongly connected component is : "  << " ";
          for(vp=vertices(p); vp.first != vp.second; vp.first++){
                 Vertex_t v = *vp.first;
                if(rindex[id[v]] == i){
                    count_component++;
                    std::cout << id[v]+1 <<  " " ;
                }
         }
        std::cout << std::endl;
        std::cout << "Number of elements in the component is: " << count_component << std::endl;
    }

}

void Pearce::print_result_min(std::vector<int> &rindex){
    int sizeOfGraph = num_vertices(p); 
    typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    v_p id = get(&VertexProperty::index ,p);
     int min = *min_element(std::begin(rindex), std::end(rindex));
    for(int i = sizeOfGraph-1; i >= min; i--){
         int count_component = 0;
          std::cout << "Strongly connected component is : "  << " ";
          for(vp=vertices(p); vp.first != vp.second; vp.first++){
                 Vertex_t v = *vp.first;
                if(rindex[id[v]] == i){
                    std::cout << id[v]+1 <<  " " ;
                    count_component++;
                }
         }
        std::cout << std::endl;
        std::cout << "Number of elements in the component is: " << count_component << std::endl;
    }

}
void Pearce::DFS() {
    int index = 0;
    v_p id = get(&VertexProperty::index ,p);
    typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    int sizeOfGraph = num_vertices(p);
    std::vector<int> visited(sizeOfGraph,false);
    for(vp = vertices(p); vp.first != vp.second; vp.first++){
        Vertex_t v = *vp.first;
        if(!visited[id[v]]){
            visit(v,visited,index);
        }
    }
    std::cout << "\nPearce DFS implementation exited succesfully" << std::endl;
    std::cout << "Discovery Order is: " << std::endl;
    for(vp=vertices(p); vp.first != vp.second; vp.first++){
        Vertex_t v = *vp.first;
        std::cout << "Node(" << id[v] << ") --> " << visited[id[v]] << std::endl;
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
        if (visited[id[w]] == false){
            visit(w, visited,index);
        }
    }

}

UtilityStructs::StorageItems Pearce::Pea_Find_SCC1() {
    float ms_duration;
    int index = 0;
    int c= 0;
    int sizeOfGraph = num_vertices(p);
    std::vector<bool> visited(sizeOfGraph,false);
    std::vector<int> rindex (sizeOfGraph,0);
    std::vector<bool> inComponent(sizeOfGraph,false);
    std::vector<Vertex_t> Stack;
    v_p id = get(&VertexProperty::index, p);
    typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
//    std::cout << "\nPearce SCC implementation mark 1 exited succesfully" << std::endl;
    //Create the Timer object
    {
        UtilityStructs::Timer timer;
    for(vp=vertices(p); vp.first != vp.second; vp.first++){
        Vertex_t v = *vp.first;
        if(!visited[id[v]]){
            visit_scc1(v,visited,rindex,inComponent,Stack,index,c);
        }
    }
    ms_duration = timer.stop();
    }
    //Storage info collection
    //print_result_max(rindex);
    size_t total_bytes = 0;
    total_bytes += sizeof(visited[0]) * visited.size();
    total_bytes += sizeof(rindex[0]) * rindex.size();
    total_bytes += sizeof(rindex[0]) * inComponent.size();
    UtilityStructs::StorageItems s;
    s.vertexCount = num_vertices(p);
    s.edgeCount = num_edges(p);
    s.duration = ms_duration;
    s.total_bytes = total_bytes;
    return s;
}

void Pearce::visit_scc1(Vertex_t &v,
                        std::vector<bool> &visited,
                        std::vector<int> &rindex,
                        std::vector<bool> &inComponent,
                        std::vector<Vertex_t> &Stack,
                        int &index,
                        int &c){

    v_p id = get(&VertexProperty::index, p);
    bool root= true;
    visited[id[v]] = true;
    rindex[id[v]] = index++;
    inComponent[id[v]] = false;

    typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
    boost::graph_traits<theGraph>::out_edge_iterator out_i, out_end;

    for (boost::tie(out_i, out_end) = out_edges(v, p); out_i != out_end; ++out_i){
        Edge e = *out_i;
        Vertex_t w = target(e, p);
        if (visited[id[w]] == false){
            visit_scc1(w, visited,rindex,inComponent,Stack, index,c);
        }
        if(! inComponent[id[w]] && (rindex[id[w]] < rindex[id[v]])){
            rindex[id[v]] = rindex[id[w]]; 
            root = false;
        }
    }
    if(root){
        inComponent[id[v]] = true ;
        if(!Stack.empty()){
            while(!Stack.empty() && (rindex[id[v]] <= rindex[id[Stack.back()]])){
                Vertex_t w = Stack.back();
                Stack.pop_back();
                rindex[id[w]] = c;
                inComponent[id[w]] = true;
            }
                 
        }
        rindex[id[v]] = c;
        c = c+1;
    }else{
        Stack.push_back(v);
    }
}

UtilityStructs::StorageItems Pearce::Pea_Find_SCC2(){
    float ms_duration;
    int index = 1;
    int sizeOfGraph = num_vertices(p);
    int c = sizeOfGraph -1;
    std::vector<int> rindex(sizeOfGraph, 0);
    std::vector<Vertex_t> Stack;
    v_p id = get(&VertexProperty::index, p);
    typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    //Create the Timer object
    //TODO
//    std::cout << "\nPearce SCC implementation mark 2 exited succesfully" << std::endl;
    {
        UtilityStructs::Timer timer;
        for (vp = vertices(p); vp.first != vp.second; vp.first++){
        Vertex_t v = *vp.first;
        if (rindex[id[v]] == 0){
            visit_scc2(v,rindex, Stack, index, c);
        }
    }
    ms_duration = timer.stop();
    }
    //Storage info collection
    //print_result_min(rindex);
    size_t total_bytes = 0;
    total_bytes += sizeof(c);
    total_bytes += sizeof(rindex[0]) * rindex.size();
    UtilityStructs::StorageItems s;
    s.vertexCount = num_vertices(p);
    s.edgeCount = num_edges(p);
    s.duration = ms_duration;
    s.total_bytes = total_bytes;
    return s;
}

void Pearce::visit_scc2(Vertex_t &v,
                        std::vector<int> &rindex,
                        std::vector<Vertex_t> &Stack,
                        int &index,
                        int &c) {

    v_p id = get(&VertexProperty::index, p);
    bool  root = true;
    rindex[id[v]] = index++;

    typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
    boost::graph_traits<theGraph>::out_edge_iterator out_i, out_end;

    for (boost::tie(out_i, out_end) = out_edges(v, p); out_i != out_end; ++out_i){
        Edge e = *out_i;
        Vertex_t w = target(e, p);
        if (rindex[id[w]] == 0){
            visit_scc2(w, rindex, Stack, index, c);
        }
        if(rindex[id[w]] < rindex[id[v]]){
            rindex[id[v]] = rindex[id[w]] ;
            root = false;
        }
    }

    if(root){
        index--;
        if(!Stack.empty()){
            while(! Stack.empty() && (rindex[id[v]] <= rindex[id[Stack.back()]])){
                Vertex_t w = Stack.back();
                Stack.pop_back();
                rindex[id[w]] = c;
                index--; 
            }
        }
        rindex[id[v]] = c;
        c=c-1;
    }else{
        Stack.push_back(v);
    }
}

UtilityStructs::StorageItems Pearce::Pea_Find_SCC3() {
    float ms_duration;
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
    //Create the Timer Object 
    //TODO
 //   std::cout << "\nPearce SCC implementation mark 3 exited succesfully" << std::endl;
    {
        UtilityStructs::Timer timer;
        for (vp = vertices(p); vp.first != vp.second; vp.first++){
        Vertex_t v = *vp.first;
        if (rindex[id[v]] == 0){
            visit_scc3(v, root,rindex,vStack,iStack,index,c);
        }
    }
        ms_duration = timer.stop();
    }
    //print_result_min(rindex);  
    //Storage info collection
    size_t total_bytes= 0;
    total_bytes += sizeof(root[0]) * root.size();
    total_bytes += sizeof(rindex[0]) * rindex.size();
    UtilityStructs::StorageItems s;
    s.vertexCount = num_vertices(p);
    s.edgeCount = num_edges(p);
    s.duration = ms_duration;
    s.total_bytes = total_bytes;
    return s;
      
    

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
        visitLoop(root,rindex,vStack,iStack,index,c);
    }
}

void Pearce::visitLoop( std::vector<bool> &root,
                        std::vector<int> &rindex,
                        std::vector<Vertex_t> &vStack,
                        std::vector<int> &iStack,
                        int &index,
                        int &c) {
    Vertex_t v = vStack[0];
    int i = iStack[0];
    
    int out_edges = out_degree(v,p);
    
    while(i <= out_edges){
        if (i > 0){
            int k = i-1;
            finishEdge(v,k,rindex,root);
        }
        if ( i < out_edges && beginEdge(v,i,root,rindex,vStack,iStack,index,c)){
            return;
        }
        i = i+1;
    }
    finishVisiting(v,root,rindex,vStack,iStack,index,c);
}

void Pearce::beginVisiting(Vertex_t &v,
                           std::vector<bool> &root,
                           std::vector<int> &rindex,
                           std::vector<Vertex_t> &vStack,
                           std::vector<int> &iStack,
                           int &index){
    
    vStack.insert(vStack.begin(),v);
    iStack.insert(iStack.begin(),0);
    v_p id = get(&VertexProperty::index, p);
    root[id[v]] = true;
    rindex[id[v]] = index;
    index = index+1;
}

void Pearce::finishVisiting(Vertex_t &v,
                            std::vector<bool> &root,
                            std::vector<int> &rindex,
                            std::vector<Vertex_t> &vStack,
                            std::vector<int> &iStack,
                            int &index,
                            int &c) {
    v_p id = get(&VertexProperty::index, p);
    vStack.erase(vStack.begin());
    iStack.erase(iStack.begin());
    if(root[id[v]]){
        index--;
        while(!vStack.empty() && (rindex[id[v]] <= rindex[id[vStack.back()]])){
            Vertex_t w = vStack.back();
            vStack.pop_back();
            rindex[id[w]] = c;
            index--;
        }
        rindex[id[v]] = c;
        c = c-1;
    }else{
        vStack.push_back(v);
    }

}

bool Pearce::beginEdge(Vertex_t &v,
                        int &k,
                        std::vector<bool> &root,
                        std::vector<int> &rindex,
                        std::vector<Vertex_t> &vStack,
                        std::vector<int> &iStack,
                        int &index,
                        int &c) {

    v_p id = get(&VertexProperty::index, p);
    typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
    boost::graph_traits<theGraph>::out_edge_iterator out_i, out_end;
    boost::tie(out_i,out_end) = out_edges(v,p);
    out_i += k;
    Edge e = *out_i;
    Vertex_t w = target(e, p);
    if(rindex[id[w]] == 0){
        iStack.erase(iStack.begin());
        iStack.insert(iStack.begin(),k+1);
        beginVisiting(w,root,rindex,vStack,iStack,index);
        return true;
    }else{
        return false;
    }

}

void Pearce::finishEdge(Vertex_t &v,
                        int &k,
                        std::vector<int> &rindex,
                        std::vector<bool> &root) {
    v_p id = get(&VertexProperty::index, p);
    typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
    boost::graph_traits<theGraph>::out_edge_iterator out_i, out_end;
    boost::tie(out_i,out_end) = out_edges(v,p);
    out_i += k;
    Edge e = *out_i;
    Vertex_t w = target(e, p);
    if(rindex[id[w]] < rindex[id[v]]){
        rindex[id[v]] = rindex[id[w]];
        root[id[v]] = false;
    }

}

