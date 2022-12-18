#include "HashTable.h"

// Конструктор хеш-таблицы
HashTable::HashTable(string dataFilePath, string helpFilePath) {
    table = new forward_list<Node*>[tableSize];
    this->dataFilePath = dataFilePath;
    this->helpFilePath = helpFilePath;
    activeFile = FIRST;
}

// Конструктор информационной части узла однонаправленного списка
HashTable::Node::Node(int key, int position){
    this->key = key;
    this->position = position;
}

// Деструктор хеш-таблицы
HashTable::~HashTable(){
    // Удаление информационной части узла списка Node
    for (int i = 0; i < tableSize; i++){
        for (auto el : table[i]){
            delete el;
        }
    }
    delete [] table;
}

// Хеш-функция
int HashTable::getHash(int num) {
    return num % tableSize;
}

// Метод добавления нового элемента в хеш-таблицу и файл одновременно
bool HashTable::add(Insurance* data) {
    string path = getActiveFilePath();
    
    fstream file;
    file.open(path, ios::binary | ios::app | ios::out);
    
    if (!file.is_open()){
        cout << "Ошибка открытия файла, добавление записи невозможно" << endl;
    }
    else {
        // Условие необходимости рехеширования таблицы
        if ((float)(cellsFilled+1)/tableSize > 0.75)
            rehash();
        
        int hash = getHash(data->num);
        // cellsFilled <=> индексу последней свободной позиции в файле
        table[hash].push_front(new Node(data->num, cellsFilled));
        file.write((char*)data, sizeof(Insurance));
        cellsFilled++;
        file.close();
        delete data;
        return true;
    }
    file.close();
    delete data;
    return false;
}

// Метод удаления записи из хеш-таблицы и файла
bool HashTable::remove(int num) {
    string oldPath, newPath;
    // Выбор пути к бинарному файлу с актуальной информацией об объектах
    if (activeFile == FIRST){
        oldPath = dataFilePath;
        newPath = helpFilePath;
    }
    else {
        oldPath = helpFilePath;
        newPath = dataFilePath;
    }
    fstream oldFile, newFile;
    oldFile.open(oldPath, ios::binary | ios::in);
    newFile.open(newPath, ios::binary | ios::out | ios::trunc);
    
    int index = getHash(num);
    if (!oldFile.is_open() || !newFile.is_open()) {
        cout << "Ошибка открытия файла, удаление записи невозможно" << endl;
    }
    else if (table[index].empty()) {
        cout << "\nЗапись не найдена" << endl;
    }
    else {
        int position = -1; // Позиция удаляемого элемента в файле
        // found участвует в поиске элемента, соответствующего удаляемому
        // deleter является итератором, указывающим на элемент,
        // находящийся до foudn, необходим из-за специфики работы forward_list
        for (auto found = table[index].begin(), deleter = table[index].before_begin();
             found != table[index].end(); found++, deleter++) {
            if ((*found)->key == num) {
                position = (*found)->position;
                table[index].erase_after(deleter);
                break;
            }
        }
        if (position == -1){ // Если запись найдена, position может принимать значение 0 и более
            cout << "\nЗапись не найдена" << endl;
            return false;
        }
        Insurance* insuranceData = new Insurance();
        // cellsFilled эквивалентно числу числу запианных в файле объектов
        for (int i = 0; i < cellsFilled; i++){
            oldFile.read((char*)insuranceData, sizeof(Insurance));
            if (i == position)
                break;
            newFile.write((char*)insuranceData, sizeof(Insurance));
        }
        // У элементов, которые находились после удаленного нужно изменить номер позиции в файле на 1 влево
        for (int i = position+1; i < cellsFilled; i++){
            oldFile.read((char*)insuranceData, sizeof(Insurance));
            int num = insuranceData->num;
            int hash = getHash(num);
            for (auto record = table[hash].begin(); record != table[hash].end(); record++){
                if ((*record)->key == num){
                    (*record)->position--;
                    break;
                }
            }
            newFile.write((char*)insuranceData, sizeof(Insurance));
        }
        cellsFilled--;
        oldFile.close(); newFile.close();
        delete insuranceData;
        (activeFile == FIRST) ? activeFile = SECOND : activeFile = FIRST;
        return true;
    }
    return false;
}

// Метод поиска элемента при помощи хеш-таблицы и возвращения данных о нем из файла
Insurance HashTable::find(int num) {
    int position = -1, index = getHash(num);
    for (auto record = table[index].begin(); record != table[index].end(); record++){
        if ((*record)->key == num){
            position = (*record)->position;
            break;
        }
    }
    if (position == -1){
        cout << "\nЗапись не найдена" << endl;
        return Insurance(0, "N/A", "No name");
    }
    
    fstream file;
    file.open(getActiveFilePath(), ios::binary | ios::in);
    file.seekg(sizeof(Insurance)*position);
    
    Insurance* record = new Insurance();
    file.read((char*)record, sizeof(Insurance));
    return *record;
}

// Метод рехеширования таблицы
void HashTable::rehash(){
    int oldTableSize = tableSize;
    tableSize *= 2;
    forward_list<Node*>* tmp;
    forward_list<Node*>* oldTable = new forward_list<Node*>[tableSize];
    tmp = table;
    table = oldTable;
    oldTable = tmp;
    for (int i = 0; i < oldTableSize; i++){
        for (auto data : oldTable[i]){
            int hash = getHash(data->key);
            table[hash].push_front(new Node(data->key, data->position));
        }
    }
    delete [] oldTable;
}

// Метод вывода хеш-таблицы в консоль
void HashTable::printTable() {
    cout << "\nBuckets\t\t" << "Entries" << endl;
    for (int i = 0; i < tableSize; i++) {
        cout << i+1 << "\t\t\t";
        for (auto data : table[i]) {
            Insurance record =  find(data->key);
            cout << "--" << "(" << record.num << ", " <<
            outputPrettier(record.company) << ", " << outputPrettier(record.surname) << ")";
        }
        cout << endl;
    }
    cout << endl;
}

// Закрытый метод, возвращающий путь к файлу с актуальными данными, связанными с таблицей
string HashTable::getActiveFilePath(){
   return (activeFile == FIRST) ? dataFilePath : helpFilePath;
}

// Метод для вывода строковых полей без лишних пробелов в конце
string HashTable::outputPrettier(string str){
    int i = str.size()-1;
    while (str[i] == ' ') {i--;}
    return str.substr(0, i+1);
}
