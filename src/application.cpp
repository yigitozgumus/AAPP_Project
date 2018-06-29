#include "./../header/application.h"
#include "./../header/visualize.h"
#include "./../header/analyzer.h"
#include "./../header/utilities.h"

//STL
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <dirent.h>
#include <cstring>
#include <memory>

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list_io.hpp>
#include <boost/graph/property_iter_range.hpp>
#include <boost/graph/copy.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/filesystem.hpp>

void Application::mainLoop()
{
    Visualize v;
    std::string result = "start";
    v.printProgramEntry();
    welcomeScreen();
}

void Application::welcomeScreen()
{
    Visualize v;
    int choice = 0;
    v.printLine( "Please choose the operation you want to perform:");
    v.printLine( " 1-) Generate a Graph set");
    v.printLine( " 2-) Run an Experiment");
    v.printLine( " 3-) Visualize a Graph");
    v.printLine( " 0-) Exit the Application");
    v.printProgramBottom();
    std::cout << "|>> ";
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        generateGraph();
        break;
    case 2: 
        runExperiment();
        break;
    case 3: visualizeGraph();
        break;
    case 0:
        break;
    default:
        break;
    }
}

void Application::generateGraph()
{
    Visualize v;
    v.printProgramEntry();
    v.printLine("");
    std::string Program = "python src/generate_graph_directories.py";
    std::string dir_name;
    std::string numOfGraph;
    std::string single_class;
    int singleC = 0;
    v.printLine("Please enter the name of the output folder:");
    std::cout << "|>> ";
    std::cin >> dir_name;
    v.printLine("Please enter the number of graph instances for each node class:");
    std::cout << "|>> ";
    std::cin >> numOfGraph;
    v.printLine("Would you like to choose the node classes specifically ?:( y or n )");
    std::cout << "|>> ";
    std::cin >> single_class;
    if(single_class == "n")
    {   
        v.printLine("The output folder is: " + dir_name);
        v.printLine("The number of graphs per each class is" + numOfGraph);
        std::string command;
        command = Program + " " + numOfGraph + " " + dir_name;
        std::system(command.c_str());
         v.printLine("Press c to Continue, q to quit");
        std::cout << "|>> ";
        std::string branch;
        std::cin >> branch;
        if(branch == "c"){
            v.printProgramEntry();
            welcomeScreen();
        }else if (branch == "q"){
            return ;
        }
    }else{
        v.printProgramEntry();
        v.printLine("");
        v.printLine("The Graph Classes are below:");
        v.printLine("1-) 5-50 Nodes");
        v.printLine("2-) 50-100 Nodes");
        v.printLine("3-) 100-500 Nodes");
        v.printLine("4-) 500-1000 Nodes");
        v.printLine("Please type the required classes with their index seperated by spaces:");
        std::cout << "|>>";
        std::string classes = "";
        std::cin.ignore();
        std::getline(std::cin,classes);
        std::string command;
        command = Program + " " + numOfGraph + " " + dir_name + " --single " + classes ;
        std::system(command.c_str());
        v.printLine("Press c to Continue, q to quit");
        std::cout << "|>> ";
        std::string branch;
        std::cin >> branch;
        if(branch == "c"){
            v.printProgramEntry();
            welcomeScreen();
        }else if (branch == "q"){
            return ;
        }
    }
}

void Application::runExperiment(){
    Visualize v;
    std::string dir;
    v.printProgramEntry();
    v.printLine("");
    v.printLine("Please enter the name of the graph directory: (Relative)");
    v.printProgramBottom();
    std::cout << "|>> ";
    std::cin >> dir;
    boost::filesystem::path full_path(boost::filesystem::current_path());
    std::string full_p_dir = full_path.string() + "/" + dir;
    v.printProgramEntry();
    v.printLine("");
    v.printLine("The " + full_p_dir + " directory will be used");
    v.printLine("Please choose the option you want to execute:");
    v.printLine("1-) Run the Experiment (default option, only terminal table)");
    v.printLine("2-) Run the Experiment, save the result to the logs directory");
    v.printLine("3-) Run the Experiment, save the result as log and csv file to the data directory");
    v.printProgramBottom();
    std::cout << "|>> ";
    int choice = 1;
    std::cin >> choice;
    Analyzer a(full_p_dir);
    if(choice == 1){
        a.benchmark_comparison(false,false,full_p_dir);
    }else if(choice == 2){
        a.benchmark_comparison(true, false, full_p_dir);
    }else if(choice == 3){
        a.benchmark_comparison(true, true, full_p_dir);
    }
    v.printLine("Press c to Continue, q to quit");
    std::cout << "|>> ";
    std::string branch;
    std::cin >> branch;
    if(branch == "c"){
        v.printProgramEntry();
        welcomeScreen();
    }else if (branch == "q"){
        return ;
    }
    
}

void Application::visualizeGraph(){
    Visualize v;
    v.printLine("Will be implemented soon");
}