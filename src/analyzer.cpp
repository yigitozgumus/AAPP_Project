#include "./../header/analyzer.h"

//STL
 #include <iostream>
 #include <vector>
 #include <string>
 #include <fstream>
 #include <sstream>
 #include <iterator>
 //Boost
 #include <boost/config.hpp>
 #include <boost/graph/strong_components.hpp>
 #include <boost/graph/adjacency_list.hpp>
 #include <boost/graph/graphviz.hpp>
 #include <boost/graph/graph_utility.hpp>
 #include <boost/graph/adjacency_list_io.hpp>
 #include <boost/graph/property_iter_range.hpp>
 #include <boost/graph/copy.hpp>
 #include <boost/property_map/property_map.hpp>


using namespace boost::system;
namespace filesys = boost::filesystem;
#ifndef USING_BOOST
#define USING_BOOST
#endif
 

std::vector<std::string> Analyzer::getInputList(std::string &dirPath){

	std::vector<std::string> inputGraphs;
	try {
		if (filesys::exists(dirPath) && filesys::is_directory(dirPath)){
			filesys::recursive_directory_iterator iter(dirPath);
 			filesys::recursive_directory_iterator end;
 
			// Iterate till end
			while (iter != end){
				inputGraphs.push_back(iter->path().string());
				
				error_code ec;
				// Increment the iterator to point to next entry in recursive iteration
				iter.increment(ec);
				if (ec) {
					std::cerr << "Error While Accessing : " << iter->path().string() << " :: " << ec.message() << '\n';
				}
			}

		}
	}catch (std::system_error & e){
		std::cerr << "Exception :: " << e.what();
	}
	return inputGraphs;
	}

