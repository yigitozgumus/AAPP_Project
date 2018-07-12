
#include "./../header/application.h"
#include "./../header/utilities.h"


int main(int, char *argv[])
{
    Session s;
    s.graph_dir = "None";
    s.csv = "None";
    Application a;
    a.run(s);
    return 0;
}
