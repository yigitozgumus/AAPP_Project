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

// This struct will be used for the Tarjan Algorithm implementatation
struct SCCVertexProperties{
    std::size_t index;
    std::string label;
    int num;
    int lowPt;
    int lowVine;
};
struct VertexProperty
{
    std::size_t index;
    boost::default_color_type color;
};

//typedef boost::property < boost::vertex_name_t, std::string> VertexProperty;

typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
SCCVertexProperties, boost::no_property> SCC_Graph;


typedef boost::adjacency_list<boost::vecS, boost::listS,boost::directedS,
VertexProperty, boost::no_property> inputGraph;

typedef graph_traits<inputGraph>::vertex_descriptor vertex_t;
typedef graph_traits<inputGraph>::edge_descriptor edge_t;

template <typename Graph>
void read_graph_file(std::istream &in, Graph &g)
{
    typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
    typedef typename graph_traits<Graph>::vertices_size_type size_type;
    size_type n_vertices;
    in >> n_vertices; // read in number of vertices
    std::vector<Vertex> vertex_set(n_vertices);
    for (size_type i = 0; i < n_vertices; ++i)
        vertex_set[i] = add_vertex(g);

    size_type u, v;
    while (in >> u)
        if (in >> v)
            add_edge(vertex_set[u], vertex_set[v], g);
        else
            break;
}

int main(int, char* argv[]){
    std::string filename = argv[1];
    std::ifstream infile(filename);
    //typedef boost::graph_traits<inputGraph>::vertices_size_type size_v;
    //size_v vertices;
    //infile >> vertices;
    //std::cout << vertices << std::endl;
    inputGraph test;
    read_graph_file(infile,test);
    property_map<inputGraph, std::size_t VertexProperty::*>::type
        id = get(&VertexProperty::index, test);
    boost::graph_traits<inputGraph>::vertex_iterator vi, viend;
    int vnum = 0;
    for (boost::tie(vi, viend) = vertices(test); vi != viend; ++vi)
        id[*vi] = vnum++;
    graph_traits<inputGraph>::vertex_iterator i, end;
    graph_traits<inputGraph>::out_edge_iterator ei, edge_end;
    for (boost::tie(i, end) = vertices(test); i != end; ++i)
    {
        std::cout << id[*i] << " ";
        for (boost::tie(ei, edge_end) = out_edges(*i, test); ei != edge_end; ++ei)
            std::cout << " --" << "--> " << id[target(*ei, test)] << "  ";
        std::cout << std::endl;
    }
    print_edges(test, id);
    return 0;
}