#include <random>
#include <chrono>
#include <fstream>
#include <iostream>

#include "HashTable.h"
#include "Insurance.h"

using namespace std;

// Функция, позволяющая задать одинаковую длину строки
// вне зависимости от ввода пользователя
string checkForLength(string str, int targetLen) {
    if (str.size() < targetLen){
        for (int i = str.size(); i < targetLen; i++){
            str += " ";
        }
    } else if (str.size() > targetLen){
        str = str.substr(0, targetLen);
    }
    return str;
}

// Функция, генерирующая информацию о новом человеке
// и возвращающая указатель на экземпляр структуры Insurance
Insurance* generateData(){
    int insuranceNum = rand()%1000000000;
    
    string companyNames[19] = {"Walmart         ", "Amazon          ", "Apple           ", "AT&T            ",
           "Exxon mobile    ", "JPMorgan Chase  ", "Phillips        ", "Wells Fargo     ", "Intel           ",
           "AMD             ", "IBM             ", "HP              ", "Boeing          ", "Tesla           ",
           "Cisco           ", "Nike            ", "Morgan Stanley  ", "Procter & Gamble", "FedEx           "};
    
    string surnames[20] = {"Smith    ", "Johnson  ", "Williams ", "Brown    ", "Jones    ", "Garcia   ",
              "Miller   ", "Davis    ", "Rodriguez", "Martinez ", "Hernandez", "Lopez    ", "Gonzalez ",
              "Wilson   ", "Anderson ", "Thomas   ", "Taylor   ", "Moore    ", "Jackson  ", "Martin   "};
    return new Insurance(insuranceNum, companyNames[rand()%19], surnames[rand()%20]);
}

// Функция, заполняющая данными файл и таблицу одновременно одновременно
// На вход принимает указатель на заполняему хеш-таблицу,
// путь к заполняемому файлу и желаемое количество записей
void fillFileAndTable(HashTable* ht, string path, int recordsNum) {
    fstream file;
    file.open(path, ios::binary | ios::out | ios::trunc);
    file.close();
    Insurance* record;
    for (int i = 0; i < recordsNum; i++){
        record = generateData();
        ht->add(record);
    }
}

int main() {
    srand(time(NULL));
    
    string pathData = "data.txt";
    string pathHelp = "help.txt";
    
    int num = 0, flag = 0;
    HashTable* ht = new HashTable(pathData, pathHelp);
    
    cout << "Введите количество записей в файле: ";
    cin >> flag;
    
    fillFileAndTable(ht, pathData, flag);
    ht->printTable();
    while (flag != 0) {
        cout << "Что нужно сделать?\n0 - Завершить работу программы\n1 - Добавить новый элемент" <<
        "\n2 - Удалить элемент по номеру полиса\n3 - Найти элемент по номеру полиса\n> ";

        cin >> flag;

        switch (flag) {
            case 0:
                cout << "\nРабота программы завершена!" << endl;
                break;
            case 1: {
                string company = "N/A", surname = "No name";
                cout << "\nВведите через пробел номер страхового полиса, компанию и фамилию:\n> ";
                cin >> num >> company >> surname;
                ht->add(new Insurance(num, checkForLength(company, 16), checkForLength(surname, 9)));
                ht->printTable();
                break;
            }
            case 2: {
                cout << "\nВведите номер полиса человека, запись о котором нужно удалить:\n> ";
                cin >> num;
                ht->remove(num);
                ht->printTable();
                break;
            }
            case 3: {
                cout << "\nВведите номер полиса человека, информацию о котором нужно вывести в консоль:\n> ";
                cin >> num;
                auto begin = chrono::high_resolution_clock::now();
                Insurance found = ht->find(num);
                auto end = chrono::steady_clock::now();
                chrono::duration<double, std::milli> time = end - begin;
                cout << '\n' << found.num << ' ' << ht->outputPrettier(found.company)
                     << ' ' << ht->outputPrettier(found.surname) << endl << endl;
                //cout << "На поиск затрачено: " << time.count() << "мс" << endl << endl;
                break;
            }
            default:
                cout << "\nВведена неверная команда, попробуйте еще раз..." << endl << endl;
                break;
        }
    }
    delete ht;
    return 0;
}

