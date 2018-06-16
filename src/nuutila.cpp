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
 #include <boost/graph/strong_components.hpp>
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

 void Nuutila::print_sccs(std::vector<int> &root){
     v_p id = get(&VertexProperty::index,n);
     typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
     std::pair<vertex_iter, vertex_iter> vp1;
     std::pair<vertex_iter, vertex_iter> vp_inner;
     for(vp1 = vertices(n); vp1.first != vp1.second; ++vp1.first){
         Vertex_t v = *vp1.first;
         if(id[v] == root[id[v]]){
         	 int count_component = 0;
       //      std::cout << id[v] <<" root " << std::endl; 
        //     std::cout << "Strongly connected component is : "  << " ";
         	 
             for(vp_inner =vertices(n); vp_inner.first != vp_inner.second; ++vp_inner.first){
                     Vertex_t w = *vp_inner.first;
                     if (root[id[w]] == id[v]){
                     	count_component++;
                   //      std::cout << id[w] +1 << " ";
                     }
             }
             std::cout << "Number of elements in the component is: " << count_component << std::endl;
          //   std::cout << std::endl;
         }
     }
     // for(vp_inner =vertices(n); vp_inner.first != vp_inner.second; ++vp_inner.first){
     //                 Vertex_t w = *vp_inner.first;
     //                     std::cout << root[id[w]] +1 << " ";
     // }
             
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
     std::vector<int>visited(sizeOfGraph,999999);
     std::vector<int>root(sizeOfGraph,666);
     for (vp = vertices(n); vp.first != vp.second; vp.first++) {
         Vertex_t v = *vp.first;
         if (visited[id[v]]== 999999) {
             Visit(v,Points,root,visited,isComponent,Counter);
         }
     }
     std::cout << "\nThe Nuutila Version of the SCC Algorithms is processing the graph" << std::endl;
     print_sccs(root);
 }

 void Nuutila::Visit( Vertex_t &v, std::vector<Vertex_t> &Points,std::vector<int> &root, std::vector<int> &visited, std::vector<bool> &isComponent ,int &Counter) {
     v_p id = get(&VertexProperty::index,n);
     typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
     visited[id[v]] =  Counter ;
     Counter++;
     root[id[v]] = id[v];
     isComponent[id[v]] = false;
     Points.push_back(v);
     typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
     boost::graph_traits<theGraph>::out_edge_iterator o_i,o_o;
     for (boost::tie(o_i,o_o) = out_edges(v,n); o_i != o_o; ++o_i){
         Edge e = *o_i;
         Vertex_t w = target(e,n);
         if(visited[id[w]] == 999999){
             Visit(w,Points,root,visited,isComponent,Counter);
         }
         if (!isComponent[id[w]]) {
             if ( visited[root[id[v]]] > visited[root[id[w]]] ) {
                  root[id[v]] = root[id[w]];
             }
         }
     }
     if(root[id[v]] == id[v]){
         Vertex_t w ;
         do{
         	w = Points.back();
            Points.pop_back();
            isComponent[id[w]] = true;
            
         }while(v != w);
         // Points.pop_back();
         // isComponent[id[w]] = true;
         
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
     std::vector<int> visited(sizeOfGraph, 999999);
     std::vector<int> root(sizeOfGraph, -1);
    for (vp = vertices(n); vp.first != vp.second; vp.first++) {
        Vertex_t v = *vp.first;
        if (visited[id[v]] == 999999) {
            Visit_v1( v,Points,root,visited,isComponent, Counter);
        }
    }
    std::cout << "\nThe Nuutila First Modified Version of the SCC Algorithms is processing the graph" << std::endl;
    print_sccs(root);
}

      void Nuutila::ApplySCC_v2(){

        v_p id = get(&VertexProperty::index, n);

        typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
        typedef boost::graph_traits<theGraph>::vertex_iterator vertex_iter;
        std::pair<vertex_iter, vertex_iter> vp;
        std::vector<int> Points;
        Points.push_back(0);
        int Counter = 0;
        int sizeOfGraph = num_vertices(n);
        std::vector<bool>isComponent(sizeOfGraph+1,false);
        std::vector<int>visited(sizeOfGraph+1,999999);
        std::vector<int>root(sizeOfGraph,-1);
        visited[0] = -999;
         for (vp = vertices(n); vp.first != vp.second; vp.first++) {
             Vertex_t v = *vp.first;
             if (visited[id[v]+1] == 999999) {
                 Visit_v2( v,Points,root,visited,isComponent, Counter);
             }
         }
          std::cout << "\nThe Nuutila Second Modified Version of the SCC Algorithms is processing the graph" << std::endl;
          print_sccs(root);
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
                if (visited[id[w]] == 999999){
                    Visit_v1(w,Points,root,visited,isComponent, Counter);
                }
                if (!isComponent[id[w]]){
                    if (visited[root[id[v]]] > visited[root[id[w]]] ) {
                        root[id[v]] = root[id[w]];
                    }else{
		             	root[id[w]] = root[id[v]];
		             }
                }
           }
           if(root[id[v]] == id[v]){
               isComponent[id[v]]= true;
               if(!Points.empty()){
                   Vertex_t w = Points.back();
                   while(visited[id[w]] > visited[id[v]]){
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
               Points.push_back(v);
           }
        }

        void Nuutila::Visit_v2(Vertex_t &v, std::vector<int> &Points, std::vector<int> &root, std::vector<int> &visited, std::vector<bool> &isComponent, int &Counter)
        {
                  v_p id = get(&VertexProperty::index, n);
                 typedef boost::graph_traits<theGraph>::vertex_descriptor Vertex_t;
                 visited[id[v]+1] = Counter;
                 Counter++;
                 root[id[v]] = id[v];
                 isComponent[id[v]+1] = false;
                 typedef boost::graph_traits<theGraph>::edge_descriptor Edge;
                 boost::graph_traits<theGraph>::out_edge_iterator hoho,haha;
                 for (boost::tie(hoho,haha) = out_edges(v,n); hoho != haha; ++hoho){
                     Edge e = *hoho;
                     Vertex_t w = target(e, n);
                     if (visited[id[w]+1] == 999999){
                         Visit_v2( w, Points,root,visited,isComponent, Counter);
                     }
                     if (!isComponent[root[id[w]]+1]){
                         if (visited[root[id[v]]+1] > visited[root[id[w]]+1] ) {
                             root[id[v]] = root[id[w]];
                         }
                     }
                 }
                 if(root[id[v]] == id[v]){
                    int w = Points.back();
                    if(visited[w] >= visited[id[v]+1] ){
                        do{
                            Points.pop_back();
                            isComponent[w] = true;
                            w = Points.back();
                        }while(visited[w] >= visited[id[v]+1] );
                    }else {
                        isComponent[id[v]+1] = true;
                    }
                 }
                 else if (std::find(Points.begin(), Points.end(), root[id[v]]) == Points.end()){
                  //     std::cout << root[id[v]] << " is going in " << std::endl;
                     Points.push_back(root[id[v]]);
                 }
             }
