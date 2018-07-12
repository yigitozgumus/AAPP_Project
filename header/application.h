#ifndef APPLICATION_H
#define APPLICATION_H

#include "./visualize.h"
#include "./analyzer.h"
#include "./utilities.h"


class Application{
    public:
    Visualize v;
    Application(){
    };
    void run(Session &s);
    void welcomeScreen(Session &s);
    std::string generateGraph(Session &s);
    std::string runExperiment(Session &s);
    void runDebugMode(Session &s);
    void analyzeExperiment(Session &s);
};
#endif 