// #include "./../header/nuutila.h"

// //STL
// #include <iostream>
// #include <vector>
// #include <string>
// #include <fstream>
// #include <sstream>
// #include <iterator>
// //Boost
// #include <boost/config.hpp>
// #include <boost/graph/adjacency_list.hpp>
// #include <boost/graph/graphviz.hpp>
// #include <boost/graph/graph_utility.hpp>
// #include <boost/graph/adjacency_list_io.hpp>
// #include <boost/graph/property_iter_range.hpp>
// #include <boost/graph/copy.hpp>
// #include <boost/property_map/property_map.hpp>

// void Nuutila::ApplySCC_Original(theGraph &g) {

//     v_p_n visited = get(&NVertexProperties::visited, g);
//     v_p_n self = get(&NVertexProperties::index, g);
//     v_p_n num = get(&NVertexProperties::num, g);
//     typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
//     typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
//     std::pair<vertex_iter, vertex_iter> vp;
//     std::stack<Vertex_t> Points;
//     int Counter = 0;
//     std::vector<bool> strongs(num_vertices(g),0);

//     for (vp = vertices(g); vp.first != vp.second; vp.first++) {
//         Vertex_t v = *vp.first;
//         if (num[v] == 666) {
//             Visit(g, v, strongs,Points, Counter);
//         }
//     }
//     std::cout << "The Nuutila Version of the SCC Algorithms is processing the graph" << std::endl;
//     std::pair<vertex_iter, vertex_iter> vp_inner;
//     for(vp = vertices(g); vp.first != vp.second; vp.first++){
//         Vertex_t v = *vp.first;
//         if((self[v]) == visited[v]){
//             std::cout << "Strongly connected component is : "  << " ";
//             for(vp_inner =vertices(g); vp_inner.first != vp_inner.second; vp_inner.first++){
//                     Vertex_t w = *vp_inner.first;
//                     if((self[v]) == visited[w]){
//                         std::cout << self[w]  << " ";
//                     }
//             }
//             std::cout << std::endl;
//         }
//     }
// }

// void Nuutila::Visit(theGraph &g, Vertex_t &v, std::vector<bool> &sccs, std::stack<Vertex_t> &Points,int &Counter) {
//     v_p_n root = get(&NVertexProperties::visited, g);
//     v_p_nb inComponent = get(&NVertexProperties::isComponent, g);
//     v_p_n self = get(&NVertexProperties::index,g);
//     v_p_n num = get(&NVertexProperties::num, g);
//     typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
//     Counter++;
//     num[v] =  Counter ;
//     root[v] = self[v];
//     inComponent[v] = false;
//     Points.push(v);
//     sccs[self[v]] = true;
//     typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
//     boost::graph_traits<theGraph>::out_edge_iterator o_i,o_o;
//     for (boost::tie(o_i,o_o) = out_edges(v,g); o_i != o_o; ++o_i){
//         Edge e = *o_i;
//         Vertex_t w = target(e,g);
//         if(num[w] == 666){
//             Visit(g,w,sccs,Points,Counter);
//         }
//         if (!inComponent[w]) {
//             if (root[v] > root[w] || num[v] > num[w]) {
//                 root[v] = root[w];
//             }
//         }
//     }
//     if(root[v] == (self[v])){
//         Vertex_t w ;
//         do{
//             w = Points.top();
//             Points.pop();
//             inComponent[w] = true;

//         }while((root[v] != root[w]));

//     }
// }

// void Nuutila::ApplySCC_v1(theGraph &g){
//     v_p_n visited = get(&NVertexProperties::visited, g);
//     v_p_n self = get(&NVertexProperties::index, g);
//     v_p_n num = get(&NVertexProperties::num, g);
//     typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
//     typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
//     std::pair<vertex_iter, vertex_iter> vp;
//     std::stack<Vertex_t> Points;
//     int Counter = 0;
//     std::vector<StronglyConnected> strongs;
//     for (vp = vertices(g); vp.first != vp.second; vp.first++) {
//         Vertex_t v = *vp.first;
//         if (num[v] == 666) {
//             Visit_v1(g, v, strongs,Points, Counter);
//         }
//     }
//     std::cout << "The Nuutila First Modified Version of the SCC Algorithms is processing the graph" << std::endl;
//     std::pair<vertex_iter, vertex_iter> vp_inner;
//     for(vp = vertices(g); vp.first != vp.second; vp.first++){
//         Vertex_t v = *vp.first;
//         if((self[v]) == visited[v]){
//             std::cout << "Strongly connected component is : "  << " ";
//             for(vp_inner =vertices(g); vp_inner.first != vp_inner.second; vp_inner.first++){
//                 Vertex_t w = *vp_inner.first;
//                 if((self[v]) == visited[w]){
//                     std::cout << self[w]  << " ";
//                 }
//             }
//             std::cout << std::endl;
//         }
//     }
// }

