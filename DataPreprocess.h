
//
// Created by ysun138 on 2/23/2017.
//

#ifndef MINHOP_DATAPREPROCESS_H
#define MINHOP_DATAPREPROCESS_H

#include "Universe.h"

void ReadGraph(vector<set<int>> &graph, string filepath);

void OutputGraph(vector<set<int>> &graph, string filepath);

void GraphConvert(string ori_graph_path, string new_graph_path);


#endif //MINHOP_DATAPREPROCESS_H