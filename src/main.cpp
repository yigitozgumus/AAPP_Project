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

#include "./../header/graphcomponent.h"

using namespace boost;

int main(int, char *argv[])
{
    std::string filename = argv[1];
    std::ifstream infile(filename);
    GraphComponent test(filename);

    return 0;
}