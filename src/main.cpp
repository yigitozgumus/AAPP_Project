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

#include "./../header/tarjan.h"
#include "./../header/nuutila.h"
#include "./../header/pearce.h"

using namespace boost;

int main(int, char *argv[])
{
     std::string filename = argv[1];
     Tarjan test(filename);
    // test.print_graph();
     test.ApplyDFS();
     test.ApplySCC();
    // test.print_graph();
     Nuutila test2(filename);
     test2.ApplySCC_Original();
     test2.ApplySCC_v1();
     test2.ApplySCC_v2();
    // test2.print_graph();
    Pearce test3(filename);
    test3.DFS();
     test3.Pea_Find_SCC1();
     test3.Pea_Find_SCC2();
     test3.Pea_Find_SCC3();
    
   // test.print_graph_file();
    //t.ApplyDFS(test.theGraph);
    //t.ApplySCC(test.theGraph);
    
    //test.ApplyDFS();
    //test.print_graph_file();
   
  //  Vertex_t v = vertex(0,test.theGraph);
   // Vertex_t w = vertex(7,test.theGraph);
   // std::cout << t.isReachable(test.theGraph,v,w) << std::endl;

    return 0;
}
