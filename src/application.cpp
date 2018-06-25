#include "./../header/application.h"
#include "./../header/visualize.h"
#include "./../header/analyzer.h"
#include "./../header/utilities.h"

//STL
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <dirent.h>
#include <cstring>
#include <memory>

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list_io.hpp>
#include <boost/graph/property_iter_range.hpp>
#include <boost/graph/copy.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/filesystem.hpp>



void Application::mainLoop()
{
    Visualize v;
    std::string result = "start";
    boost::filesystem::path full_path(boost::filesystem::current_path());
    while (result != "q")
    {
        v.printProgramEntry(PROGRAM_WIDTH);
          v.printLine(PROGRAM_WIDTH,"");
        std::string s = ": ";
        std::cin >> result;
    }
}