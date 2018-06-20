import networkx as nx
import pathlib
import os
from contextlib import contextmanager
import numpy as np


@contextmanager
def working_directory(directory):
    owd = os.getcwd()
    try:
        os.chdir(directory)
        yield directory
    finally:
        os.chdir(owd)


def generate_folders():
    
    node_capacity_list = ["5_50","50_100","100_500", "500_1000"]
    number_edge_percentage = 5
    ncp_v2 = np.array([[x] * number_edge_percentage for x in node_capacity_list])
    ncp_v2 = ncp_v2.flatten()
    print(ncp_v2)
    edge_percentage_list = ["0_10","10_25","25_50","50_75","75_100"]
    ecp_v2 = np.array([edge_percentage_list * len(node_capacity_list)]).flatten()
    print(ecp_v2)
    current_directory = os.getcwd() + "/input"
    pathlib.Path(current_directory).mkdir( exist_ok=True)
    print(current_directory)
    final_directory_list = []
    #generate the first level of folders 
    print("Seperate directories for the node classes will be created")
    print("Sub directories with different percentage of edge creations will be created")
    for ddir in node_capacity_list:
        final_directory = os.path.join(current_directory, ddir)
        #print(final_directory)
        pathlib.Path(final_directory).mkdir( exist_ok=True)
        #generate the second level of folders
        final_directory_list.extend([final_directory] * len(edge_percentage_list))
        # for cdir in edge_percentage_list:
        #     percentage_folder = os.path.join(final_directory, cdir)
        #     final_directory_list.append(percentage_folder)
        #     pathlib.Path(percentage_folder).mkdir(exist_ok=True)
    #print(final_directory_list)
    results = zip(final_directory_list,ncp_v2,ecp_v2)
    return results

def generate_graphs(data_pack,graph_num):
    
    for ddir,n_r,e_p in data_pack:
        counter = 0
        with working_directory(ddir):
            #get the node number
            nodes = n_r.split("_")
            node_list = np.random.randint(int(nodes[0]),int(nodes[1]),graph_num)
            #get the edge percentage
            edges = e_p.split("_")
            edges = [int(x)/100.0 for x in edges]
           # print(edges)
            edge_list = [edges[0] + (edges[1]-edges[0]) * np.random.rand() for x in range(graph_num)] 
           # print(edge_list)
            #generate the graph
            for x in range(len(node_list)):
                graph = nx.gnp_random_graph(node_list[x],edge_list[x],directed=True,seed=666)
                #graph = nx.empty_graph(node)
                name = n_r +"|" + e_p + "|" + str(counter) + ".graph"
                counter+=1
                write_graph(graph,node_list[x],name)
                

def write_graph(graph,node,name):
    f = open(name, 'w')
    f.write(str(node) + "\n")
    for s,t in graph.edges:
        f.write(str(s) + " " + str(t) + "\n")
    f.close()
    
def main():
    dir_results = generate_folders()
    generate_graphs(dir_results,5)



if __name__ == "__main__":
    main()
