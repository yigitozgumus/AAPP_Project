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
    Visualize v;
    std::string result = "start";
    boost::filesystem::path full_path(boost::filesystem::current_path());
    std::string inputDirectory = full_path.string() + "/" + argv[1];
     while(result != "q"){
       v.printProgramEntry(PROGRAM_WIDTH);
    //  v.printTableBanner(PROGRAM_WIDTH);
       std::string s = "Please enter a key to start the analysis: ";
       v.printLine(PROGRAM_WIDTH,s);
       std::cin >> result;
     }
     float ms ;
     UtilityStructs::Timer t;
     Analyzer a(inputDirectory);
    a.benchmark_comparison();
    ms = t.stop();
    std::cout << "Estimated time is: " << ms/1000 << " seconds" << std::endl;
    return 0;
}
