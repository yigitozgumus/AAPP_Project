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

namespace UtilityStructs {

    struct EdgeProperty {
        EdgeProperty(const std::string &n) : name(n) {}
        std::string name;
    };

    struct VertexProperty {
        std::size_t index;

    };
}

typedef UtilityStructs::VertexProperty VertexProperty;
typedef UtilityStructs::EdgeProperty EdgeProperty;

typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
                              VertexProperty, EdgeProperty>
    theGraph;

typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
typedef property_map<theGraph, std::size_t VertexProperty::*>::type v_p;
typedef property_map<theGraph, std::string EdgeProperty::*>::type e_p;