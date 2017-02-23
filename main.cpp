#include <iostream>
#include "Universe.h"

void GenerateHMBR(vector<vector<int>> &graph, vector<Entity> &entities, int hop_num, vector<vector<MyRect>> &HMBR)
{
    HMBR.resize(entities.size());
    for ( int i = 0; i < graph.size(); i++)
    {
        HMBR[i].resize(hop_num);

        vector<int> prehop_neighbors;
        vector<int> curhop_neighbors;
        prehop_neighbors.reserve(entities.size());
        curhop_neighbors.reserve(entities.size());

        prehop_neighbors.push_back(i);
        for ( int j = 0; j < hop_num; j++)
        {
            vector<bool> visited = vector<bool>(entities.size());
            for ( int k = 0; k < prehop_neighbors.size(); k++)
            {
                int pre_id = prehop_neighbors[k];
                for ( int l = 0; l < graph[pre_id].size(); l++)
                {
                    int pre_neighbor_id = graph[pre_id][l];
                    if(visited[pre_neighbor_id])
                        continue;
                    curhop_neighbors.push_back(pre_neighbor_id);
                }
            }

            int k = 0;
            MyRect cur_MBR = MyRect();
            for ( ; k < curhop_neighbors.size(); k++)
            {
                Entity p_entity = entities[curhop_neighbors[k]];
                if(p_entity.IsSpatial)
                {
                    cur_MBR = MyRect(p_entity.location.x, p_entity.location.y, p_entity.location.x, p_entity.location.y);
                    k++;
                    break;
                }
            }
            for ( ; k < curhop_neighbors.size(); k++)
            {
                Entity p_entity = entities[curhop_neighbors[k]];
                if(p_entity.IsSpatial)
                    cur_MBR.MBR(p_entity.location);
            }

            HMBR[i][j] = cur_MBR;
            prehop_neighbors = curhop_neighbors;
            curhop_neighbors.clear();
        }
    }
}

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

int main()
{
    string dir = "D:\\Ubuntu_shared\\Real_Data\\Yelp";
    int node_count;

    string graph_path = dir + "\\graph_entity_newformat.txt";
    vector<vector<int>> graph;
    ReadGraph(graph, node_count, graph_path);

    string entity_path = dir + "\\Random_spatial_distributed\\1\\entity_newformat.txt";
    vector<Entity> entities;
    ReadEntity(node_count, entities, entity_path);

    vector<vector<MyRect>> HMBR;
    GenerateHMBR(graph, entities, 2, HMBR);
    OutputHMBR(dir + "\\HMBR.txt", HMBR, 2);

    cout << "success"<< endl;
}