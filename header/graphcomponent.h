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

namespace UtilityStructs {
    struct TVertexProperties {
        std::size_t index;
        // std::string label;
        std::size_t num;
        std::size_t lowPt;
        std::size_t lowVine;
    };
    struct NVertexProperties{
        std::size_t index;
        std::size_t num;
        std::size_t visited;
        bool isComponent;
    };

    struct EdgeProperties {
        EdgeProperties(const std::string &n) : name(n) {}

        std::string name;
    };

    struct VertexProperty {
        std::size_t index;

    };
}

class GraphComponent {

private:
    typedef UtilityStructs::VertexProperty VertexProperty;
    typedef UtilityStructs::EdgeProperties EdgeProperties;
    typedef UtilityStructs::TVertexProperties TVertexProperties;
    typedef UtilityStructs::NVertexProperties NVertexProperties;
    typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
            VertexProperty, EdgeProperties>
            inputGraph;

    typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
            TVertexProperties, EdgeProperties>
            SCC_Graph;
    typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
            NVertexProperties, EdgeProperties>
            Nuutila_Graph;
    typedef boost::graph_traits<SCC_Graph>::vertex_descriptor Vertex_t;
    typedef boost::graph_traits<Nuutila_Graph>::vertex_descriptor Vertex_n;
    typedef boost::graph_traits<SCC_Graph>::edge_descriptor Edge;
    typedef property_map<SCC_Graph, std::size_t TVertexProperties::*>::type v_p;
    typedef property_map<Nuutila_Graph, std::size_t NVertexProperties::*>::type v_p_n;
    typedef property_map<Nuutila_Graph, bool NVertexProperties::*>::type v_p_nb;
    typedef property_map<SCC_Graph, std::string EdgeProperties::*>::type e_p;
    typedef property_map<Nuutila_Graph, std::size_t EdgeProperties::*>::type e_p_n;

public:
    SCC_Graph theGraph;
    Nuutila_Graph NGraph;
    

    GraphComponent(std::string filename) {
        std::ifstream infile_t(filename);
        read_graph_file_tarjan(infile_t, theGraph);
        std::ifstream infile_n(filename);
        read_graph_file_nuutila(infile_n,NGraph);
        std::cout << "The graph has been imported from the file: "
                  << filename << std::endl;
        //print_graph_file();
        std::cout << "The graph has been imported from the file: "
                  << filename
                  << std::endl;
       // print_graph_file_nuutila();
    }

    void print_graph_file();
    void print_graph_file_nuutila();
    void read_graph_file_tarjan(std::istream &in, SCC_Graph &g);
    void read_graph_file_nuutila(std::istream &in, Nuutila_Graph &g);

};