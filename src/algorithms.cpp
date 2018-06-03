#include "./../header/algorithms.h"
//STL
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <deque>
#include <algorithm>
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
//======================================================================================================================
//                                                      TARJAN
//======================================================================================================================
void Algorithms::Tarjan::ApplyDFS(SCC_Graph &g) {
    typedef boost::graph_traits<SCC_Graph>::vertex_descriptor Vertex;
    Vertex_t theFirst = *(vertices(g).first);
    int Counter = 0;
    std::cout << "Discovery Order is: " << std::endl;
    DepthFirstSearch(g, theFirst, Counter);

}

void Algorithms::Tarjan::DepthFirstSearch(SCC_Graph &g, Vertex_t &v, int &Counter) {
    v_p visited = get(&TVertexProperties::num, g);
    v_p id = get(&TVertexProperties::index, g);
    e_p arch_type = get(&EdgeProperties::name, g);
    Counter++;
    visited[v] = static_cast<unsigned long>(Counter);
    std::cout << "Node(" << id[v] << ") --> " << visited[v] << std::endl;
    typedef boost::graph_traits<SCC_Graph>::edge_descriptor Edge;
    boost::graph_traits<SCC_Graph>::out_edge_iterator out_i, out_end;
    for (boost::tie(out_i, out_end) = out_edges(v, g); out_i != out_end; ++out_i) {
        Edge e = *out_i;
        Vertex_t w = target(e, g);
        if (visited[w] == 666) {
            arch_type[e] = "forward";
            //std::cout << "Node(" <<id[w] << ") --> " << visited[w] << std::endl;
            DepthFirstSearch(g, w, Counter);
        } else if (visited[w] < visited[v]) {
            arch_type[e] = "backward";
        }
    }
}

bool Algorithms::Tarjan::isReachable(SCC_Graph &g, Vertex_t &source, Vertex_t &Target) {
    typedef graph_traits<SCC_Graph>::vertices_size_type size_type;
    size_type n_vertices;
    n_vertices = num_vertices(g);
    v_p id = get(&TVertexProperties::index, g);
    std::vector<bool> Visited(n_vertices, false);
    std::deque<Vertex_t> Checks;
    Visited[id[source]] = true;
    Checks.push_back(source);
    while (!Checks.empty()) {
        Vertex_t v = Checks.front();
        Checks.pop_front();
        boost::graph_traits<SCC_Graph>::out_edge_iterator out_i, out_end;
        for (boost::tie(out_i, out_end) = out_edges(v, g); out_i != out_end; ++out_i) {
            Vertex_t w = target(*out_i, g);
            if (id[w] == id[Target]) {
                return true;
            } else if (!Visited[id[w]]) {
                Visited[id[w]] = true;
                Checks.push_back(w);
            }

        }

    }
    return false;

}

void Algorithms::Tarjan::ApplySCC(SCC_Graph &g) {
    v_p visited = get(&TVertexProperties::num, g);
    typedef boost::graph_traits<SCC_Graph>::vertex_descriptor Vertex_t;
    typedef boost::graph_traits<SCC_Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    std::vector<Vertex_t> Points;
    int Counter = 0;
    std::vector<StronglyConnected> strongs;
    std::cout << "Tarjan version of the SCC Algorithm is processing the graph" << std::endl;
    for (vp = vertices(g); vp.first != vp.second; vp.first++) {
        Vertex_t v = *vp.first;
        if (visited[v] == 666) {
            StrongConnect(g, v, strongs,Points, Counter);
        }
    }

}

