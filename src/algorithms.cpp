#include "../header/algorithms.h"
//STL
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <deque>
#include <algorithm>
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

void Algorithms::Tarjan::ApplyDFS(SCC_Graph &g) {
    typedef boost::graph_traits<SCC_Graph>::vertex_descriptor Vertex;
    Vertex theFirst = *(vertices(g).first);
    int Counter = 0;
    std::cout << "Discovery Order is: " << std::endl;
    DepthFirstSearch(g, theFirst, Counter);

}

void Algorithms::Tarjan::DepthFirstSearch(SCC_Graph &g, Vertex &v, int &Counter) {
    v_p visited = get(&PVertexProperties::num, g);
    v_p id = get(&PVertexProperties::index, g);
    e_p arch_type = get(&EdgeProperties::name, g);
    Counter++;
    visited[v] = static_cast<unsigned long>(Counter);
    std::cout << "Node(" << id[v] << ") --> " << visited[v] << std::endl;
    typedef boost::graph_traits<SCC_Graph>::edge_descriptor Edge;
    boost::graph_traits<SCC_Graph>::out_edge_iterator out_i, out_end;
    for (boost::tie(out_i, out_end) = out_edges(v, g); out_i != out_end; ++out_i) {
        Edge e = *out_i;
        Vertex w = target(e, g);
        if (visited[w] == 666) {
            arch_type[e] = "forward";
            //std::cout << "Node(" <<id[w] << ") --> " << visited[w] << std::endl;
            DepthFirstSearch(g, w, Counter);
        } else if (visited[w] < visited[v]) {
            arch_type[e] = "backward";
        }
    }
}

bool Algorithms::Tarjan::isReachable(SCC_Graph &g, Vertex &source, Vertex &Target) {
    typedef graph_traits<SCC_Graph>::vertices_size_type size_type;
    size_type n_vertices;
    n_vertices = num_vertices(g);
    v_p id = get(&PVertexProperties::index, g);
    std::vector<bool> Visited(n_vertices, false);
    std::deque<Vertex> Checks;
    Visited[id[source]] = true;
    Checks.push_back(source);
    while (!Checks.empty()) {
        Vertex v = Checks.front();
        Checks.pop_front();
        boost::graph_traits<SCC_Graph>::out_edge_iterator out_i, out_end;
        for (boost::tie(out_i, out_end) = out_edges(v, g); out_i != out_end; ++out_i) {
            Vertex w = target(*out_i, g);
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

void Algorithms::Tarjan::ApplySCC(SCC_Graph &g) {
    v_p visited = get(&PVertexProperties::num, g);
    typedef boost::graph_traits<SCC_Graph>::vertex_descriptor Vertex;
    typedef boost::graph_traits<SCC_Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    std::vector<Vertex> Points;
    int Counter = 0;
    std::vector<StronglyConnected> strongs;

    for (vp = vertices(g); vp.first != vp.second; vp.first++) {
        Vertex v = *vp.first;
        if (visited[v] == 666) {
            StrongConnect(g, v, strongs,Points, Counter);
        }
    }
}

void Algorithms::Tarjan::StrongConnect(SCC_Graph &g, Vertex &v, std::vector<StronglyConnected> &sccs,
                                       std::vector<Vertex> &Points, int &Counter) {
    v_p visited = get(&PVertexProperties::num, g);
    v_p lowPt = get(&PVertexProperties::lowPt, g);
    v_p lowVine = get(&PVertexProperties::lowVine, g);
    e_p arch_type = get(&EdgeProperties::name, g);
    v_p id = get(&PVertexProperties::index,g);
    Counter++;
    visited[v]= Counter;
    lowPt[v]= Counter;
    lowVine[v] = Counter;
    std::cout<< visited[v] << " " << lowPt[v] << " " << lowVine[v] << std::endl;
    Points.push_back(v);
    typedef boost::graph_traits<SCC_Graph>::edge_descriptor Edge;
    boost::graph_traits<SCC_Graph>::out_edge_iterator out_i, out_end;
    for (boost::tie(out_i, out_end) = out_edges(v, g); out_i != out_end; ++out_i) {
        Edge e = *out_i;
        Vertex w = target(e, g);
        if (visited[w] == 666) {
            arch_type[e] = "tree"; // like in tarjan's algorithm
            StrongConnect(g, w,sccs,Points, Counter);
            lowPt[v] = lowPt[v]< lowPt[w]?lowPt[v]:lowPt[w];
            lowVine[v] = lowVine[v]< lowVine[w]?lowVine[v]:lowVine[w];
        } else if (isReachable(g, w, v)) {// TODO Ancestor problem
            arch_type[e] = "frond";
            lowPt[v] = lowPt[v]< visited[w]?lowPt[v]:visited[w];
        } else if (visited[w] < visited[v]) {
            arch_type[e] = "vine";
            if (std::find(Points.begin(), Points.end(), w) != Points.end()) {
                lowVine[v] = lowVine[v]< visited[w]?lowVine[v]:visited[w];
            }
        }

    }
    if (lowPt[v] == visited[v] && lowVine[v] == visited[v]) {
        StronglyConnected newComp;
        std::cout << "Strongly connected component with root: " << " ";
        //   boost::add_vertex(v,newComp);
        while(!Points.empty() && visited[Points.back()] >= visited[v]){
            Vertex x = Points.back();
            Points.pop_back();
            std::cout << id[x] << " ";
            //     boost::add_vertex(x,newComp);
        }
        std::cout<<std::endl;
        // sccs.push_back(newComp);
    }
}

void Algorithms::Tarjan::Biconnect(SCC_Graph &g, Vertex &v, int &Counter) {

}

void Algorithms::Tarjan::ApplyBiconnectivity(SCC_Graph &g) {

}



