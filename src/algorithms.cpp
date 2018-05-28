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

void Algorithms::Tarjan::ApplyDFS(SCC_Graph &g){
    typedef boost::graph_traits<SCC_Graph>::vertex_descriptor Vertex;
    Vertex theFirst = *(vertices(g).first);
    int Counter = 0;
    std::cout << "Discovery Order is: " << std::endl;
    DepthFirstSearch(g,theFirst,Counter);
    
}

void Algorithms::Tarjan::DepthFirstSearch(SCC_Graph &g, Vertex &v,int &Counter){
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

void Algorithms::Tarjan::ApplySCC(SCC_Graph &g){
    v_p visited = get(&PVertexProperties::num, g);
    typedef boost::graph_traits<SCC_Graph>::vertex_descriptor Vertex;
    typedef boost::graph_traits<SCC_Graph>::vertex_iterator vertex_iter ;
    std::pair<vertex_iter, vertex_iter> vp;
    std::deque<Vertex> Points;
    int Counter = 0;
    for(vp = vertices(g); vp.first != vp.second; vp.first++){
        Vertex v = *vp.first ;
        if(visited[v] == 666){
            StrongConnect(g,v,Points,Counter);
        }
    }
}

void Algorithms::Tarjan::StrongConnect(SCC_Graph &g,Vertex &v,std::deque<Vertex> &Points, int &Counter){
    v_p visited = get(&PVertexProperties::num,g);
    v_p lowPt = get(&PVertexProperties::lowPt,g);
    v_p lowVine = get(&PVertexProperties::lowVine,g);
    e_p arch_type = get(&EdgeProperties::name, g);
    Counter++;
    visited[v] = lowPt[v] = lowVine[v] = Counter;
    Points.push_back(v);
     typedef boost::graph_traits<SCC_Graph>::edge_descriptor Edge;
    boost::graph_traits<SCC_Graph>::out_edge_iterator out_i, out_end;
    for(boost::tie(out_i,out_end)= out_edges(v,g); out_i != out_end;++out_i){
        Edge e = *out_i;
        Vertex w = target(e,g);
        if(visited[w] == 666){
            arch_type[e] = "tree"; // like in tarjan's algorithm
            StrongConnect(g,w,Points,Counter);
            lowPt[v] = std::min(lowPt[v],lowPt[w]);
            lowVine[v] = std::min(lowVine[v],lowVine[w]);
        }else if(true){// TODO Ancestor problem
            arch_type[e] = "frond";
            lowPt[v] = std::min(lowPt(v),visited(w));
        }else if(visited[w] <visited[v]){
            arch_type[e] = "vine";
            if (std::find(Points.begin(),Points.end(),w) != Points.end()){
                lowVine[v] = std::min(lowVine[v],visited[w]);
            }
        }
    }if(lowPt[v] ==visited[v] && lowVine[v] == visited[v]){
        //TODO implementation
    
    }
    

    
}



