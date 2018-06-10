 #include "./../header/nuutila.h"

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

 void Nuutila::print_graph(){
    GraphComponent::print_graph_file(n);
 }
 void Nuutila::ApplySCC_Original() {
    
     v_p id = get(&VertexProperty::index,n);
     typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
     typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
     std::pair<vertex_iter, vertex_iter> vp;
     std::vector<Vertex_t> Points;
     int Counter = 0;
     int sizeOfGraph = num_vertices(n);
     std::vector<bool>isComponent(sizeOfGraph,false);
     std::vector<int>visited(sizeOfGraph,999999999);
     std::vector<int>root(sizeOfGraph,666);
     for (vp = vertices(n); vp.first != vp.second; vp.first++) {
         Vertex_t v = *vp.first;
         if (visited[id[v]]== 999999999) {
             Visit(v,Points,root,visited,isComponent,Counter);
         }
     }
     std::cout << "\nThe Nuutila Version of the SCC Algorithms is processing the graph" << std::endl;
     std::pair<vertex_iter, vertex_iter> vp_inner;
     for(vp = vertices(n); vp.first != vp.second; vp.first++){
         Vertex_t v = *vp.first;
         if(id[v] == root[id[v]]){
             std::cout << "Strongly connected component is : "  << " ";
             for(vp_inner =vertices(n); vp_inner.first != vp_inner.second; vp_inner.first++){
                     Vertex_t w = *vp_inner.first;
                     if(id[v] == root[id[w]]){
                         std::cout << id[w] +1 << " ";
                     }
             }
             std::cout << std::endl;
         }
     }
 }

 void Nuutila::Visit( Vertex_t &v, std::vector<Vertex_t> &Points,std::vector<int> &root, std::vector<int> &visited, std::vector<bool> &isComponent ,int &Counter) {
     v_p id = get(&VertexProperty::index,n);
     typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
     visited[id[v]] =  Counter ;
     Counter++;
     root[id[v]] = id[v];
   //  isComponent[id[v]] = false;
     Points.push_back(v);
//     std::cout << id[v]+1 << " is going in " << std::endl;
     typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
     boost::graph_traits<theGraph>::out_edge_iterator o_i,o_o;
     for (boost::tie(o_i,o_o) = out_edges(v,n); o_i != o_o; ++o_i){
         Edge e = *o_i;
         Vertex_t w = target(e,n);
         if(visited[id[w]] == 999999999){
             Visit(w,Points,root,visited,isComponent,Counter);
         }
         if (!isComponent[id[w]]) {
             if ( visited[root[id[v]]] > visited[root[id[w]]] ) {
 //                std::cout << root[id[v]] << " changes with " << root[id[w]] << std::endl;
                  root[id[v]] = root[id[w]];
             }
         }
     }
     if(root[id[v]] == id[v]){
         Vertex_t w ;
         do{
             w = Points.back();
            Points.pop_back();
//            std::cout << id[w]+1 << " is going out with root:" << root[id[w]]+1 << std::endl;
            isComponent[id[w]] = true;
             
         }while(id[v] != root[id[w]]);

     }
 }

 void Nuutila::ApplySCC_v1(){
     
     v_p id= get(&VertexProperty::index, n);
    typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
     typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
     std::pair<vertex_iter, vertex_iter> vp;
     std::vector<Vertex_t> Points;
     int Counter = 0;
     int sizeOfGraph = num_vertices(n);
     std::vector<bool> isComponent(sizeOfGraph, false);
     std::vector<int> visited(sizeOfGraph, 666);
     std::vector<int> root(sizeOfGraph, -1);
    for (vp = vertices(n); vp.first != vp.second; vp.first++) {
        Vertex_t v = *vp.first;
        if (visited[id[v]] == 666) {
            Visit_v1( v,Points,root,visited,isComponent, Counter);
        }
    }
    std::cout << "\nThe Nuutila First Modified Version of the SCC Algorithms is processing the graph" << std::endl;
    std::pair<vertex_iter, vertex_iter> vp_inner;
    for(vp = vertices(n); vp.first != vp.second; vp.first++){
        Vertex_t v = *vp.first;
        if((id[v]) == root[id[v]]){
            std::cout << "Strongly connected component is : "  << " ";
            for(vp_inner =vertices(n); vp_inner.first != vp_inner.second; vp_inner.first++){
                Vertex_t w = *vp_inner.first;
                if((id[v]) == root[id[w]]){
                    std::cout << id[w]+1  << " ";
                }
            }
            std::cout << std::endl;
        }
    }
}

      void Nuutila::ApplySCC_v2(){

          v_p id = get(&VertexProperty::index, n);

          typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
          typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
         std::pair<vertex_iter, vertex_iter> vp;
         std::vector<Vertex_t> Points;
         Vertex_t v ;
         Points.push_back(v);
         int Counter = 0;
         int sizeOfGraph = num_vertices(n);
         std::vector<bool>isComponent(sizeOfGraph,false);
        std::vector<int>visited(sizeOfGraph,666);
        std::vector<int>root(sizeOfGraph,-1);
         
         for (vp = vertices(n); vp.first != vp.second; vp.first++) {
             Vertex_t v = *vp.first;
             if (visited[id[v]] == 666) {
                 Visit_v2( v,Points,root,visited,isComponent, Counter);
             }
         }
          std::cout << "\nThe Nuutila Second Modified Version of the SCC Algorithms is processing the graph" << std::endl;
          std::pair<vertex_iter, vertex_iter> vp_inner;
          for (vp = vertices(n); vp.first != vp.second; vp.first++){
              Vertex_t v = *vp.first;
              if ((id[v]) == root[id[v]]){
                  std::cout << "Strongly connected component is : "
                            << " ";
                  for (vp_inner = vertices(n); vp_inner.first != vp_inner.second; vp_inner.first++){
                      Vertex_t w = *vp_inner.first;
                      if ((id[v]) == root[id[w]]){
                          std::cout << id[w]+1 << " ";
                      }
                  }
                  std::cout << std::endl;
              }
          }
      }

        void Nuutila::Visit_v1( Vertex_t &v, std::vector<Vertex_t> &Points,std::vector<int> &root, std::vector<int> &visited, std::vector<bool> &isComponent ,int &Counter){
      
            v_p id = get(&VertexProperty::index, n);
            typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
            visited[id[v]] = Counter;
            Counter++;
            root[id[v]] = id[v];
            isComponent[id[v]] = false;
            typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
             boost::graph_traits<theGraph>::out_edge_iterator hoho,haha;
            for (boost::tie(hoho,haha) = out_edges(v,n); hoho != haha; ++hoho){
                Edge e = *hoho;
                Vertex_t w = target(e, n);
                if (visited[id[w]] == 666){
                    Visit_v1(w,Points,root,visited,isComponent, Counter);
                }
                if (!isComponent[id[w]]){
                    if (visited[root[id[v]]] > visited[root[id[w]]] ) {
                        root[id[v]] = root[id[w]];
                    }
                }
           }
           if(root[id[v]] == id[v]){
               isComponent[id[v]]= true;
            //   std::cout << Points.size() << std::endl;
               if(!Points.empty()){
                   Vertex_t w = Points.back();
                   while(visited[id[w]] > visited[id[v]]){
  //                    std::cout << id[w] << " hiammina" << std::endl;
                      Points.pop_back();
                      isComponent[id[w]] = true;
                      if (Points.empty()){
                          break;
                      }
                      else{
                          w = Points.back();
                      }
                  }
              }
           }else{
             //  std::cout << id[v] << " is going in " << std::endl;
               Points.push_back(v);
           }
        }

        void Nuutila::Visit_v2(Vertex_t &v, std::vector<Vertex_t> &Points, std::vector<int> &root, std::vector<int> &visited, std::vector<bool> &isComponent, int &Counter)
        {
                  v_p id = get(&VertexProperty::index, n);
                 typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
                 visited[id[v]] = Counter;
                 Counter++;
                 root[id[v]] = id[v];
                 isComponent[id[v]] = false;
                 typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
                 boost::graph_traits<theGraph>::out_edge_iterator hoho,haha;
                 for (boost::tie(hoho,haha) = out_edges(v,n); hoho != haha; ++hoho){
                     Edge e = *hoho;
                     Vertex_t w = target(e, n);
                     if (visited[id[w]] == 666){
                         Visit_v2( w, Points,root,visited,isComponent, Counter);
                     }
                     if (!isComponent[root[id[w]]]){
                         if (visited[root[id[v]]] > visited[root[id[w]]] ) {
                             root[id[v]] = root[id[w]];
                         }
                     }
                 }
                 if(root[id[v]] == id[v]){
                     if(Points.size() > 1){
                         Vertex_t w = Points.back();
                             if(visited[id[w]] > visited[id[v]] ){
                                 do{
                                     Points.pop_back();
                                     isComponent[id[w]] = true;
                                     w = Points.back();
                                 }while(visited[id[w]] > id[v] );
                             }else {
                                 isComponent[id[v]] = true;
                             }
                     }

                 }
                 else if (std::find(Points.begin(), Points.end(), vertex(root[id[v]],n)) == Points.end()){
                  //     std::cout << root[id[v]] << " is going in " << std::endl;
                     Points.push_back(vertex(root[id[v]],n));
                 }
             }
