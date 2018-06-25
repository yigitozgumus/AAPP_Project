#ifndef APPLICATION_H
#define APPLICATION_H

#include "./visualize.h"
#include "./analyzer.h"
#include "./utilities.h"


class Application{
    public:
    Application(){};
    void mainLoop();
    void welcomeScreen();
    void generateGraph();
    void runExperiment();
};
#endif // !