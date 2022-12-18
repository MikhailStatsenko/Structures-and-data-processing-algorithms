#pragma once
#ifndef NODE_RT_H
#define NODE_RT_H

#include "Node.h"

/// Структура узла рандомизированного дерева
struct NodeRT : public Node {
    int size; // Размер в вершинах с корнем в данном узле
    NodeRT *left, *right; // Указатели на левого и правого потомков
    NodeRT(int key, int position) : Node(key, position) {
        size = 1;
        left = right = nullptr;
    }
};

#endif

