#include "./graphcomponent.h"

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
  typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS, 
                                    boost::no_property, boost::no_property>
            StronglyConnected;
  typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
                                    boost::no_property, boost::no_property>
            biconnectivity;