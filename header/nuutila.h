#ifndef NUUTILA_H
#define NUUTILA_H

#include "./graphcomponent.h"
#include "./analyzer.h"
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

class Nuutila : protected GraphComponent
{
  public:
    theGraph n;
    std::vector<theGraph> experiment;
    Nuutila(){}; 
    Nuutila(std::string filename): GraphComponent(filename){
        read_graph_file(filename, n);
    }

    //TODO
    void solve(std::vector<std::string> methods, int graphNum);
    
    void print_sccs(UtilityStructs::StorageItems &s);

    void print_graph();

    UtilityStructs::StorageItems ApplySCC_Original();

    void Visit( Vertex_t &v,
                std::vector<Vertex_t> &Points,
                std::vector<int> &root,
                std::vector<int> &visited,
                std::vector<bool> &isComponent,
                int &Counter,
                int &stackCount);

    UtilityStructs::StorageItems ApplySCC_v1();

    UtilityStructs::StorageItems ApplySCC_v2();

    void Visit_v1(Vertex_t &v,
                  std::vector<Vertex_t> &Points,
                  std::vector<int> &root,
                  std::vector<int> &visited,
                  std::vector<bool> &isComponent,
                  int &Counter,
                  int &stackCount);

    void Visit_v2(Vertex_t &v,
                  std::vector<int> &Points,
                  std::vector<int> &root,
                  std::vector<int> &visited,
                  std::vector<bool> &isComponent ,
                  int &Counter,
                  int &stackCount);
};

#endif
