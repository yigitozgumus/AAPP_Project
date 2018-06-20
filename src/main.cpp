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
#include "./../header/analyzer.h"
#include "./../header/visualize.h"

using namespace boost;

#include <dirent.h>
#include <cstring>
#include <memory>
 

int main(int, char *argv[])
{   
    Visualize v;
    v.printProgramEntry(120);
    // std::string result = "start";
    // std::system("clear");
    // std::string programEntry = std::string(100,'=') + 
    //         "\n=" +  
    //         std::string(23,' ') + 
    //         "Advanced Algorithms and Parallel Programming Project" + 
    //         std::string(23,' ') + 
    //         "=\n" + 
    //         std::string(100,'=') + 
    //         "\n\n";
    // std::cout << programEntry;
    // while(result != "q"){
    //   std::system("clear");
    //   std::cout << programEntry;
    //   std::cout << "Please enter a function: ";
    //   std::cin >> result;
    // }
    std::string dirname = "/Users/yigitozgumus/Code/Workspace/ClionProjects/SCC/input";
    Analyzer a(dirname);
    // std::vector<std::string> test = a.getInputList(dirname);
    // for (auto str : test)
    //     std::cout << str << std::endl;
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
