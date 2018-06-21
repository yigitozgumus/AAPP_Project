#include "./../header/visualize.h"

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

std::string Visualize::centered(int width, const std::string& str) {
    int len = str.length();
    if(width < len) { return str; }

    int diff = width - len;
    int pad1 = diff/2;
    int pad2 = diff - pad1;
    return string(pad1, ' ') + str + string(pad2, ' ');
}

void Visualize::printTableBanner(int width){
	int cell = (width-18) /17 ; 
	int remainder = (width-18) % 17 ;
	std::cout << std::string(width,'-') + "\n|"
			  << setw(width-2) << left << "Result Table" << "|\n"
			  << std::string(width,'-') + "\n|"
			  << setw(cell) << left << "id" << "|"
			  << setw(cell) << left << "Vertex" << "|"
			  << setw(cell) << left << "Edge" << "|"
			  << setw(cell) << left << "Tj T" << "|"
			  << setw(cell) << left << "Tj S" << "|"
			  << setw(cell) << left << "N_0 T" << "|"
			  << setw(cell) << left << "N_0 S" << "|"
			  << setw(cell) << left << "N_1 T" << "|"
			  << setw(cell) << left << "N_1 S" << "|"
			  << setw(cell) << left << "N_2 T" << "|"
			  << setw(cell) << left << "N_2 S" << "|"
			  << setw(cell) << left << "P_0 T" << "|"
			  << setw(cell) << left << "P_0 S" << "|"
			  << setw(cell) << left << "P_1 T" << "|"
			  << setw(cell) << left << "P_1 S" << "|"
			  << setw(cell) << left << "P_2 T" << "|"
			  << setw(cell) << left << "P_2 S" 
			  << std::string(remainder,' ') << "|\n";
}
void Visualize::printTableSeperator(int width){
	std::cout << std::string(width,'-') + "\n";
}
void Visualize::printProgramEntry(int width){
	std::system("clear");
	std::cout << std::string(width,'=') + "\n="
			  << centered(width-2,"Advanced Algorithms and Parallel Programming Project") << "=\n"
			  << std::string(width,'=') + "\n";
}

void Visualize::printLine(int width,std::string &message){
	std::cout << "|" << setw(width-2) << left << message << "|\n";
}
