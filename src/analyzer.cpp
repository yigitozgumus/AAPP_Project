#include "./../header/analyzer.h"
#include "./../header/tarjan.h"
#include "./../header/nuutila.h"
#include "./../header/pearce.h"

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
				if(!filesys::is_directory(iter->path().string())){
					inputGraphs.push_back(iter->path().string());
				}				
						
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

void Analyzer::benchmark_comparison(){
		Visualize v;
		v.printTableBanner(PROGRAM_WIDTH);
		UtilityStructs::StorageItems r_t;
		
	for (std::vector<std::string>::iterator it = graphList.begin(); it != graphList.end(); it++){
	std::vector<UtilityStructs::StorageItems> results;	
		Tarjan t(*it);
		r_t = t.ApplySCC();
		int vertex = r_t.vertexCount;
		int edges = r_t.edgeCount;
		int id = it - graphList.begin();
		results.push_back(r_t);
		Nuutila n(*it);
		r_t = n.ApplySCC_Original();
		results.push_back(r_t);
		r_t = n.ApplySCC_v1();
		results.push_back(r_t);
		r_t = n.ApplySCC_v2();
		results.push_back(r_t);
		Pearce p(*it);
		r_t = p.Pea_Find_SCC1();
		results.push_back(r_t);
		r_t = p.Pea_Find_SCC2();
		results.push_back(r_t);
		r_t = p.Pea_Find_SCC3();
		results.push_back(r_t);
		
		v.printExperimentRow(PROGRAM_WIDTH,id,vertex,edges,results);
	}
		
}
