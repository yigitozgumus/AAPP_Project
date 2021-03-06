#ifndef TYPEDEF_H
#define TYPEDEF_H
#define PROGRAM_WIDTH 180

//Boost
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list_io.hpp>
#include <boost/graph/property_iter_range.hpp>
#include <boost/graph/copy.hpp>
#include <boost/property_map/property_map.hpp>

#include <time.h>


using namespace boost;
/**
 * @brief This struct is used to contain information about the last generated graph directive and the experiment result
 * for users
 * 
 */
struct Session{
	std::string graph_dir;
	std::string csv;
};

namespace UtilityStructs
{
/**
 * @brief This struct contains the edge type info for Tarjan's SCC Algorithm
 * 
 */
struct EdgeProperty
{
	EdgeProperty(const std::string &n) : name(n) {}
	std::string name;
};
/**
 * @brief This struct contains the vertex index info that are used by all of the algorithms
 * 
 */
struct VertexProperty
{
	std::size_t index;
};
/**
 * @brief This struct is used to store all of the output information of algorithms for later use
 * 
 */
struct StorageItems
{
	std::size_t total_bytes;
	float duration;
	int vertexCount;
	int edgeCount;
	std::vector<int> auxilary;
};
/**
 * @brief This class is used to measure the execution time of a executed function with the same scope.
 * 
 */
class Timer
{
  public:
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::duration<float> duration;
	std::chrono::time_point<std::chrono::steady_clock> finish;

	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	float stop()
	{
		finish = std::chrono::high_resolution_clock::now();
		duration = finish - start;
		float ms = duration.count() * 1000.0f;

		return ms;
	}
	~Timer()
	{
		finish = std::chrono::high_resolution_clock::now();
		duration = finish - start;
		float ms = duration.count() * 1000.000f;
	}
};

} // namespace UtilityStructs

typedef UtilityStructs::VertexProperty VertexProperty;
typedef UtilityStructs::EdgeProperty EdgeProperty;

typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS,
							  VertexProperty, EdgeProperty>
	theGraph;

typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
typedef boost::graph_traits<theGraph>::edge_descriptor Edge_t;
typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
typedef property_map<theGraph, std::size_t VertexProperty::*>::type v_p;
typedef property_map<theGraph, std::string EdgeProperty::*>::type e_p;

#endif