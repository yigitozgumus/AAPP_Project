#ifndef TARJAN_H
#define TARJAN_H

#include "./graphcomponent.h" //STL
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

    void print_sccs(std::vector<int> &rindex);

    void ApplyDFS();

    void DepthFirstSearch(Vertex_t &v, int &Counter,std::vector<int> &visited);

    void ApplyBiconnectivity(theGraph &g);

    void Biconnect(theGraph &g, Vertex_t &v, int &Counter);

    void ApplySCC();

    bool isReachable( Vertex_t &source, Vertex_t &target);

    void StrongConnect( Vertex_t &v, std::vector<Vertex_t> &Points,
                  int &Counter,std::vector<int> &visited, std::vector<int> &lowPt, std::vector<int> &lowVine);
};

#endif