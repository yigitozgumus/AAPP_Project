
#include "./graphcomponent.h"
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

class Nuutila : protected GraphComponent
{
  public:
    theGraph n;
    Nuutila() = default;
    Nuutila(std::string filename){
        read_graph_file(filename, n);
    }

    void ApplySCC_Original(theGraph &g);

    void Visit(theGraph &g, Vertex_t &v, std::vector<bool> &sccs, std::stack<Vertex_t> &Points, int &Counter);

    void ApplySCC_v1(theGraph &g);

    void ApplySCC_v2(theGraph &g);

    void Visit_v1(theGraph &g, Vertex_t &v,  std::stack<Vertex_t> &Points, int &Counter);

    void Visit_v2(theGraph &g, Vertex_t &v,  std::vector<Vertex_t> &Points, int &Counter);
};