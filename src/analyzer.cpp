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
#include <fstream>
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

std::string Analyzer::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
} 

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

void Analyzer::benchmark_comparison(bool &write_to_file,bool isCsv, std::string &inputDirectory){
		Visualize v;
		boost::filesystem::path full_path(boost::filesystem::current_path());
		std::string dateTime = currentDateTime();
		std::string file_location_csv = full_path.string() + "/data/experiment_" + dateTime +".csv";
        std::string file_location = full_path.string() + "/logs/experiment-" + dateTime +".log";
        std::ofstream logFile;
		logFile.open(file_location,std::ios::app);
		logFile << "This log is created with the " + inputDirectory + " directory" << std::endl;
		logFile.close();
		if(write_to_file){
			v.writeTableBanner(PROGRAM_WIDTH,file_location);
		}else{
			v.printTableBanner(PROGRAM_WIDTH);
		}
		
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
		if(write_to_file){
			if(isCsv){
				v.writeExperimentRow_CSV(PROGRAM_WIDTH,id,vertex,edges,results,file_location_csv);
			}
			v.writeExperimentRow(PROGRAM_WIDTH,id,vertex,edges,results,file_location);
		}else{
			v.printExperimentRow(PROGRAM_WIDTH,id,vertex,edges,results);
		}
		
	}
		
}
