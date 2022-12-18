#pragma once
#ifndef RANDOMIZED_TREE_H
#define RANDOMIZED_TREE_H

#include <iomanip>
#include <iostream>

#include "NodeRT.h"
#include "DataStructure.h"

using namespace std;

/// Класс рандомизированного дерева: наследуется
/// от абстрактного класса Структуры Данных
/// Дерево состоит из узлов NodeRT,   унаследованных от Node
class RandomizedTree : public DataStructure {
private:
    NodeRT* root; // Корень всего дерева
    
    void clear(NodeRT* p);
    int getSize(NodeRT* p);
    void fixSize(NodeRT* p);
    
    // Методы вставки узла в дерево
    NodeRT* rotateLeft(NodeRT* p);
    NodeRT* rotateRight(NodeRT* p);
    NodeRT* insert(NodeRT* p, int key, int pos);
    NodeRT* insertRoot(NodeRT* p, int key, int pos);
    
    // Методы удаления узла из дерева
    NodeRT* remove(NodeRT* p, int key);
    NodeRT* merge(NodeRT* p, NodeRT* q);
    
    // Метод поиска узла в дереве
    NodeRT* find(NodeRT* p, int key);
    
    // Методы вывода дерева в консоль
    int maxDepth(NodeRT* p);
    void printTreeSimple(NodeRT* p, int depth);
    void printTree(NodeRT* p, int depth, int maxDepth);
    void drawTableLine(int colWidth, int colCount, string cornerStart, string columnConnect, string cornerEnd);
public:    
    RandomizedTree();
    // Метод упрощенного вывода в консоль
    void printSimple();
    
    // Реализация абстрактынх методов-интерфейсов базового класса
    void print() override;
    bool remove(int key) override;
    int getPos(int key) override;
    NodeRT* find(int key) override;
    bool insert(int key, int pos) override;
    
    ~RandomizedTree();
};

#endif

