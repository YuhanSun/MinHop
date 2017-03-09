#include <iostream>
#include "Universe.h"
#include "DataPreprocess.h"
#include "Hmbr.h"
#include "Experiment.h"

#define TIME_RECORD

void OutputHMBR(string output_path, vector<vector<MyRect>> &HMBR, int hop_num)
{
    char * ch = (char*)output_path.c_str();
    freopen(ch, "w", stdout);
    printf("%d,%d\n", HMBR.size(), hop_num);
    for ( int i = 0; i < HMBR.size(); i++)
    {
        for ( int j = 0; j < hop_num; j++)
        {
            MyRect rect = HMBR[i][j];
            if(rect.HasRec)
                printf("1,(%f,%f,%f,%f);",rect.left_bottom.x, rect.left_bottom.y, rect.right_top.x, rect.right_top.y);
            else
                printf("0,(0,0,0,0);");
        }
        printf("\n");
    }
    fclose(stdout);
}



string dataset = "foursquare";

void DataPreprocess()
{
    string dir = "D:\\Ubuntu_shared\\GeoMinHop\\data\\" + dataset;
    string ori_graph_path = dir + "\\graph_entity_newformat.txt";
    string new_graph_path = dir + "\\graph.txt";
    GraphConvert(ori_graph_path,new_graph_path);
}

void test()
{
    vector<int> v1 = vector<int>(3);
    for ( int i = 0; i < v1.size(); i++)
        cout<< v1[i]<<endl;
    cout<<endl;

    vector<int> v2 = vector<int>(1);
    v1 = v2;

    for ( int i = 0; i < v1.size(); i++)
        cout<< v1[i]<<endl;
    cout<<endl;
}

void GenerateHMBR()
{
    string dir = "D:\\Ubuntu_shared\\GeoMinHop\\data\\" + dataset;
    int node_count;
    int hop_num = 6;

    string graph_path = dir + "\\graph.txt";
    vector<vector<int>> graph;
    ReadGraph(graph, node_count, graph_path);

    string entity_path = dir + "\\entity.txt";
    vector<Entity> entities;
    ReadEntity(node_count, entities, entity_path);

    vector<vector<MyRect>> HMBR;
    vector<int> time = GenerateHMBR(graph, entities, hop_num, HMBR);
    OutputHMBR(dir + "\\HMBR.txt", HMBR, hop_num);

    cout << dataset << ": " << time[0] << endl;
    cout << "success"<< endl;
}


int main()
{
//    DataPreprocess();
    GenerateHMBR();
//    IniTime("Gowalla");
//    IniTime("foursquare");
}
