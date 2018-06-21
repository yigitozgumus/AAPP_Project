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
#include <boost/filesystem.hpp>

#include "./../header/tarjan.h"
#include "./../header/nuutila.h"
#include "./../header/pearce.h"
#include "./../header/analyzer.h"
#include "./../header/visualize.h"

using namespace boost;

#include <dirent.h>
#include <cstring>
#include <memory>
 

int main(int, char *argv[])
{   
    // Visualize v;
    // std::string result = "start";
    // boost::filesystem::path full_path(boost::filesystem::current_path());
    // std::string inputDirectory = full_path.string() + "/" + argv[1];
    //  while(result != "q"){
    //    v.printProgramEntry(PROGRAM_WIDTH);
    // //  v.printTableBanner(PROGRAM_WIDTH);
    //    std::string s = "Please enter a function: ";
    //    v.printLine(PROGRAM_WIDTH,s);
    //    std::cin >> result;
    //  }
    //  Analyzer a(inputDirectory);
    // a.benchmark_comparison();

    std::string filename = argv[1];
    Tarjan t(filename);
    Nuutila n(filename);
    Pearce p(filename);
    t.ApplySCC();
    n.ApplySCC_Original();
    n.ApplySCC_v1();
    n.ApplySCC_v2();
    p.Pea_Find_SCC1();
    p.Pea_Find_SCC2();
    p.Pea_Find_SCC3();
    //t.ApplyDFS(test.theGraph);
    //t.ApplySCC(test.theGraph);
    
    //test.ApplyDFS();
    //test.print_graph_file();
   
  //  Vertex_t v = vertex(0,test.theGraph);
   // Vertex_t w = vertex(7,test.theGraph);
   // std::cout << t.isReachable(test.theGraph,v,w) << std::endl;

    return 0;
}
