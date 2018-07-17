#ifndef ANALYZER_H
#define ANALYZER_H

/**
 * This class will test the algorithms with different settings to create a basis for analysis
 * and a comparison baseline. It also provides the same settings for different types of algorithms
 * to provide a optimal debug mode experience.
 * 
 */

#include "./graphcomponent.h"
#include "./visualize.h"
//STL
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <chrono>
#include <thread>
#include <time.h>
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


/**
 * @brief This class is mainly responsible for the experiment functionality. It also provides the wrapped 
 * experiment methods. 
 * 
 */
class Analyzer{

	public:
		std::vector<std::string> graphList;
		Visualize v;
		Analyzer(){};
		Analyzer(std::string &dirname){
			graphList = getInputList(dirname);
			//v.printTableSeperator();
			//std::string message = "All the graph files are imported";
			//v.printLine(message);
		}

    	std::vector<std::string> getInputList(std::string &dirPath);
    	std::string currentDateTime();
    	void solve_with_all(std::string &inputFile);
    	void solve_with_tarjan(std::string &inputFile);
    	void solve_with_nuutila(std::string &inputFile);
    	void solve_with_pearce(std::string &inputFile);
    	std::string benchmark_comparison(bool write_to_file,bool isCsv,std::string &inputDirectory);
    	

};


#endif
