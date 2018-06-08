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

    void print_graph();

    void DFS();

    void visit(Vertex_t &v,
              std::vector<int> &visited,
              int &index);

    void Pea_Find_SCC1();

    void visit_scc1(Vertex_t &v,
                    std::vector<bool> &root,
                    std::vector<bool> &visited,
                    std::vector<int> &rindex,
                    std::vector<bool> &inComponent,
                    std::vector<Vertex_t> &Stack,
                    int &index,
                    int &c);

    void Pea_Find_SCC2();

    void visit_scc2(Vertex_t &v,
                    std::vector<bool> &root,
                    std::vector<int> &rindex,
                    std::vector<Vertex_t> &Stack,
                    int &index,
                    int &c);

    void Pea_Find_SCC3();

    void visit_scc3(Vertex_t &v,
                    std::vector<bool> &root,
                    std::vector<int> &rindex,
                    std::vector<Vertex_t> &vStack,
                    std::vector<int> &iStack,
                    int &index,
                    int &c);

    void visitLoop();

    void beginVisiting(Vertex_t &v,
                       std::vector<bool> &root,
                       std::vector<int> &rindex,
                       std::vector<Vertex_t> &vStack,
                       std::vector<int> &iStack,
                       int &index);

    void finishVisiting(Vertex_t &v);

    void beginEdge(Vertex_t &v);

    void finishEdge(Vertex_t &v);
};
