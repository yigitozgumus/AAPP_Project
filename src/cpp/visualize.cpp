#include "./../../header/visualize.h"

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <fstream>


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
	return std::string(pad1, ' ') + str + std::string(pad2, ' ');
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
		   <<std::setw(cell) << std::left << id << "|"
		   <<std::setw(cell) << std::left << vertex << "|"
		   <<std::setw(cell) << std::left << edge << "|";
	for (std::vector<UtilityStructs::StorageItems>::iterator it = rowInfo.begin(); it != rowInfo.end() - 1; it++)
	{
		buffer <<std::setw(cell) << std::left << (*it).duration << "|"
			   <<std::setw(cell) << std::left << (float)(*it).total_bytes / 1024 << "|";
	}
	buffer << std::setw(cell) << std::left << rowInfo[6].duration << "|"
		   << std::setw(cell) << std::left << (float)rowInfo[6].total_bytes / 2014
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
		   <<std::setw(cell) << std::left << id << "|"
		   <<std::setw(cell) << std::left << vertex << "|"
		   <<std::setw(cell) << std::left << edge << "|";
	for (std::vector<UtilityStructs::StorageItems>::iterator it = rowInfo.begin(); it != rowInfo.end() - 1; it++)
	{
		buffer <<std::setw(cell) << std::left << (*it).duration << "|"
			   <<std::setw(cell) << std::left << (float)(*it).total_bytes / 1024 << "|";
	}
	buffer <<std::setw(cell) << std::left << rowInfo[6].duration << "|"
		   <<std::setw(cell) << std::left << (float)rowInfo[6].total_bytes / 1024
		   << std::string(remainder, ' ') + "|\n|"
		   << std::string(width - 2, '-') + "|\n";
	std::ofstream logFile;
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
	std::ofstream logFile;
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
		   <<std::setw(width - 2) << std::left << "Result Table"
		   << "|\n"
		   << std::string(width, '-') + "\n|"
		   <<std::setw(cell) << std::left << "id"
		   << "|"
		   <<std::setw(cell) << std::left << "Vertex"
		   << "|"
		   <<std::setw(cell) << std::left << "Edge"
		   << "|"
		   <<std::setw(cell) << std::left << "Tj T"
		   << "|"
		   <<std::setw(cell) << std::left << "Tj S"
		   << "|"
		   <<std::setw(cell) << std::left << "N_0 T"
		   << "|"
		   <<std::setw(cell) << std::left << "N_0 S"
		   << "|"
		   <<std::setw(cell) << std::left << "N_1 T"
		   << "|"
		   <<std::setw(cell) << std::left << "N_1 S"
		   << "|"
		   <<std::setw(cell) << std::left << "N_2 T"
		   << "|"
		   <<std::setw(cell) << std::left << "N_2 S"
		   << "|"
		   <<std::setw(cell) << std::left << "P_0 T"
		   << "|"
		   <<std::setw(cell) << std::left << "P_0 S"
		   << "|"
		   <<std::setw(cell) << std::left << "P_1 T"
		   << "|"
		   <<std::setw(cell) << std::left << "P_1 S"
		   << "|"
		   <<std::setw(cell) << std::left << "P_2 T"
		   << "|"
		   <<std::setw(cell) << std::left << "P_2 S"
		   << std::string(remainder, ' ') << "|\n"
		   << std::string(width, '-') << "\n";
	std::ofstream logFile;
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
			  <<std::setw(width - 2) << std::left << "Result Table"
			  << "|\n"
			  << std::string(width, '-') + "\n|"
			  <<std::setw(cell) << std::left << "id"
			  << "|"
			  <<std::setw(cell) << std::left << "Vertex"
			  << "|"
			  <<std::setw(cell) << std::left << "Edge"
			  << "|"
			  <<std::setw(cell) << std::left << "Tj T"
			  << "|"
			  <<std::setw(cell) << std::left << "Tj S"
			  << "|"
			  <<std::setw(cell) << std::left << "N_0 T"
			  << "|"
			  <<std::setw(cell) << std::left << "N_0 S"
			  << "|"
			  <<std::setw(cell) << std::left << "N_1 T"
			  << "|"
			  <<std::setw(cell) << std::left << "N_1 S"
			  << "|"
			  <<std::setw(cell) << std::left << "N_2 T"
			  << "|"
			  <<std::setw(cell) << std::left << "N_2 S"
			  << "|"
			  <<std::setw(cell) << std::left << "P_0 T"
			  << "|"
			  <<std::setw(cell) << std::left << "P_0 S"
			  << "|"
			  <<std::setw(cell) << std::left << "P_1 T"
			  << "|"
			  <<std::setw(cell) << std::left << "P_1 S"
			  << "|"
			  <<std::setw(cell) << std::left << "P_2 T"
			  << "|"
			  <<std::setw(cell) << std::left << "P_2 S"
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
void Visualize::printProgramEntry(Session &s)
{
	std::system("clear");
	std::cout << std::string(width, '=') + "\n="
			  << centered(width - 2, "Advanced Algorithms and Parallel Programming Project") << "=\n"
			  << std::string(width, '=') + "\n";
	std::stringstream buffer_dir;
	std::stringstream buffer_csv;
	buffer_dir << std::setw(50) << std::left << "The last graph directory created in this session";
	buffer_dir << ": " << s.graph_dir ;
	buffer_csv << std::setw(50) << std::left << "The last experiment ran in this session";
	buffer_csv << ": " << s.csv;
	printLine("");
	printLine(buffer_dir.str());
	printLine(buffer_csv.str());
	printLine("");

}

void Visualize::printLine( std::string message)
{
	std::cout << "|" <<std::setw(width - 2) << std::left << message << "|\n";
}
