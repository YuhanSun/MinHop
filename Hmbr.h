//
// Created by ysun138 on 3/8/2017.
//

#ifndef MINHOP_HMBR_H
#define MINHOP_HMBR_H

#include "Universe.h"

void GenerateHMBR_BF(vector<vector<int>> &graph, vector<Entity> &entities, int hop_num, vector<vector<MyRect>> &HMBR);

vector<int> GenerateHMBR(vector<vector<int>> &graph, vector<Entity> &entities, int hop_num, vector<vector<MyRect>> &HMBR);


#endif //MINHOP_HMBR_H
