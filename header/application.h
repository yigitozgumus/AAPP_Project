#ifndef APPLICATION_H
#define APPLICATION_H

#include "./visualize.h"
#include "./analyzer.h"
#include "./utilities.h"


class Application{
    public:
    Application(){};
    void run();
    void welcomeScreen();
    void generateGraph();
    void runExperiment();
    void runDebugMode();
};
#endif 