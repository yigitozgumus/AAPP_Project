/**
 * This class will test the algorithms with different settings to create a basis for analysis
 * and a comparison baseline
 * 
 */

#include "./graphcomponent.h"
//STL
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
//Boost
#include <boost/config.hpp>
#include <boost/filesystem.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list_io.hpp>
#include <boost/graph/property_iter_range.hpp>
#include <boost/graph/copy.hpp>
#include <boost/property_map/property_map.hpp>



class Analyzer{
	public:
		std::vector<std::string> graphList;
		Analyzer(){};
		Analyzer(std::string &dirname){
			graphList = getInputList(dirname);
			for (auto str : graphList)
				std::cout << str << std::endl;
			std::cout << " I am created" << std::endl;
		}

    	std::vector<std::string> getInputList(std::string &dirPath);

};