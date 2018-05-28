#include "../header/algorithms.h"
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



