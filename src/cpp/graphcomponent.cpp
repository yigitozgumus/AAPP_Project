#include "./../../header/graphcomponent.h"
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

void GraphComponent::read_graph_file(std::string filename, theGraph &g)
{
    std::ifstream infile(filename);
    v_p id = get(&VertexProperty::index, g);
    typedef graph_traits<theGraph>::vertex_descriptor Vertex;
    typedef graph_traits<theGraph>::vertices_size_type size_type;
    size_type n_vertices;
    infile >> n_vertices; // read in number of vertices
    std::vector<Vertex_t> vertex_set(n_vertices);
    for (size_type i = 0; i < n_vertices; ++i)
        vertex_set[i] = add_vertex(g);

    size_type u, v;
    while (infile >> u)
        if (infile >> v)
            add_edge(vertex_set[u], vertex_set[v], EdgeProperty(""), g);
        else
            break;
    //initialize the nums for the DFS
    boost::graph_traits<theGraph>::vertex_iterator vi, viend;
    int vnum = 0;
    for (boost::tie(vi, viend) = vertices(g); vi != viend; ++vi)
        id[*vi] = vnum++;
}

void GraphComponent::print_graph_file(theGraph &graph)
{
    v_p id = get(&VertexProperty::index, graph);

    property_map<theGraph, std::string EdgeProperty::*>::type
        name = get(&EdgeProperty::name, graph);
    graph_traits<theGraph>::vertex_iterator i, end;
    graph_traits<theGraph>::out_edge_iterator ei, edge_end;
    for (boost::tie(i, end) = vertices(graph); i != end; ++i)
    {
        std::cout << id[*i] + 1 << " ";
        for (boost::tie(ei, edge_end) = out_edges(*i, graph); ei != edge_end; ++ei)
            std::cout << " -" << name[*ei] << "-> " << id[target(*ei, graph)] + 1 << "  ";
        std::cout << std::endl;
    }
    // print_edges(theGraph, id);
}
