#include "./../header/graphcomponent.h"
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

void GraphComponent::read_graph_file(std::istream &in, Graph &g)
{
    typedef graph_traits<inputGraph>::vertex_descriptor Vertex;
    typedef graph_traits<inputGraph>::vertices_size_type size_type;
    size_type n_vertices;
    in >> n_vertices; // read in number of vertices
    std::vector<Vertex> vertex_set(n_vertices);
    for (size_type i = 0; i < n_vertices; ++i)
        vertex_set[i] = add_vertex(g);

    size_type u, v;
    while (in >> u)
        if (in >> v)
            add_edge(vertex_set[u], vertex_set[v], EdgeProperties("undefined"), g);
        else
            break;
}

void GraphComponent::print_graph_file()
{
    property_map<inputGraph, std::size_t VertexProperty::*>::type
        id = get(&VertexProperty::index, theGraph);
    property_map<inputGraph, std::string EdgeProperties::*>::type
        name = get(&EdgeProperties::name, theGraph);
    boost::graph_traits<inputGraph>::vertex_iterator vi, viend;
    int vnum = 0;
    for (boost::tie(vi, viend) = vertices(theGraph); vi != viend; ++vi)
        id[*vi] = vnum++;
    graph_traits<inputGraph>::vertex_iterator i, end;
    graph_traits<inputGraph>::out_edge_iterator ei, edge_end;
    for (boost::tie(i, end) = vertices(theGraph); i != end; ++i)
    {
        std::cout << id[*i] << " ";
        for (boost::tie(ei, edge_end) = out_edges(*i, theGraph); ei != edge_end; ++ei)
            std::cout << " --" << name[*ei] << "--> " << id[target(*ei, theGraph)] << "  ";
        std::cout << std::endl;
    }
    print_edges(theGraph, id);
}
//typedef boost::property < boost::vertex_name_t, std::string> VertexProperty;
//typedef graph_traits<inputGraph>::vertex_descriptor vertex_t;
//typedef graph_traits<inputGraph>::edge_descriptor edge_t;

template <typename Graph1, typename Graph2>
void DepthFirstSearch(Graph1 &input)
{
}

template <typename Graph1, typename Graph2>
void BiConnectivity(Graph1 &input, Graph2 &output)
{
}

template <typename Graph1, typename Graph2>
void StrongConnect(Graph1 &input, Graph2 &output)
{
    //TODO
}
