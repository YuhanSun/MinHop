
//
// Created by ysun138 on 2/23/2017.
//

#ifndef MINHOP_DATAPREPROCESS_H
#define MINHOP_DATAPREPROCESS_H

#include "Universe.h"

void ReadGraph(vector<set<int>> &graph, string filepath);

void OutputGraph(vector<set<int>> &graph, string filepath);

/**
 * convert from directional to bi-directional
 * make sure if a-->b exists then b-->a exists as well
 * @param ori_graph_path
 * @param new_graph_path
 */
void GraphConvert(string ori_graph_path, string new_graph_path);


#endif //MINHOP_DATAPREPROCESS_H