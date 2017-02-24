//
// Created by ysun138 on 2/23/2017.
//
#include "DataPreprocess.h"

void ReadGraph(vector<set<int>> &graph, string filepath)
{
    int node_count;
    char *ch = (char *)filepath.data();
    freopen(ch, "r", stdin);

    scanf("%d\n", &node_count);
    graph.resize(node_count);

    for (int i = 0; i < node_count; i++)
    {
        int id, count, outid;
        scanf("%d,%d", &id, &count);
        for (int j = 0; j < count; j++)
        {
            scanf(",%d", &outid);
            graph[i].insert(outid);
        }
    }
    fclose(stdin);
}

void OutputGraph(vector<set<int>> &graph, string filepath)
{
    char *ch = (char *)filepath.data();
    freopen(ch, "w", stdout);

    printf("%d\n", graph.size());
    for (int i = 0; i < graph.size(); i++)
    {
        printf("%d,%d", i, graph[i].size());
        set<int>::iterator end = graph[i].end();
        for (set<int>::iterator iter = graph[i].begin(); iter != end; iter++)
        {
            printf(",%d", *iter);
        }
        printf("\n");
    }
    fclose(stdout);
}

void GraphConvert(string ori_graph_path, string new_graph_path)
{
    vector<set<int>> graph;
    ReadGraph(graph, ori_graph_path);

    for ( int i = 0; i < graph.size(); i++)
    {
        set<int>::iterator end = graph[i].end();
        for ( set<int>::iterator iter = graph[i].begin(); iter != end; iter++)
        {
            int neighbor = *iter;
            graph[neighbor].insert(i);
        }
    }

    OutputGraph(graph, new_graph_path);
}