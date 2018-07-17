
#include "./../../header/application.h"
#include "./../../header/utilities.h"

/**
 * @brief This is the main function of the application. Its only functionality is to execute the 
 * actual application
 * 
 * @param argv 
 * @return int 
 */
int main(int, char *argv[])
{
    Session s;
    s.graph_dir = "None";
    s.csv = "None";
    Application a;
    a.run(s);
    return 0;
}
