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
/**
 * @brief 
 * 
 */
void Application::run(Session &s)
{  
    v.printProgramEntry(s);
    welcomeScreen(s);
}
/**
 * @brief 
 * 
 */
void Application::welcomeScreen(Session &s)
{
    
    int choice = 0;
    v.printLine( "Please choose the operation you want to perform:");
    v.printLine( " 1-) Generate a Graph set");
    v.printLine( " 2-) Run an Experiment");
    v.printLine( " 3-) Run Debug Mode");
    v.printLine( " 0-) Exit the Application");
    v.printProgramBottom();
    std::cout << "|>> ";
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        generateGraph(s);
        break;
    case 2: 
        runExperiment(s);
        break;
    case 3:
        runDebugMode(s);
        break;
    case 0:
        break;
    default:
        break;
    }
}
/**
 * @brief 
 * 
 */
std::string Application::generateGraph(Session &s)
{
    
    v.printProgramEntry(s);
    v.printLine("");
    std::string Program = "python src/generate_graph_directories.py";
    std::string dir_name;
    std::string numOfGraph;
    std::string single_class;
    int singleC = 0;
    v.printLine("Please enter the name of the output folder:");
    std::cout << "|>> ";
    std::cin >> dir_name;
    s.graph_dir = dir_name;
    v.printLine("Please enter the number of graph instances for each node class:");
    std::cout << "|>> ";
    std::cin >> numOfGraph;
    v.printLine("Would you like to choose the node classes specifically ?:( y or n )");
    std::cout << "|>> ";
    std::cin >> single_class;
    if(single_class == "n")
    {   
        v.printLine("The output folder is: " + dir_name);
        v.printLine("The number of graphs per each class is " + numOfGraph);
        std::string command;
        command = Program + " " + numOfGraph + " " + dir_name;
        std::system(command.c_str());
         v.printLine("Press c to Continue, q to quit");
        std::cout << "|>> ";
        std::string branch;
        std::cin >> branch;
        if(branch == "c"){
            v.printProgramEntry(s);
            welcomeScreen(s);
        }else if (branch == "q"){
            return dir_name;
        }
    }else{
        v.printProgramEntry(s);
        v.printLine("");
        v.printLine("The Graph Classes are below:");
        v.printLine("1-) 5-50 Nodes");
        v.printLine("2-) 50-100 Nodes");
        v.printLine("3-) 100-500 Nodes");
        v.printLine("4-) 500-1000 Nodes");
        v.printLine("Please type the required classes with their index seperated by spaces:");
        v.printLine("Additionally, If you want to create a graph with an exact number of nodes, type the number of nodes with '#' prefix : #56");
        std::cout << "|>>";
        std::string classes = "";
        std::cin.ignore();
        std::getline(std::cin,classes);
        std::string command;
        if(classes.compare(0,1,"#")==0){
             command = Program + " " + numOfGraph + " " + dir_name + " --node " + classes.substr(1) ;
        }else{
             command = Program + " " + numOfGraph + " " + dir_name + " --single " + classes ;
        }
        
        std::system(command.c_str());
        v.printLine("Press c to Continue, q to quit");
        std::cout << "|>> ";
        std::string branch;
        std::cin >> branch;
        if(branch == "c"){
            v.printProgramEntry(s);
            welcomeScreen(s);
        }else if (branch == "q"){
            return dir_name;
        }
    }
    return dir_name;
}
/**
 * @brief 
 * 
 */
std::string Application::runExperiment(Session &s){
    
    std::string dir;
    std::string csv;
    csv = "None";
    v.printProgramEntry(s);
    v.printLine("");
    v.printLine("Please enter the name of the graph directory: (Relative)");
    v.printProgramBottom();
    std::cout << "|>> ";
    std::cin >> dir;
    boost::filesystem::path full_path(boost::filesystem::current_path());
    std::string full_p_dir = full_path.string() + "/" + dir;
    v.printProgramEntry(s);
    v.printLine("");
    v.printLine("The " + full_p_dir + " directory will be used");
    v.printLine("");
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
      csv =  a.benchmark_comparison(true, true, full_p_dir);
      s.csv = csv;
    }
    v.printLine("Press c to Continue, q to quit");
    std::cout << "|>> ";
    std::string branch;
    std::cin >> branch;
    if(branch == "c"){
        v.printProgramEntry(s);
        welcomeScreen(s);
    }else if (branch == "q"){
        return csv;
    }
    return csv;
}
/**
 * @brief 
 * 
 */
void Application::runDebugMode(Session &s){
    
    v.printProgramEntry(s);
    v.printLine("");
    v.printLine("Please enter the name (path) of the graph file you want to debug (Relative) ");
    std::string fl;
    v.printProgramBottom();
    std::cout << "|>> ";
    std::cin >> fl;
    v.printProgramEntry(s);
    v.printLine("");
    v.printProgramBottom();
    v.printLine("Which method do you want to use ?");
    v.printLine("1-) Tarjan's Algorithm");
    v.printLine("2-) Nuutila's Algorithms");
    v.printLine("3-) Pearce's Algorithms");
    v.printLine("4-) All of them");
    v.printProgramBottom();
    std::cout << "|>> ";
    int choice = 1;
    std::cin >> choice;
    Analyzer a;
    if(choice == 1){
        v.printProgramEntry(s);
        a.solve_with_tarjan(fl);
    }else if(choice == 2){
        v.printProgramEntry(s);
        a.solve_with_nuutila(fl);
    }else if(choice == 3){
        v.printProgramEntry(s);
        a.solve_with_pearce(fl);
    }else if(choice == 4){
        v.printProgramEntry(s);
        a.solve_with_all(fl);
    }
    v.printLine("Press c to Continue, q to quit");
    std::cout << "|>> ";
    std::string branch;
    std::cin >> branch;
    if(branch == "c"){
        v.printProgramEntry(s);
        welcomeScreen(s);
    }else if (branch == "q"){
        return ;
    }
}