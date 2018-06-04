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

class Pearce : protected GraphComponent
{ 
  public:
    theGraph p;
    Pearce() = default;
    Pearce(std::string filename){
      read_graph_file(filename,p);
    }

    void DFS(theGraph &g, Vertex_t &v);

    void visit(Vertex_t &v);

    void Pea_Find_SCC1(theGraph &g, Vertex_t &v);

    void visit_scc1(Vertex_t &v);

    void Pea_Find_SCC2(theGraph &g, Vertex_t &v);

    void visit_scc2(Vertex_t &v);

    void Pea_Find_SCC3(theGraph &g, Vertex_t &v);

    void visit_scc3(Vertex_t &v);

    void visitLoop();

    void beginvisiting(Vertex_t &v);

    void finishVisiting(Vertex_t &v);

    void beginEdge(Vertex_t &v);

    void finishEdge(Vertex_t &v);
};
