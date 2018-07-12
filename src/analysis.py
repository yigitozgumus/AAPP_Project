import pandas as pd
import numpy as np
import sklearn as sk
import scipy as sp
import bokeh as bkh
import matplotlib.pyplot as plt
import argparse
from os import listdir
from os.path import isfile, join

# visualization library
import seaborn as sns
sns.set( color_codes=True)
sns.set_context(rc={"font.family":'sans',"font.size":24,"axes.titlesize":24,"axes.labelsize":24}) 

def main():
    parser = argparse.ArgumentParser(description='Visualize the experiment results')
    parser.add_argument("csv", metavar='C', help="The Target Location of the experiment csv file")
    parser.add_argument("--index",metavar='I',help="Optional file selection variable")
    
    args = parser.parse_args()
    file_name = args.csv
    
   # df = get_data(4)
    df = get_data_from_file(file_name)
    new_dfs = seperate_dataframes(df)
    plot_comparisons(new_dfs)

def print_available_cvs():
    data = "data"
    experiment_csvs = [("/data/" + f) for f in listdir(data) if isfile(join(data, f))]
    print("The current experiment list is:")
    for f in range(1,len(experiment_csvs)):
        print(str(f) + "-) " + experiment_csvs[f] )
        
def get_data_from_file(filename):
    names = ["id","Vertex","Edge",
         'T-Tarjan','S-Tarjan',
         'T-Nuutila Original','S-Nuutila Original', 
         'T-Nuutila Version1','S-Nuutila Version1',
         'T-Nuutila Version2','S-Nuutila Version2', 
         'T-Pearson Version1','S-Pearson Version1',
         'T-Pearson Version2','S-Pearson Version2',
         'T-Pearson Version3','S-Pearson Version3']
    file = "/data/" + filename
    df = pd.read_csv(file[1:], sep=',', names=names)
    return df

def get_data(index):
    data = "data"
    experiment_csvs = [("/data/" + f) for f in listdir(data) if isfile(join(data, f))]
    names = ["id","Vertex","Edge",
         'T-Tarjan','S-Tarjan',
         'T-Nuutila Original','S-Nuutila Original', 
         'T-Nuutila Version1','S-Nuutila Version1',
         'T-Nuutila Version2','S-Nuutila Version2', 
         'T-Pearson Version1','S-Pearson Version1',
         'T-Pearson Version2','S-Pearson Version2',
         'T-Pearson Version3','S-Pearson Version3']
    print("\n The file that is used to create the dataframe is : " + experiment_csvs[index][1:])
    df = pd.read_csv(experiment_csvs[index][1:],sep=',',names=names)
    return df

def seperate_dataframes(df):
    df_storage_all = df[['Vertex','S-Tarjan',
                 'S-Nuutila Original', 
                 'S-Nuutila Version1',
                 'S-Nuutila Version2', 
                 'S-Pearson Version1',
                 'S-Pearson Version2',
                'S-Pearson Version3']]
    df_storage_all = df_storage_all.sort_values(by=['Vertex']);

    df_s_t = df_storage_all[['Vertex','S-Tarjan']]
    df_s_n = df_storage_all[['Vertex',
                                     'S-Nuutila Original', 
                                     'S-Nuutila Version1',
                                     'S-Nuutila Version2', ]]
    df_s_p = df_storage_all[['Vertex',
                                   'S-Pearson Version1',
                                    'S-Pearson Version2',
                                    'S-Pearson Version3']]
    bundle = [df_s_t,df_s_n,df_s_p,df_storage_all]
    return bundle

def plot_storage(df,axe):
   # plt.figure(figsize = (10,8))
    for i in range(1,len(df.columns)):
        axe.plot(df['Vertex'],df[df.columns[i]])
    axe.legend(loc='best')  
    axe.set_xlabel('Vertex')
    axe.set_ylabel('Kilobytes')
    
def plot_comparisons(bundle):
    f, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2,figsize=(20,20))
    axs = [ax1,ax2,ax3, ax4]
    for i in range(len(bundle)):
        plot_storage(bundle[i],axs[i])
    plt.show()

if __name__ == "__main__":
    main()
