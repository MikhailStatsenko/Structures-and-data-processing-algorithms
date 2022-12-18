#pragma once
#ifndef NODE_BST_H
#define NODE_BST_H

#include "Node.h"

/// Структура узла бинарного дерева поиска
struct NodeBST : public Node {
    NodeBST *left, *right; // Указатели на левого и правого потомков
    NodeBST(int key, int position) : Node(key, position) {
        left = right = nullptr;
    }
};

#endif