void Algorithms::Tarjan::StrongConnect(SCC_Graph &g, Vertex_t &v, std::vector<StronglyConnected> &sccs,
                                       std::vector<Vertex_t> &Points, int &Counter) {
    v_p visited = get(&TVertexProperties::num, g);
    v_p lowPt = get(&TVertexProperties::lowPt, g);
    v_p lowVine = get(&TVertexProperties::lowVine, g);
    e_p arch_type = get(&EdgeProperties::name, g);
    v_p id = get(&TVertexProperties::index,g);
    Counter++;
    visited[v]= Counter;
    lowPt[v]= Counter;
    lowVine[v] = Counter;
   // std::cout<< visited[v] << " " << lowPt[v] << " " << lowVine[v] << std::endl;
    Points.push_back(v);
    typedef boost::graph_traits<SCC_Graph>::edge_descriptor Edge;
    boost::graph_traits<SCC_Graph>::out_edge_iterator out_i, out_end;
    for (boost::tie(out_i, out_end) = out_edges(v, g); out_i != out_end; ++out_i) {
        Edge e = *out_i;
        Vertex_t w = target(e, g);
        if (visited[w] == 666) {
            arch_type[e] = "tree"; // like in tarjan's algorithm
            StrongConnect(g, w,sccs,Points, Counter);
            lowPt[v] = lowPt[v]< lowPt[w]?lowPt[v]:lowPt[w];
            lowVine[v] = lowVine[v]< lowVine[w]?lowVine[v]:lowVine[w];
        } else if (!isReachable(g, w, v)) {
            if (visited[w] < visited[v]) {
                arch_type[e] = "vine";
                if (std::find(Points.begin(), Points.end(), w) != Points.end()) {
                    lowVine[v] = lowVine[v] < visited[w] ? lowVine[v] : visited[w];
                }
            }
        } else {// TODO Ancestor problem
            arch_type[e] = "frond";
            lowPt[v] = lowPt[v] < visited[w] ? lowPt[v] : visited[w];
        }
    }
    if (lowPt[v] == visited[v] && lowVine[v] == visited[v]) {
        StronglyConnected newComp;
        v_p id_t = get(&TVertexProperties::index,newComp);
        std::cout <<"Strongly connected Component is: ";
        while(!Points.empty() && visited[Points.back()] >= visited[v]){
            Vertex_t x = Points.back();
            Vertex_t temp = boost::add_vertex(newComp);
            id_t[temp] = id[x];
            Points.pop_back();
            std::cout << id[x]+1 << " ";
        }
        std::cout << std::endl;
        //Create a Vector of Vertex Vectors
        //pass it to the ApplySCC function
        //Create and Visualize Graphs there
    }

}

void Algorithms::Tarjan::Biconnect(SCC_Graph &g, Vertex_t &v, int &Counter) {

}

void Algorithms::Tarjan::ApplyBiconnectivity(SCC_Graph &g) {

}

//======================================================================================================================
//                                                      NUUTILA
//======================================================================================================================
void Algorithms::Nuutila::ApplySCC_Original(Nuutila_Graph &g) {

    v_p_n visited = get(&NVertexProperties::visited, g);
    v_p_n self = get(&NVertexProperties::index, g);
    v_p_n num = get(&NVertexProperties::num, g);
    typedef boost::graph_traits<Nuutila_Graph>::vertex_descriptor Vertex_n;
    typedef boost::graph_traits<Nuutila_Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    std::stack<Vertex_n> Points;
    int Counter = 0;
    std::vector<bool> strongs(num_vertices(g),0);

    for (vp = vertices(g); vp.first != vp.second; vp.first++) {
        Vertex_n v = *vp.first;
        if (num[v] == 666) {
            Visit(g, v, strongs,Points, Counter);
        }
    }
    std::cout << "The Nuutila Version of the SCC Algorithms is processing the graph" << std::endl;
    std::pair<vertex_iter, vertex_iter> vp_inner;
    for(vp = vertices(g); vp.first != vp.second; vp.first++){
        Vertex_n v = *vp.first;
        if((self[v]) == visited[v]){
            std::cout << "Strongly connected component is : "  << " ";
            for(vp_inner =vertices(g); vp_inner.first != vp_inner.second; vp_inner.first++){
                    Vertex_n w = *vp_inner.first;
                    if((self[v]) == visited[w]){
                        std::cout << self[w]  << " ";
                    }
            }
            std::cout << std::endl;
        }
    }
}

