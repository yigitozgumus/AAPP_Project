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

using namespace std;
using namespace boost;

void Tarjan::print_graph(){
    GraphComponent::print_graph_file(t);
}

void Tarjan::ApplyDFS() {
    typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex;
    Vertex_t theFirst = *(vertices(t).first);
    int Counter = 0;
    int SizeOfGraph = num_vertices(t);
    std::vector<int> visited(SizeOfGraph,666);
    std::cout << "Discovery Order is: " << std::endl;
    DepthFirstSearch( theFirst, Counter, visited);

}

void Tarjan::DepthFirstSearch( Vertex_t &v, int &Counter,std::vector<int> &visited) {
    v_p id = get(&VertexProperty::index, t);
    e_p arch_type = get(&EdgeProperty::name, t);
    Counter++;
    visited[id[v]] = static_cast<unsigned long>(Counter);
    std::cout << "Node(" << id[v] << ") --> " << visited[id[v]] << std::endl;
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

void Tarjan::ApplySCC() {
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
    std::cout << "Tarjan version of the SCC Algorithm is processing the graph" << std::endl;
    for (vp = vertices(t); vp.first != vp.second; vp.first++) {
        Vertex_t v = *vp.first;
        if (visited[id[v]] == 666) {
            StrongConnect(v,Points, Counter,visited,lowPt,lowVine);
        }
    }

}

void Tarjan::StrongConnect(Vertex_t &v, std::vector<Vertex_t> &Points, int &Counter,std::vector<int> &visited, std::vector<int> &lowPt, std::vector<int> &lowVine) {
    e_p arch_type = get(&EdgeProperty::name, t);
    v_p id = get(&VertexProperty::index,t);

    Counter++;
    visited[id[v]]= Counter;
    lowPt[id[v]]= Counter;
    lowVine[id[v]] = Counter;
   // std::cout<< visited[v] << " " << lowPt[v] << " " << lowVine[v] << std::endl;
    Points.push_back(v);
    typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
    boost::graph_traits<theGraph>::out_edge_iterator out_i, out_end;
    for (boost::tie(out_i, out_end) = out_edges(v, t); out_i != out_end; ++out_i) {
        Edge e = *out_i;
        Vertex_t w = target(e, t);
        if (visited[id[w]] == 666) {
            arch_type[e] = "tree"; // like in tarjan's algorithm
            StrongConnect(w,Points, Counter,visited,lowPt,lowVine);
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

        std::cout <<"Strongly connected Component is: ";
        while(!Points.empty() && visited[id[Points.back()]] >= visited[id[v]]){
            Vertex_t x = Points.back();
            Points.pop_back();
            std::cout << id[x]+1 << " ";
        }
        std::cout << std::endl;
        //Create a Vector of Vertex Vectors
        //pass it to the ApplySCC function
        //Create and Visualize Graphs there
    }

}

// void Tarjan::Biconnect( Vertex_t &v, int &Counter) {

// }

// void Tarjan::ApplyBiconnectivity() {

// }