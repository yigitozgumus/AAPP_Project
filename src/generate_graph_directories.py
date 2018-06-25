#!/usr/bin/python
import networkx as nx
import pathlib
import os
from contextlib import contextmanager
import numpy as np
import argparse
from time import sleep


@contextmanager
def working_directory(directory):
    owd = os.getcwd()
    try:
        os.chdir(directory)
        yield directory
    finally:
        os.chdir(owd)

# Print iterations progress


def printProgressBar(iteration, total, prefix='', suffix='', decimals=1, length=100, fill='█'):
    """
    Call in a loop to create terminal progress bar
    @params:
        iteration   - Required  : current iteration (Int)
        total       - Required  : total iterations (Int)
        prefix      - Optional  : prefix string (Str)
        suffix      - Optional  : suffix string (Str)
        decimals    - Optional  : positive number of decimals in percent complete (Int)
        length      - Optional  : character length of bar (Int)
        fill        - Optional  : bar fill character (Str)
    """
    percent = ("{0:." + str(decimals) + "f}").format(100 *
                                                     (iteration / float(total)))
    filledLength = int(length * iteration // total)
    bar = fill * filledLength + '-' * (length - filledLength)
    print('\r%s |%s| %s%% %s' % (prefix, bar, percent, suffix), end='\r')
    # Print New Line on Complete
    if (iteration == total):
        print()

def generate_folders(foldername,index):
    
    n_c_list = ["5_50","50_100","100_500", "500_1000"]
    if(index != -1):
        n_c_list = n_c_list[index:index+1]
    #n_c_list = ["5_50"]
    number_edge_percentage = 5
    ncp_v2 = np.array([[x] * number_edge_percentage for x in n_c_list])
    ncp_v2 = ncp_v2.flatten()
    print("\nGraph Creation has begun\n")
    print("The Graph Node Ranges are:")
    for i in range(len(n_c_list)):
        nodes = n_c_list[i].split("_")
        print(i+1, "-) {} - {}".format(int(nodes[0]),int(nodes[1])))
    e_p_list = ["0_10","10_25","25_50","50_75","75_100"]
    ecp_v2 = np.array([e_p_list * len(n_c_list)]).flatten()
    print("\nEdge Creation Percentages are:")
    for i in range(len(e_p_list)):
        minmax = e_p_list[i].split("_")
        print(i+1, "-) {} - {}".format(int(minmax[0]),int(minmax[1])))
    current_directory = os.getcwd() + "/" + foldername
    pathlib.Path(current_directory).mkdir( exist_ok=True)
    print("\nThe graphs will be written into :\n {}".format(current_directory))
    final_directory_list = []
    #generate the first level of folders 
   
    for ddir in n_c_list:
        final_directory = os.path.join(current_directory, ddir)
        pathlib.Path(final_directory).mkdir( exist_ok=True)
        #generate the second level of folders
        final_directory_list.extend([final_directory] * len(e_p_list))
    results = zip(final_directory_list,ncp_v2,ecp_v2)
    print("\nSeperate directories for the node classes is created\n")
    total_graph = len(n_c_list) * len(e_p_list)
    return (results,total_graph)

def generate_graphs(data_pack,graph_num):
    total_graph = data_pack[1] * graph_num
    printProgressBar(0, total_graph, prefix='Progress:', suffix='Complete', length=100)
    counter = 0
    for ddir,n_r,e_p in data_pack[0]:
        
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
                sleep(0.1)
                printProgressBar(counter, total_graph, prefix='Progress:', suffix='Complete', length=100)
    print("\nThe Graps are created with success\n")
                

def write_graph(graph,node,name):
    f = open(name, 'w')
    f.write(str(node) + "\n")
    for s,t in graph.edges:
        f.write(str(s) + " " + str(t) + "\n")
    f.close()
    
def main():
    parser = argparse.ArgumentParser(description='Generate directed graphs \
                                        with different edge creation probabilities.')
    parser.add_argument("graph_count", metavar ='G', help="Number of graphs for each edge creation interval")
    parser.add_argument("folder", metavar='F', help="The Target Location of the Graph files")
    parser.add_argument("--single", metavar="S", help="Single node class Graph creation for fast testing between \n 5_50, 50_100 , 100_500 ,  500_1000")
    args = parser.parse_args()
    graph_count = args.graph_count
    relative_folder = args.folder
    index = -1;
    if(args.single):
        index = int(args.single)
    
    dir_results = generate_folders(relative_folder,index)
    generate_graphs(dir_results,int(graph_count))



if __name__ == "__main__":
    main()
