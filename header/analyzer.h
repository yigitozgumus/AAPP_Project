#ifndef ANALYZER_H
#define ANALYZER_H

/**
 * This class will test the algorithms with different settings to create a basis for analysis
 * and a comparison baseline
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
		Visualize v;
		Analyzer(){};
		Analyzer(std::string &dirname){
			graphList = getInputList(dirname);
			std::string message = "All the graph files are imported";
			v.printLine(PROGRAM_WIDTH,message);
		}

    	std::vector<std::string> getInputList(std::string &dirPath);
    	void benchmark_comparison();
    	

};

class Timer{
	public:
		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::duration<float> duration;
		std::chrono::time_point<std::chrono::steady_clock> finish;
		
		Timer(){
			start = std::chrono::high_resolution_clock::now();
		}
		float stop(){
			finish = std::chrono::high_resolution_clock::now();
			duration = finish-start;
			float ms = duration.count() * 1000.0f;
			std::cout << "Timer took " << ms << " ms" << std::endl;
			return ms;
		}
		~Timer(){
			finish = std::chrono::high_resolution_clock::now();
			duration = finish-start;
			float ms = duration.count() * 1000.0f;
			std::cout << "Timer took " << ms << " ms" << std::endl; 
		}
		
};

#endif
