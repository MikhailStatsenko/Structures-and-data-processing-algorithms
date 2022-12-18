#pragma once
#ifndef DATASTUCTURE_H
#define DATASTUCTURE_H

#include "Node.h"

/// Абстрактный класс Структуры Данных
class DataStructure {
public:
    virtual void print() = 0;
    virtual Node* find(int key) = 0;
    virtual int getPos(int key) = 0;
    virtual bool remove(int key) = 0;
    virtual bool insert(int key, int pos) = 0;
    virtual ~DataStructure() {}
};

#endif