void Algorithms::Nuutila::Visit(Nuutila_Graph &g, Vertex_n &v, std::vector<bool> &sccs, std::stack<Vertex_n> &Points,int &Counter) {
    v_p_n root = get(&NVertexProperties::visited, g);
    v_p_nb inComponent = get(&NVertexProperties::isComponent, g);
    v_p_n self = get(&NVertexProperties::index,g);
    v_p_n num = get(&NVertexProperties::num, g);
    typedef boost::graph_traits<Nuutila_Graph>::vertex_descriptor Vertex_n;
    Counter++;
    num[v] =  Counter ;
    root[v] = self[v];
    inComponent[v] = false;
    Points.push(v);
    sccs[self[v]] = true;
    typedef boost::graph_traits<Nuutila_Graph>::edge_descriptor Edge;
    boost::graph_traits<Nuutila_Graph>::out_edge_iterator o_i,o_o;
    for (boost::tie(o_i,o_o) = out_edges(v,g); o_i != o_o; ++o_i){
        Edge e = *o_i;
        Vertex_n w = target(e,g);
        if(num[w] == 666){
            Visit(g,w,sccs,Points,Counter);
        }
        if (!inComponent[w]) {
            if (root[v] > root[w] || num[v] > num[w]) {
                root[v] = root[w];
            }
        }
    }
    if(root[v] == (self[v])){
        Vertex_n w ;
        do{
            w = Points.top();
            Points.pop();
            inComponent[w] = true;

        }while((root[v] != root[w]));

    }
}

void Algorithms::Nuutila::ApplySCC_v1(Nuutila_Graph &g){
    v_p_n visited = get(&NVertexProperties::visited, g);
    v_p_n self = get(&NVertexProperties::index, g);
    v_p_n num = get(&NVertexProperties::num, g);
    typedef boost::graph_traits<Nuutila_Graph>::vertex_descriptor Vertex_n;
    typedef boost::graph_traits<Nuutila_Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    std::stack<Vertex_n> Points;
    int Counter = 0;
    std::vector<StronglyConnected> strongs;
    for (vp = vertices(g); vp.first != vp.second; vp.first++) {
        Vertex_n v = *vp.first;
        if (num[v] == 666) {
            Visit_v1(g, v, strongs,Points, Counter);
        }
    }
    std::cout << "The Nuutila First Modified Version of the SCC Algorithms is processing the graph" << std::endl;
    std::pair<vertex_iter, vertex_iter> vp_inner;
    for(vp = vertices(g); vp.first != vp.second; vp.first++){
        Vertex_n v = *vp.first;
        if((self[v]) == visited[v]){
            std::cout << "Strongly connected component is : "  << " ";
            for(vp_inner =vertices(g); vp_inner.first != vp_inner.second; vp_inner.first++){
                Vertex_n w = *vp_inner.first;
                if((self[v]) == visited[w]){
                    std::cout << self[w]  << " ";
                }
            }
            std::cout << std::endl;
        }
    }
}

