#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "./utilities.h"


class Visualize{
	public:
		Visualize(){};
		std::string centered(int width, const std::string& str);
		void printProgramEntry(int width);
    	void printTableBanner(int width);
    	void printTableSeperator(int width);
    	void printLine(int width,std::string &message);
    	void printExperimentRow(int width,int &id,int &vertex,int &edge,std::vector<UtilityStructs::StorageItems> &rowInfo);
};

#endif