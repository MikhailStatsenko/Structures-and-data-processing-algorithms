#pragma once
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iomanip>
#include <iostream>

#include "NodeBST.h"
#include "DataStructure.h"

using namespace std;

/// Класс бинарного дерева поиска:
/// наследуется от абстрактного класса Структуры Данных
/// Дерево состоит из узлов NodeBST,   унаследованных от Node
class BinarySearchTree : public DataStructure {
private:
    NodeBST* root; // Корень всего дерева
    
    void clear(NodeBST* p);
    NodeBST* findAssignee(NodeBST* p);
    NodeBST* find(NodeBST* p, int key);
    NodeBST* remove(NodeBST* p, int key);
    NodeBST* insert(NodeBST* p, int key, int pos);
    
    // Методы вывода дерева в консоль
    int maxDepth(NodeBST* p);
    void printTreeSimple(NodeBST* p, int depth);
    void printTree(NodeBST* p, int depth, int maxDepth);
    void drawTableLine(int colWidth, int colCount, string cornerStart, string columnConnect, string cornerEnd);
public:
    BinarySearchTree();
    void printSimple();
    
    // Реализация абстрактынх методов-интерфейсов базового класса
    void print() override;
    bool remove(int key) override;
    int getPos(int key) override;
    NodeBST* find(int key) override;
    bool insert(int key, int pos) override;
    
    ~BinarySearchTree();
};

#endif



