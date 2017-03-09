//
// Created by ysun138 on 3/2/2017.
//

#include "Experiment.h"

void IniTime(string dataset)
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
    cout << dataset << ": " << time[0] << endl;
}
