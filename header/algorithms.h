#include "./../header/typedef.h"
//STL
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
//Boost
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list_io.hpp>
#include <boost/graph/property_iter_range.hpp>
#include <boost/graph/copy.hpp>
#include <boost/property_map/property_map.hpp>


using namespace std;
using namespace boost;

class Algorithms {

public:
    Algorithms() = default;;

    class Tarjan {
    public:
        Tarjan() = default;;

        void ApplyDFS(SCC_Graph &g);

        void DepthFirstSearch(SCC_Graph &g, Vertex_t &v, int &Counter);

        void ApplyBiconnectivity(SCC_Graph &g);

        void Biconnect(SCC_Graph &g, Vertex_t &v, int &Counter);

        void ApplySCC(SCC_Graph &g);

        bool isReachable(SCC_Graph &g, Vertex_t &source, Vertex_t &target);

        void
        StrongConnect(SCC_Graph &g, Vertex_t &v, std::vector<StronglyConnected> &sccs, std::vector<Vertex_t> &Points,
                      int &Counter);
    };

    class Nuutila {
    public:
        Nuutila() = default;

        void ApplySCC_Original(Nuutila_Graph &g);

        void Visit(Nuutila_Graph &g, Vertex_n &v,std::vector<bool> &sccs, std::stack<Vertex_n> &Points,int &Counter);

        void ApplySCC_v1(Nuutila_Graph &g);

        void ApplySCC_v2(Nuutila_Graph &g);

        void Visit_v1(Nuutila_Graph &g, Vertex_n &v,std::vector<StronglyConnected> &sccs, std::stack<Vertex_n> &Points,int &Counter);

        void Visit_v2(Nuutila_Graph &g, Vertex_n &v,std::vector<StronglyConnected> &sccs, std::stack<Vertex_n> &Points,int &Counter);
    };

};

