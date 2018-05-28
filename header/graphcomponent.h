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

namespace UtilityStructs{
    struct PVertexProperties
    {
        std::size_t index;
        boost::default_color_type color;
       // std::string label;
        std::size_t num;
        std::size_t lowPt;
        std::size_t lowVine;
    };
    struct EdgeProperties
    {
        EdgeProperties(const std::string &n) : name(n) {}
        std::string name;
    };
    struct VertexProperty
    {
        std::size_t index;
        
    };
}

class GraphComponent{
  
    private:
        typedef UtilityStructs::VertexProperty VertexProperty;
        typedef UtilityStructs::EdgeProperties EdgeProperties;
        typedef UtilityStructs::PVertexProperties PVertexProperties;  
        typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
                                    VertexProperty, EdgeProperties>
            inputGraph;
        
        typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
                                    PVertexProperties, EdgeProperties>
            SCC_Graph;
        typedef boost::graph_traits<SCC_Graph>::vertex_descriptor Vertex;
        typedef boost::graph_traits<SCC_Graph>::edge_descriptor Edge;
        typedef boost::property_map<SCC_Graph, std::size_t PVertexProperties::*>::type marked;
        typedef property_map<SCC_Graph, std::size_t PVertexProperties::*>::type v_p;
        typedef property_map<SCC_Graph,std::string EdgeProperties::*>::type e_p;
        
    public:
        SCC_Graph theGraph;

        GraphComponent(std::string filename){
        std::ifstream infile(filename);
        read_graph_file(infile, theGraph);
        std::cout <<"\n" << "The graph has been imported from the file: " 
        << filename << "\n" << std::endl;
        print_graph_file();
        }

        void print_graph_file();
        void read_graph_file(std::istream &in, SCC_Graph &g);
        
};