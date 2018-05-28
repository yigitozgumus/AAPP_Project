#include "../header/algorithms.h"
//STL
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <stack>
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

void Algorithms::ApplyDFS(SCC_Graph &g){
    typedef boost::graph_traits<SCC_Graph>::vertex_descriptor Vertex;
    Vertex theFirst = *(vertices(g).first);
    int Counter = 0;
    std::cout << "Discovery Order is: " << std::endl;
    DepthFirstSearch(g,theFirst,Counter);
    
}

void Algorithms::DepthFirstSearch(SCC_Graph &g, Vertex &v,int &Counter){
    v_p visited = get(&PVertexProperties::num, g);
    v_p id = get(&PVertexProperties::index, g);
    e_p arch_type = get(&EdgeProperties::name, g);
    Counter++;
    visited[v] = Counter;
    std::cout << "Node(" <<id[v] << ") --> " << visited[v] << std::endl;
    typedef boost::graph_traits<SCC_Graph>::edge_descriptor Edge;
    boost::graph_traits<SCC_Graph>::out_edge_iterator out_i, out_end;
    for(boost::tie(out_i,out_end) = out_edges(v,g); out_i != out_end; ++out_i){
        Edge e = *out_i;
        Vertex w = target(e,g);
        if(visited[w] == 666){
            arch_type[e] = "forward";
            //std::cout << "Node(" <<id[w] << ") --> " << visited[w] << std::endl;
            DepthFirstSearch(g,w,Counter);  
        }else if (visited[w] < visited[v]){
            arch_type[e] = "backward";
        }
    }
}

void Algorithms::ApplySCC(SCC_Graph &g){
    v_p visited = get(&PVertexProperties::num, g);
    typedef boost::graph_traits<SCC_Graph>::vertex_descriptor Vertex;
    typedef boost::graph_traits<SCC_Graph>::vertex_iterator v_i, v_e ;
    std::stack<Vertex> Points;
    for(boost::tie(v_i,v_e) = vertices(g); v_i != v_e; v_i++){
        Vertex v = *v_i ;
        if(visited[v_i] == 666){
            StrongConnect(g,v);
        }
    }
}

void Algorithms::StrongConnect(SCC_Graph &g,Vertex &v,std::stack<Vertex &Points, int &Counter){
    v_p visited = get(&PVertexProperties::num,g);
    v_p lowPt = get(&PVertexProperties::lowPt,g);
    v_p LowVine = get(&PVertexProperties::lowVine,g);
    Counter++;
    visited[v] = lowPt[v] = LowVine[v] = Counter;
    Points.push(v);
     typedef boost::graph_traits<SCC_Graph>::edge_descriptor Edge;
    boost::graph_traits<SCC_Graph>::out_edge_iterator out_i, out_end;
    for(boost::tie(out_i,out_end)= out_edges(v,g); out_i != out_end: ++out_i){
        Edge e = *out_i;
        Vertex w = target(e,g);
        if(visited[w] == 666){
            arch_type[e] = "tree"; // like in tarjan's algorithm
            StrongConnect(g,w,Points,Counter);
            lowPt[v]
        }
    }    

    
}



