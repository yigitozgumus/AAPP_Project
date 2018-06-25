#include "./../header/visualize.h"

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <fstream>

using namespace std;

std::string Visualize::centered(int width, const std::string &str)
{
	int len = str.length();
	if (width < len)
	{
		return str;
	}

	int diff = width - len;
	int pad1 = diff / 2;
	int pad2 = diff - pad1;
	return string(pad1, ' ') + str + string(pad2, ' ');
}

void Visualize::printExperimentRow(int id,
								   int vertex,
								   int edge,
								   std::vector<UtilityStructs::StorageItems> rowInfo)
{
	int cell = (width - 18) / 17;
	int remainder = (width - 18) % 17;
	std::stringstream buffer;
	buffer << "|"
		   << setw(cell) << left << id << "|"
		   << setw(cell) << left << vertex << "|"
		   << setw(cell) << left << edge << "|";
	for (std::vector<UtilityStructs::StorageItems>::iterator it = rowInfo.begin(); it != rowInfo.end() - 1; it++)
	{
		buffer << setw(cell) << left << (*it).duration << "|"
			   << setw(cell) << left << (float)(*it).total_bytes / 1024 << "|";
	}
	buffer << setw(cell) << left << rowInfo[6].duration << "|"
		   << setw(cell) << left << (float)rowInfo[6].total_bytes / 2014
		   << std::string(remainder, ' ') + "|\n|"
		   << std::string(width - 2, '-') + "|";
	std::cout << buffer.str() << std::endl;
}
void Visualize::writeExperimentRow(int id,
								   int vertex,
								   int edge,
								   std::vector<UtilityStructs::StorageItems> rowInfo,
								   std::string filename)
{
	int cell = (width - 18) / 17;
	int remainder = (width - 18) % 17;
	std::stringstream buffer;
	buffer << "|"
		   << setw(cell) << left << id << "|"
		   << setw(cell) << left << vertex << "|"
		   << setw(cell) << left << edge << "|";
	for (std::vector<UtilityStructs::StorageItems>::iterator it = rowInfo.begin(); it != rowInfo.end() - 1; it++)
	{
		buffer << setw(cell) << left << (*it).duration << "|"
			   << setw(cell) << left << (float)(*it).total_bytes / 1024 << "|";
	}
	buffer << setw(cell) << left << rowInfo[6].duration << "|"
		   << setw(cell) << left << (float)rowInfo[6].total_bytes / 2014
		   << std::string(remainder, ' ') + "|\n|"
		   << std::string(width - 2, '-') + "|\n";
	ofstream logFile;
	logFile.open(filename, std::ios::app);
	logFile << buffer.str();
	logFile.close();
}
void Visualize::writeExperimentRow_CSV(int id,
									   int vertex,
									   int edge,
									   std::vector<UtilityStructs::StorageItems> rowInfo,
									   std::string filename)
{
	int cell = (width - 18) / 17;
	int remainder = (width - 18) % 17;
	std::stringstream buffer;
	buffer << id << "," << vertex << "," << edge << ",";
	for (std::vector<UtilityStructs::StorageItems>::iterator it = rowInfo.begin(); it != rowInfo.end() - 1; it++)
	{
		buffer << (*it).duration << ","
			   << (float)(*it).total_bytes / 1024 << ",";
	}
	buffer << rowInfo[6].duration << ","
		   << (float)rowInfo[6].total_bytes / 1024 << "\n";
	ofstream logFile;
	logFile.open(filename, std::ios::app);
	logFile << buffer.str();
	logFile.close();
}

void Visualize::writeTableBanner( std::string filename)
{
	std::system("clear");
	int cell = (width - 18) / 17;
	int remainder = (width - 18) % 17;
	std::stringstream buffer;
	buffer << std::string(width, '-') + "\n|"
		   << setw(width - 2) << left << "Result Table"
		   << "|\n"
		   << std::string(width, '-') + "\n|"
		   << setw(cell) << left << "id"
		   << "|"
		   << setw(cell) << left << "Vertex"
		   << "|"
		   << setw(cell) << left << "Edge"
		   << "|"
		   << setw(cell) << left << "Tj T"
		   << "|"
		   << setw(cell) << left << "Tj S"
		   << "|"
		   << setw(cell) << left << "N_0 T"
		   << "|"
		   << setw(cell) << left << "N_0 S"
		   << "|"
		   << setw(cell) << left << "N_1 T"
		   << "|"
		   << setw(cell) << left << "N_1 S"
		   << "|"
		   << setw(cell) << left << "N_2 T"
		   << "|"
		   << setw(cell) << left << "N_2 S"
		   << "|"
		   << setw(cell) << left << "P_0 T"
		   << "|"
		   << setw(cell) << left << "P_0 S"
		   << "|"
		   << setw(cell) << left << "P_1 T"
		   << "|"
		   << setw(cell) << left << "P_1 S"
		   << "|"
		   << setw(cell) << left << "P_2 T"
		   << "|"
		   << setw(cell) << left << "P_2 S"
		   << std::string(remainder, ' ') << "|\n"
		   << std::string(width, '-') << "\n";
	ofstream logFile;
	logFile.open(filename, std::ios::app);
	logFile << buffer.str();
	logFile.close();
}

void Visualize::printTableBanner()
{
	std::system("clear");
	int cell = (width - 18) / 17;
	int remainder = (width - 18) % 17;
	std::cout << std::string(width, '-') + "\n|"
			  << setw(width - 2) << left << "Result Table"
			  << "|\n"
			  << std::string(width, '-') + "\n|"
			  << setw(cell) << left << "id"
			  << "|"
			  << setw(cell) << left << "Vertex"
			  << "|"
			  << setw(cell) << left << "Edge"
			  << "|"
			  << setw(cell) << left << "Tj T"
			  << "|"
			  << setw(cell) << left << "Tj S"
			  << "|"
			  << setw(cell) << left << "N_0 T"
			  << "|"
			  << setw(cell) << left << "N_0 S"
			  << "|"
			  << setw(cell) << left << "N_1 T"
			  << "|"
			  << setw(cell) << left << "N_1 S"
			  << "|"
			  << setw(cell) << left << "N_2 T"
			  << "|"
			  << setw(cell) << left << "N_2 S"
			  << "|"
			  << setw(cell) << left << "P_0 T"
			  << "|"
			  << setw(cell) << left << "P_0 S"
			  << "|"
			  << setw(cell) << left << "P_1 T"
			  << "|"
			  << setw(cell) << left << "P_1 S"
			  << "|"
			  << setw(cell) << left << "P_2 T"
			  << "|"
			  << setw(cell) << left << "P_2 S"
			  << std::string(remainder, ' ') << "|\n"
			  << std::string(width, '-') << std::endl;
}

void Visualize::printTableSeperator()
{
	std::cout << std::string(width, '-') + "\n";
}
void Visualize::printProgramBottom()
{	
	std::cout << "|"<< std::string(width-2, '-') << "|" << "\n";
}
void Visualize::printProgramEntry()
{
	std::system("clear");
	std::cout << std::string(width, '=') + "\n="
			  << centered(width - 2, "Advanced Algorithms and Parallel Programming Project") << "=\n"
			  << std::string(width, '=') + "\n";
}

void Visualize::printLine( std::string message)
{
	std::cout << "|" << setw(width - 2) << left << message << "|\n";
}
