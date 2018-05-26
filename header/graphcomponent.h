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
    struct SCCVertexProperties
    {
        std::size_t index;
        std::string label;
        int num;
        int lowPt;
        int lowVine;
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

class GraphComponent
{
  
  private:
    typedef UtilityStructs::VertexProperty VertexProperty;
    typedef UtilityStructs::EdgeProperties EdgeProperties;
    typedef UtilityStructs::SCCVertexProperties SCCVertexProperties;  
    typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
                                  VertexProperty, EdgeProperties>
        inputGraph;
    typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
                                  SCCVertexProperties, EdgeProperties>
        SCC_Graph;

    inputGraph theGraph;
public:
  void print_graph_file();
  void read_graph_file(std::istream &in, inputGraph &g);

  GraphComponent(std::string filename)
  {
      std::ifstream infile(filename);
      read_graph_file(infile, theGraph);
      std::cout <<"\n" << "The graph has been imported from the file: " 
      << filename << "\n" << std::endl;
      print_graph_file();
    }
};