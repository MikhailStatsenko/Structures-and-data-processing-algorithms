#include "HashTable.h"

HashTable::HashTable() {
    tableSize = 8;
    cellsFilled = 0;
    table = new forward_list<Node*>[tableSize];
}

/// Метод рехеширования таблицы
void HashTable::rehash(){
    int oldTableSize = tableSize;
    tableSize *= 2;
    forward_list<Node*>* oldTable = table;
    table = new forward_list<Node*>[tableSize];
    for (int i = 0; i < oldTableSize; i++){
        for (auto data : oldTable[i]){
            int hash = getHash(data->key);
            table[hash].push_front(new Node(data->key, data->position));
        }
    }
    delete [] oldTable;
}

/// Хеш-функция
int HashTable::getHash(int key) {
    return key % tableSize;
}

// Метод вывода хеш-таблицы в консоль
void HashTable::print() {
    cout << "\nBuckets\t\t" << "Entries" << endl;
    for (int i = 0; i < tableSize; i++) {
        cout << i+1 << "\t\t\t";
        for (auto data : table[i]) {
            Node* node =  find(data->key);
            cout << "--" << node->key;
        }
        cout << endl;
    }
    cout << endl;
}

/// Метод поиска элемента при помощи хеш-таблицы
Node* HashTable::find(int key) {
    int index = getHash(key);
    for (auto node = table[index].begin(); node != table[index].end(); node++){
        if ((*node)->key == key){
            return *node;
        }
    }
    return nullptr;
}

/// Метод получения поля position узла по ключу
int HashTable::getPos(int key) {
    int position = find(key)->position;
    return position;
}

/// Метод удаления записи из хеш-таблицы
bool HashTable::remove(int key) {
    int index = getHash(key);

    for (auto found = table[index].begin(), deleter = table[index].before_begin();
         found != table[index].end(); found++, deleter++) {
        if ((*found)->key == key) {
            table[index].erase_after(deleter);
            break;
        }
    }
    cellsFilled--;
    return true;
}

/// Метод добавления нового узла в хеш-таблицу
bool HashTable::insert(int key, int pos) {
    // Условие необходимости рехеширования таблицы
    if ((float)(cellsFilled+1)/tableSize > 0.75)
        rehash();
    int hash = getHash(key);
    table[hash].push_front(new Node(key, pos));
    cellsFilled++;
    return true;
}

HashTable::~HashTable(){
    for (int i = 0; i < tableSize; i++){
        for (auto el : table[i]){
            delete el;
        }
    }
    delete [] table;
}
