//
// Created by ysun138 on 3/8/2017.
//

#include "Hmbr.h"

/**
 * Brutal force very slow, 100 hrs for yelp.
 * For each node each hop, calculate all reachable nodes.
 * Then calculate HMBR.
 * @param graph
 * @param entities
 * @param hop_num
 * @param HMBR
 */
void GenerateHMBR_BF(vector<vector<int>> &graph, vector<Entity> &entities, int hop_num, vector<vector<MyRect>> &HMBR)
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
                    visited[pre_neighbor_id] = true;
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

        cout << i << endl;
        for ( int j = 0; j < hop_num; j++)
            cout <<HMBR[i][j].left_bottom.x << "," << HMBR[i][j].left_bottom.y << "," << HMBR[i][j].right_top.x << "," << HMBR[i][j].right_top.y<<endl;
        cout << endl;
    }
}

/**
 * Dynamically update the HMBR of all the nodes based on previous hop
 * @param graph
 * @param entities
 * @param hop_num
 * @param HMBR
 * @return
 */
vector<int> GenerateHMBR(vector<vector<int>> &graph, vector<Entity> &entities, int hop_num, vector<vector<MyRect>> &HMBR)
{
    vector<int> v_time;
    HMBR.resize(entities.size());
    for ( int i = 0; i < graph.size(); i++)
        HMBR[i].resize(hop_num);

    int start = clock();
    //initialize HMBR[i][0] (the HMBR for 1 hop)
    for ( int i = 0; i < graph.size(); i++)
        for ( int j = 0; j < graph[i].size(); j++)
        {
            int neighbor = graph[i][j];
            if(entities[neighbor].IsSpatial)
                HMBR[i][0].MBR(entities[neighbor].location);
        }

    //initialize HMBR[i][1]~[hop_num-1]
    for ( int i = 1; i < hop_num; i++)
    {
        for ( int j = 0; j < graph.size(); j++)
        {
            for ( int k = 0; k < graph[j].size(); k++)
            {
                int neighbor = graph[j][k];
                HMBR[j][i].MBR(HMBR[neighbor][i-1]);
            }
        }
    }
    int time = clock() - start;
    v_time.push_back(time);
    return v_time;
}