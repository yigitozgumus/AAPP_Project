
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
    Nuutila(){}; 
    Nuutila(std::string filename): GraphComponent(filename){
        read_graph_file(filename, n);
    }

    void solve(std::vector<std::string> methods, int graphNum);
    
    void print_sccs(std::vector<int> &root);

    void print_graph();

    void ApplySCC_Original();

    void Visit( Vertex_t &v,
                std::vector<Vertex_t> &Points,
                std::vector<int> &root,
                std::vector<int> &visited,
                std::vector<bool> &isComponent,
                int &Counter);

    void ApplySCC_v1();

    void ApplySCC_v2();

    void Visit_v1(Vertex_t &v,
                  std::vector<Vertex_t> &Points,
                  std::vector<int> &root,
                  std::vector<int> &visited,
                  std::vector<bool> &isComponent,
                  int &Counter);

    void Visit_v2(Vertex_t &v,
                  std::vector<Vertex_t> &Points,
                  std::vector<int> &root,
                  std::vector<int> &visited,
                  std::vector<bool> &isComponent ,
                  int &Counter);
};
