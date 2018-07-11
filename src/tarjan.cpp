#include "./../header/tarjan.h"

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

using namespace boost;
using namespace std;

void Tarjan::print_graph(){
    GraphComponent::print_graph_file(t);
}

void Tarjan::ApplyDFS() {
    typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex;
    v_p id = get(&VertexProperty::index, t);
    typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    Vertex_t theFirst = *(vertices(t).first);
    int Counter = 0;
    int SizeOfGraph = num_vertices(t);
    std::vector<int> visited(SizeOfGraph,666);
    DepthFirstSearch(theFirst, Counter, visited);
    std::cout << "\nTarjan Depth First Search Exited Successfully." << std::endl;
    std::cout << "Discovery Order is: " << std::endl;
     for(vp=vertices(t); vp.first != vp.second; vp.first++){
        Vertex_t v = *vp.first;
        std::cout << "Node(" << id[v] << ") --> " << visited[id[v]] << std::endl;
    }

}

void Tarjan::DepthFirstSearch( Vertex_t &v, int &Counter,std::vector<int> &visited) {
    v_p id = get(&VertexProperty::index, t);
    e_p arch_type =get(&EdgeProperty::name, t);
    Counter++;
    visited[id[v]] = static_cast<unsigned long>(Counter);
 //   std::cout << "Node(" << id[v] << ") --> " << visited[id[v]] << std::endl;
    typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
    boost::graph_traits<theGraph>::out_edge_iterator out_i, out_end;
    for (boost::tie(out_i, out_end) = out_edges(v, t); out_i != out_end; ++out_i) {
        Edge e = *out_i;
        Vertex_t w = target(e, t);
        if (visited[id[w]] == 666) {
            arch_type[e] = "forward";
            //std::cout << "Node(" <<id[w] << ") --> " << visited[w] << std::endl;
            DepthFirstSearch(w, Counter,visited);
        } else if (visited[id[w]] < visited[id[v]]) {
            arch_type[e] = "backward";
        }
    }
}

bool Tarjan::isReachable(Vertex_t &source, Vertex_t &Target) {
    typedef graph_traits<theGraph>::vertices_size_type size_type;
    size_type n_vertices;
    n_vertices = num_vertices(t);
    v_p id = get(&VertexProperty::index, t);
    std::vector<bool> Visited(n_vertices, false);
    std::deque<Vertex_t> Checks;
    Visited[id[source]] = true;
    Checks.push_back(source);
    while (!Checks.empty()) {
        Vertex_t v = Checks.front();
        Checks.pop_front();
        boost::graph_traits<theGraph>::out_edge_iterator out_i, out_end;
        for (boost::tie(out_i, out_end) = out_edges(v, t); out_i != out_end; ++out_i) {
            Vertex_t w = target(*out_i, t);
            if (id[w] == id[Target]) {
                return true;
            } else if (!Visited[id[w]]) {
                Visited[id[w]] = true;
                Checks.push_back(w);
            }

        }

    }
    return false;

}

void Tarjan::print_sccs(std::vector<int> &rindex){
    
}

