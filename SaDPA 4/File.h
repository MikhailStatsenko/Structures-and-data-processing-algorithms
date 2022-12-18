#pragma once
#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>

#include "Insurance.h"
#include "Generator.h"
#include "DataStructure.h"

/// Класс файла, помогающего
/// взаимодействовать со структурами данных
class File {
    enum ActiveFile {FIRST, SECOND};
    int recordCount; // Количество записей в файле
    ActiveFile activeFile; // Индикатор файла с актуальными данными
    string firstPath, secondPath;
    
    string getActiveFilePath();
    string checkForLength(string str, int targetLen);
public:
    File(string firstPath, string secondPath);
    
    bool fillWith(int recordsNum);
    bool readTo(DataStructure* dataStruct);
    bool fillWithIncreasingSeq(int recordsNum);
    
    Insurance* find(int pos);
    bool remove(int pos, DataStructure* dataStruct);
    int insert(int num, string company, string surname);
};

#endif

