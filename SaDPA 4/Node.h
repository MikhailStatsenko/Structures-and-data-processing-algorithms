#pragma once
#ifndef NODE_H
#define NODE_H

/// Базовая структура  узла структуры данных
struct Node {
    int key, position;
    Node(int key, int position) {
        this->key = key;
        this->position = position;
    }
};

#endif

