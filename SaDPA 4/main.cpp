#include <random>
#include <chrono>
#include <fstream>
#include <iostream>

#include "File.h"
#include "Insurance.h"
#include "Generator.h"
#include "HashTable.h"
#include "DataStructure.h"
#include "RandomizedTree.h"
#include "BinarySearchTree.h"

using namespace std;

void menu(string firstPath, string secondPath) {
    int num = 0, flag = 0;
    DataStructure* dataStruct;
    File* file = new File(firstPath, secondPath);
    
    cout << "Для выбора структуры введите\n1 - Хеш-таблица, 2 - Бинарное дерево, 3 - Рандомизированное дерево поиска: ";
    while (flag < 1 || flag > 3) {
        cin >> flag;
        switch (flag) {
            case 1:
                cout << "\nВыбрана хеш-таблица" << endl;
                dataStruct = new HashTable();
                break;
            case 2:
                cout << "\nВыбрано бинарное дерево поиска" << endl;
                dataStruct = new BinarySearchTree();
                break;
            case 3:
                cout << "\nВыбрано рандомизированное дерево" << endl;
                dataStruct = new RandomizedTree();
                break;
            default:
                cout << "\nТакой структуры данных нет, попробуйте еще раз:";
        }
    }
    
    cout << "\nВведите количество записей в файле: ";
    cin >> num;
    
    flag = 0;
    cout << "\nЗаполнить файл: 1 - случайными данными, 2 - возрастающей последовательностью: ";
    while (flag != 1 && flag != 2) {
        cin >> flag;
        switch (flag) {
            case 1: // Заполнение случайными данными
                file->fillWith(num);
                break;
            case 2: // Заполнение возрастающей последовательностью
                file->fillWithIncreasingSeq(num);
                break;
            default:
                cout << "Неверный ввод, попробуйте еще раз: ";
        }
    }
    file->readTo(dataStruct);
    dataStruct->print();
    
    while (flag != 0) {
        cout << "Что нужно сделать?\n0 - Завершить работу программы\n1 - Добавить новую запсь" <<
        "\n2 - Удалить элемент по номеру полиса\n3 - Найти элемент по номеру полиса\n> ";

        cin >> flag;
        switch (flag) {
            case 0: // Завершение работы программы
                cout << "\nРабота программы завершена!" << endl;
                break;
            case 1: { // Добавление узла
                string company = "N/A", surname = "No name";
                cout << "\nВведите через пробел номер страхового полиса, компанию и фамилию:\n> ";
                cin >> num >> company >> surname;
                int position = file->insert(num, company, surname);
                dataStruct->insert(num, position);
                dataStruct->print();
                break;
            }
            case 2: { // Удаление элемента
                cout << "\nВведите номер полиса человека, запись о котором нужно удалить:\n> ";
                cin >> num;
                file->remove(dataStruct->getPos(num), dataStruct);
                dataStruct->remove(num);
                dataStruct->print();
                break;
            }
            case 3: { // Поиск элемента
                cout << "\nВведите номер полиса человека, информацию о котором нужно вывести в консоль:\n> ";
                cin >> num;
                Insurance* found = file->find(dataStruct->getPos(num));
                cout << *found << endl;
                break;
            }
            default:
                cout << "\nВведена неверная команда, попробуйте еще раз..." << endl << endl;
                break;
        }
    }
    delete dataStruct;
}

int main(int argc, const char * argv[]) {
    string firstPath = "data.txt";
    string secondPath = "help.txt";
    
    srand(time(0));
    
    menu(firstPath, secondPath);
    
    return 0;
}

ostream& operator<<(ostream& os, const Insurance& data) {
    os << '\n' << data.num << ' ' << Insurance::outputPrettier(data.company)
            << ' ' << Insurance::outputPrettier(data.surname) << endl;
    return os;
}
