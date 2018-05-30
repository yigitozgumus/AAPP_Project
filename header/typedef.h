#include "./graphcomponent.h"

typedef UtilityStructs::VertexProperty VertexProperty;
typedef UtilityStructs::EdgeProperties EdgeProperties;
typedef UtilityStructs::TVertexProperties TVertexProperties;
typedef UtilityStructs::NVertexProperties NVertexProperties;
typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
        VertexProperty, EdgeProperties>
        inputGraph;
typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
        NVertexProperties, EdgeProperties>
        Nuutila_Graph;
typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
        TVertexProperties, EdgeProperties>
        SCC_Graph;
typedef boost::graph_traits<SCC_Graph>::vertex_descriptor Vertex_t;
typedef boost::graph_traits<Nuutila_Graph>::vertex_descriptor Vertex_n;
typedef boost::graph_traits<SCC_Graph>::edge_descriptor Edge;
typedef boost::property_map<SCC_Graph, std::size_t TVertexProperties::*>::type marked;
typedef property_map<SCC_Graph, std::size_t TVertexProperties::*>::type v_p;
typedef property_map<SCC_Graph, std::string EdgeProperties::*>::type e_p;
typedef property_map<Nuutila_Graph, std::size_t NVertexProperties::*>::type v_p_n;
typedef property_map<Nuutila_Graph, bool NVertexProperties::*>::type v_p_nb;
typedef property_map<Nuutila_Graph, std::size_t EdgeProperties::*>::type e_p_n;
typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
        TVertexProperties, EdgeProperties>
        StronglyConnected;
typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
        boost::no_property, boost::no_property>
        biconnectivity;