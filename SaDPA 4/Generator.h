#pragma once
#ifndef GENERATOR_H
#define GENERATOR_H

#include "Insurance.h"

/// Класс генератора случайных записей
/// для заполнения структуры данных
class Generator {
    static string companyNames[19];
    static string surnames[20];
public:
    static Insurance* getRecord();
};

#endif