UtilityStructs::StorageItems Tarjan::ApplySCC(bool debugMode) {
    float ms_duration = 0;
    v_p id = get(&VertexProperty::index, t);
    typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
    typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    std::vector<Vertex_t> Points;
    int Counter = 0;
    int SizeOfGraph = num_vertices(t);
    std::vector<int> visited(SizeOfGraph,666);
    std::vector<int> lowPt(SizeOfGraph,666);
    std::vector<int> lowVine(SizeOfGraph,666);
    int stackCount = 0;
   // std::cout << "\nTarjan version of the SCC Algorithm has processed the graph" << std::endl;
    //TIMER
    {
        UtilityStructs::Timer timer;
    for (vp = vertices(t); vp.first != vp.second; vp.first++) {
        Vertex_t v = *vp.first;
        if (visited[id[v]] == 666) {
            StrongConnect(v,Points, Counter,visited,lowPt,lowVine,stackCount,debugMode);
        }
    }
    ms_duration = timer.stop();
    }
    //TIMER end
    //Storage info collection
    size_t total_bytes = 0;
    total_bytes += sizeof(visited[0]) * visited.size();
    total_bytes += sizeof(lowPt[0]) * lowPt.size();
    total_bytes += sizeof(lowVine[0]) * lowVine.size();
    total_bytes +=sizeof(Points[0]) * stackCount;
    UtilityStructs::StorageItems s;
    s.vertexCount = num_vertices(t);
    s.edgeCount = num_edges(t);
    s.duration = ms_duration;
    s.total_bytes = total_bytes;
    Visualize vis;
    if(debugMode){
        vis.printProgramBottom();
         std::stringstream buffer3;
        buffer3 << setw(40) << left <<"Completion Time" ;
        buffer3 << ": " << s.duration << " miliseconds" ;
        std::stringstream buffer4;
        buffer4 << setw(40)<< left << "Total Execution Size";
        buffer4 << ": " << s.total_bytes / 1024.f << " KBs";
        vis.printLine(buffer3.str());
        vis.printLine(buffer4.str());
}
    return s;
}

void Tarjan::StrongConnect(Vertex_t &v, 
                            std::vector<Vertex_t> &Points, 
                            int &Counter,
                            std::vector<int> &visited, 
                            std::vector<int> &lowPt, 
                            std::vector<int> &lowVine,
                            int &stackCount,
                            bool debugMode) {
    e_p arch_type = get(&EdgeProperty::name, t);
    v_p id = get(&VertexProperty::index,t);
    Visualize vis;
    Counter++;
    visited[id[v]]= Counter;
    lowPt[id[v]]= Counter;
    lowVine[id[v]] = Counter;
    Points.push_back(v);
    stackCount++;
    typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
    boost::graph_traits<theGraph>::out_edge_iterator out_i, out_end;
    for (boost::tie(out_i, out_end) = out_edges(v, t); out_i != out_end; ++out_i) {
        Edge e = *out_i;
        Vertex_t w = target(e, t);
        if (visited[id[w]] == 666) {
            arch_type[e] = "tree"; // like in tarjan's algorithm
            StrongConnect(w,Points, Counter,visited,lowPt,lowVine,stackCount,debugMode);
            lowPt[id[v]] = lowPt[id[v]]< lowPt[id[w]]?lowPt[id[v]]:lowPt[id[w]];
            lowVine[id[v]] = lowVine[id[v]]< lowVine[id[w]]?lowVine[id[v]]:lowVine[id[w]];
        } else if (!isReachable( w, v)) {
            if (visited[id[w]] < visited[id[v]]) {
                arch_type[e] = "vine";
                if (std::find(Points.begin(), Points.end(), w) != Points.end()) {
                    lowVine[id[v]] = lowVine[id[v]] < visited[id[w]] ? lowVine[id[v]] : visited[id[w]];
                }
            }
        } else {// TODO Ancestor problem
            arch_type[e] = "frond";
            lowPt[id[v]] = lowPt[id[v]] < visited[id[w]] ? lowPt[id[v]] : visited[id[w]];
        }
    }
    if (lowPt[id[v]] == visited[id[v]] && lowVine[id[v]] == visited[id[v]]) {
            int count_component = 0;
            std::stringstream buffer ;
            if(debugMode){
                vis.printLine("");
                buffer << setw(40) << std::left << "The Strongly Connected Component is" ;
                 buffer << ": ";
                 count_component++;
            }
            
        while(!Points.empty() && visited[id[Points.back()]] >= visited[id[v]]){
            Vertex_t x = Points.back();
            Points.pop_back();
            buffer << id[x]+1 <<  " " ;
        }
       if(debugMode){
        vis.printLine(buffer.str());
        std::stringstream buffer2;
        buffer2 << setw(40) << std::left << "Number of elements in the component is" ;
        buffer2 << ": "<< count_component ;
        vis.printLine(buffer2.str());
       }
    }

}

// void Tarjan::Biconnect( Vertex_t &v, int &Counter) {

// }

// void Tarjan::ApplyBiconnectivity() {

// }
