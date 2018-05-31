//STL
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list_io.hpp>
#include <boost/graph/property_iter_range.hpp>
#include <boost/graph/copy.hpp>
#include <boost/property_map/property_map.hpp>

#include "./../header/algorithms.h"

using namespace boost;

int main(int, char *argv[])
{
    std::string filename = argv[1];
    std::ifstream infile(filename);
    GraphComponent test(filename);
    GraphComponent test2(filename);
    Algorithms::Tarjan t;
    Algorithms::Nuutila n;
    //t.ApplyDFS(test.theGraph);
    t.ApplySCC(test.theGraph);
    n.ApplySCC_Original(test2.NGraph);
    test2.print_graph_file_nuutila();
    n.ApplySCC_v1(test.NGraph);
    //test.ApplyDFS();
    //test.print_graph_file();
   test.print_graph_file_nuutila();
  //  Vertex_t v = vertex(0,test.theGraph);
   // Vertex_t w = vertex(7,test.theGraph);
   // std::cout << t.isReachable(test.theGraph,v,w) << std::endl;

    return 0;
}