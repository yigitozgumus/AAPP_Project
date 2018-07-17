#ifndef TARJAN_H
#define TARJAN_H

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
/**
 * @brief This class contains the implementation of algorithms from the Tarjan's paper
 * 
 */
class Tarjan : protected GraphComponent
{
  public:
    theGraph t;
    std::vector<theGraph> experiment;

    Tarjan() {};
    Tarjan(std::string filename): GraphComponent(filename){
        read_graph_file(filename,t);
    }
    //TODO
    void solve(int graphNum);

    void print_graph();

    void ApplyDFS();

    void DepthFirstSearch(Vertex_t &v, int &Counter,std::vector<int> &visited);

    bool isReachable( Vertex_t &source, Vertex_t &target);

    UtilityStructs::StorageItems applyBiconnectivity();

    void biconnect(Vertex_t &v,
                  std::vector<Edge_t> &edges, 
                  int &Counter,
                  std::vector<std::vector<Edge_t> > &components,
                  std::vector<int> &visited,
                  std::vector<int> &lowPt,
                  int &stackCount);

    UtilityStructs::StorageItems ApplySCC(bool debugMode);


    void StrongConnect( Vertex_t &v, 
                      std::vector<Vertex_t> &Points,
                      int &Counter,
                      std::vector<int> &visited, 
                      std::vector<int> &lowPt, 
                      std::vector<int> &lowVine,
                      int &stackCount,
                      bool debugMode);
};

#endif