// void Nuutila::ApplySCC_v2(theGraph &g){
//     v_p_n visited = get(&NVertexProperties::visited, g);
//     v_p_n self = get(&NVertexProperties::index, g);
//     v_p_n num = get(&NVertexProperties::num, g);
//     typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
//     typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
//     std::pair<vertex_iter, vertex_iter> vp;
//     std::vector<Vertex_t> Points;
//     Vertex_t v ;
//     Points.push_back(v);
//     int Counter = 0;
//     std::vector<StronglyConnected> strongs;
//     for (vp = vertices(g); vp.first != vp.second; vp.first++) {
//         Vertex_t v = *vp.first;
//         if (num[v] == 666) {
//             Visit_v2(g, v, strongs,Points, Counter);
//         }
//     }
//     std::cout << "The Nuutila Second Modified Version of the SCC Algorithms is processing the graph" << std::endl;
//     std::pair<vertex_iter, vertex_iter> vp_inner;
//     for (vp = vertices(g); vp.first != vp.second; vp.first++)
//     {
//         Vertex_t v = *vp.first;
//         if ((self[v]) == visited[v])
//         {
//             std::cout << "Strongly connected component is : "
//                       << " ";
//             for (vp_inner = vertices(g); vp_inner.first != vp_inner.second; vp_inner.first++)
//             {
//                 Vertex_t w = *vp_inner.first;
//                 if ((self[v]) == visited[w])
//                 {
//                     std::cout << self[w] << " ";
//                 }
//             }
//             std::cout << std::endl;
//         }
//     }
// }

//  void Nuutila::Visit_v1(theGraph &g, Vertex_t &v,std::vector<StronglyConnected> &sccs, std::stack<Vertex_t> &Points,int &Counter){
//      v_p_n root = get(&NVertexProperties::visited, g);
//      v_p_nb inComponent = get(&NVertexProperties::isComponent, g);
//      v_p_n self = get(&NVertexProperties::index, g);
//      v_p_n num = get(&NVertexProperties::num, g);
//      typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
//      Counter++;
//      num[v] = Counter;
//      root[v] = self[v];
//      inComponent[v] = false;
//      typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
//       boost::graph_traits<theGraph>::out_edge_iterator hoho,haha;
//      for (boost::tie(hoho,haha) = out_edges(v,g); hoho != haha; ++hoho){
//          Edge e = *hoho;
//          Vertex_t w = target(e, g);
//          if (num[w] == 666){
//              Visit_v1(g, w, sccs, Points, Counter);
//          }
//          if (!inComponent[w]){
//              if (num[v] > num[w] ) {
//                  root[v] = root[w];
//              }
//          }
//     }
//      if(root[v] == self[v]){
//          inComponent[v]= true;
//         if(!Points.empty()){
//              Vertex_t w = Points.top();
//             while(num[w] > num[v]){
//                 Points.pop();
//                 inComponent[w] = true;
//                 if(Points.empty()){
//                     break;
//                 }else {
//                     w = Points.top();
//                 }
//             }

//          }
//      }else{
//        //  std::cout << self[v] << " is going in " << std::endl;
//          Points.push(v);
//      }
//  }

//  void Nuutila::Visit_v2(theGraph &g, Vertex_t &v, std::vector<StronglyConnected> &sccs, std::vector<Vertex_t> &Points, int &Counter){
//      v_p_n root = get(&NVertexProperties::visited, g);
//      v_p_nb inComponent = get(&NVertexProperties::isComponent, g);
//      v_p_n self = get(&NVertexProperties::index, g);
//      v_p_n num = get(&NVertexProperties::num, g);
//      typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
//      Counter++;
//      num[v] = Counter;
//      root[v] = self[v];
//      inComponent[v] = false;
//      typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
//      boost::graph_traits<theGraph>::out_edge_iterator hoho,haha;
//      for (boost::tie(hoho,haha) = out_edges(v,g); hoho != haha; ++hoho){
//          Edge e = *hoho;
//          Vertex_t w = target(e, g);
//          if (num[w] == 666){
//              Visit_v2(g, w, sccs, Points, Counter);
//          }
//          if (!inComponent[vertex(root[w],g)]){
//              if (root[v] > root[w] ) {
//                  root[v] = root[w];
//              }
//          }
//      }
//      if(root[v] == self[v]){
//          if(Points.size() > 1){
//              Vertex_t w = Points.back();
//                  if(num[w] > num[v] ){
//                      do{
//                          Points.pop_back();
//                          inComponent[w] = true;
//                          w = Points.back();
//                      }while(num[w] > num[v] );
//                  }else {
//                      inComponent[v] = true;
//                  }
//          }

//      }
//      else if (std::find(Points.begin(), Points.end(), vertex(root[v],g)) == Points.end()){
//            std::cout << root[v] << " is going in " << std::endl;
//          Points.push_back(vertex(root[v],g));
//      }
//      // if root[v] == v part will be implemented
// }
