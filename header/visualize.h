#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "./utilities.h"

/**
 * @brief This class is used to visualize the information that are gathered from the algorithms
 * 
 */
class Visualize{
	
	public:
		int width;
		Visualize(){
			width = PROGRAM_WIDTH;
		};
		std::string centered(int width, const std::string &str);
		void printProgramEntry(Session &s);
    	void printTableBanner();
    	void printTableSeperator();
		void printProgramBottom();
    	void printLine(std::string message);
    	void printExperimentRow(int id,int vertex,int edge,std::vector<UtilityStructs::StorageItems> rowInfo);
    	void writeProgramEntry(std::string filename);
    	void writeTableBanner(std::string filename);
    	void writeTableSeperator(std::string filename);
    	void writeLine(std::string message,std::string filename);
    	void writeExperimentRow(int id,int vertex,int edge,std::vector<UtilityStructs::StorageItems> rowInfo,std::string filename);
        void writeExperimentRow_CSV(int id,int vertex,int edge,std::vector<UtilityStructs::StorageItems> rowInfo,std::string filename);
};

#endif