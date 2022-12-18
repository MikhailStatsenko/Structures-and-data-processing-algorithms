#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>
#include <forward_list>

using namespace std;

class Graph {
private:
    int verticeCnt;
    
    // Вектор содержит списки вершин, смежных данной
    // Узел списка хранит номер смежной вершины и вес ребра,
    // ведущего к ней
    vector<forward_list<pair<int, int>>*> adjacencyList;
    
    vector<vector<int>> listToMatrix();
public:
    Graph(int verticesCnt);
    void printList();
    void floydAlgorithm(int from, int to);
    bool addEdge(int from, int to, int weight=1);
    int findEccentricity(int vertice, int length=0, vector<int>* visited = nullptr);
};

#endif


