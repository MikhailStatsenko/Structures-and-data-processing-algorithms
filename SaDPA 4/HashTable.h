#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <iostream>
#include <forward_list>

#include "Insurance.h"
#include "DataStructure.h"

using namespace std;

/// Класс хеш-таблицы:
/// наследуется от абстрактного класса Структуры Данных
/// Таблица состоит из динамического массива
/// однонаправленных списков, содержащих узлы Node
class HashTable : public DataStructure {
    int cellsFilled, tableSize;
    forward_list<Node*>* table;
    
    void rehash();
    int getHash(int key);
public:
    HashTable();
    
    void print() override;
    Node* find(int key) override;
    int getPos(int key) override;
    bool remove(int key) override;
    bool insert(int key, int pos) override;
    
    ~HashTable();
};

#endif


