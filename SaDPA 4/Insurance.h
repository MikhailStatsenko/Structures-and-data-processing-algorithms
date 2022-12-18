#pragma once
#ifndef INSURANCE_H
#define INSURANCE_H

#include <string>
#include <iostream>

using namespace std;

/// Структура записи файла, соответствующая варианту
struct Insurance {
    int num;
    string company, surname;
    Insurance(){};
    Insurance(int num, string company, string surname){
        this->num = num;
        this->company = company;
        this->surname = surname;
    }
    
    /// Метод для вывода строковых полей без лишних пробелов в конце
    static string outputPrettier(string str){
        int i = str.size()-1;
        while (str[i] == ' ') {i--;}
        return str.substr(0, i+1);
    }
    
    friend ostream& operator<<(ostream& os, const Insurance& data);
};

#endif



