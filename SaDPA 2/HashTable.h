#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <fstream>
#include <iostream>
#include <forward_list>

#include "Insurance.h"

using namespace std;

class HashTable {
    enum ActiveFile {FIRST, SECOND};
    struct Node {
        int key, position;
        Node(int key, int position);
    };
    ActiveFile activeFile;
    int tableSize = 8, cellsFilled = 0;
    string dataFilePath, helpFilePath;
    forward_list<Node*>* table;
    
    void rehash();
    int getHash(int num);
    string getActiveFilePath();
public:
    HashTable(string dataFilePath, string helpFilePath);
    bool add(Insurance* data);
    bool remove(int num);
    Insurance find(int num);
    void printTable();
    ~HashTable();
    string outputPrettier(string str);
};

#endif