void Algorithms::Nuutila::ApplySCC_v2(Nuutila_Graph &g){
    v_p_n visited = get(&NVertexProperties::visited, g);
    v_p_n self = get(&NVertexProperties::index, g);
    v_p_n num = get(&NVertexProperties::num, g);
    typedef boost::graph_traits<Nuutila_Graph>::vertex_descriptor Vertex_n;
    typedef boost::graph_traits<Nuutila_Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    std::vector<Vertex_n> Points;
    Vertex_n v ;
    Points.push_back(v);
    int Counter = 0;
    std::vector<StronglyConnected> strongs;
    for (vp = vertices(g); vp.first != vp.second; vp.first++) {
        Vertex_n v = *vp.first;
        if (num[v] == 666) {
            Visit_v2(g, v, strongs,Points, Counter);
        }
    }
    std::cout << "The Nuutila Second Modified Version of the SCC Algorithms is processing the graph" << std::endl;
    std::pair<vertex_iter, vertex_iter> vp_inner;
    for (vp = vertices(g); vp.first != vp.second; vp.first++)
    {
        Vertex_n v = *vp.first;
        if ((self[v]) == visited[v])
        {
            std::cout << "Strongly connected component is : "
                      << " ";
            for (vp_inner = vertices(g); vp_inner.first != vp_inner.second; vp_inner.first++)
            {
                Vertex_n w = *vp_inner.first;
                if ((self[v]) == visited[w])
                {
                    std::cout << self[w] << " ";
                }
            }
            std::cout << std::endl;
        }
    }
}

 void Algorithms::Nuutila::Visit_v1(Nuutila_Graph &g, Vertex_n &v,std::vector<StronglyConnected> &sccs, std::stack<Vertex_n> &Points,int &Counter){
     v_p_n root = get(&NVertexProperties::visited, g);
     v_p_nb inComponent = get(&NVertexProperties::isComponent, g);
     v_p_n self = get(&NVertexProperties::index, g);
     v_p_n num = get(&NVertexProperties::num, g);
     typedef boost::graph_traits<Nuutila_Graph>::vertex_descriptor Vertex_n;
     Counter++;
     num[v] = Counter;
     root[v] = self[v];
     inComponent[v] = false;
     typedef boost::graph_traits<Nuutila_Graph>::edge_descriptor Edge;
      boost::graph_traits<Nuutila_Graph>::out_edge_iterator hoho,haha;
     for (boost::tie(hoho,haha) = out_edges(v,g); hoho != haha; ++hoho){
         Edge e = *hoho;
         Vertex_n w = target(e, g);
         if (num[w] == 666){
             Visit_v1(g, w, sccs, Points, Counter);
         }
         if (!inComponent[w]){
             if (num[v] > num[w] ) {
                 root[v] = root[w];
             }
         }
    }
     if(root[v] == self[v]){
         inComponent[v]= true;
        if(!Points.empty()){
             Vertex_n w = Points.top();
            while(num[w] > num[v]){
                Points.pop();
                inComponent[w] = true;
                if(Points.empty()){
                    break;
                }else {
                    w = Points.top();
                }
            }

         }
     }else{
       //  std::cout << self[v] << " is going in " << std::endl;
         Points.push(v);
     }
 }

 void Algorithms::Nuutila::Visit_v2(Nuutila_Graph &g, Vertex_n &v, std::vector<StronglyConnected> &sccs, std::vector<Vertex_n> &Points, int &Counter){
     v_p_n root = get(&NVertexProperties::visited, g);
     v_p_nb inComponent = get(&NVertexProperties::isComponent, g);
     v_p_n self = get(&NVertexProperties::index, g);
     v_p_n num = get(&NVertexProperties::num, g);
     typedef boost::graph_traits<Nuutila_Graph>::vertex_descriptor Vertex_n;
     Counter++;
     num[v] = Counter;
     root[v] = self[v];
     inComponent[v] = false;
     typedef boost::graph_traits<Nuutila_Graph>::edge_descriptor Edge;
     boost::graph_traits<Nuutila_Graph>::out_edge_iterator hoho,haha;
     for (boost::tie(hoho,haha) = out_edges(v,g); hoho != haha; ++hoho){
         Edge e = *hoho;
         Vertex_n w = target(e, g);
         if (num[w] == 666){
             Visit_v2(g, w, sccs, Points, Counter);
         }
         if (!inComponent[vertex(root[w],g)]){
             if (root[v] > root[w] ) {
                 root[v] = root[w];
             }
         }
     }
     if(root[v] == self[v]){
         if(Points.size() > 1){
             Vertex_n w = Points.back();
                 if(num[w] > num[v] ){
                     do{
                         Points.pop_back();
                         inComponent[w] = true;
                         w = Points.back();
                     }while(num[w] > num[v] );
                 }else {
                     inComponent[v] = true;
                 }
         }

     }
     else if (std::find(Points.begin(), Points.end(), vertex(root[v],g)) == Points.end()){
           std::cout << root[v] << " is going in " << std::endl;
         Points.push_back(vertex(root[v],g));
     }
     // if root[v] == v part will be implemented
}
