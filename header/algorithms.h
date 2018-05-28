#include "./../header/graphcomponent.h"
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

class Algorithms{

    private:
        typedef UtilityStructs::VertexProperty VertexProperty;
        typedef UtilityStructs::EdgeProperties EdgeProperties;
        typedef UtilityStructs::PVertexProperties PVertexProperties;  
        typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
                                    VertexProperty, EdgeProperties>
            inputGraph;
        typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
                                    PVertexProperties, EdgeProperties>
            SCC_Graph;
        typedef boost::graph_traits<SCC_Graph>::vertex_descriptor Vertex;
        typedef boost::graph_traits<SCC_Graph>::edge_descriptor Edge;
        typedef boost::property_map<SCC_Graph, std::size_t PVertexProperties::*>::type marked;
        typedef property_map<SCC_Graph, std::size_t PVertexProperties::*>::type v_p;
        typedef property_map<SCC_Graph,std::string EdgeProperties::*>::type e_p;

    public:
    Algorithms(){};
    void ApplyDFS(SCC_Graph &g);
    void DepthFirstSearch(SCC_Graph &g, Vertex &v,int &Counter);
    
    void ApplySCC(SCC_Graph &g);
    void StrongConnect(SCC_Graph &g,Vertex &v,std::deque<Vertex> &Points, int &Counter);

};

