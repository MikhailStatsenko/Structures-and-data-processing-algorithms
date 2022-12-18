#include "File.h"

File::File(string firstPath, string secondPath) {
    recordCount = 0;
    this->firstPath = firstPath;
    this->secondPath = secondPath;
}

/// Метод получения пути к файлу с актуальными данными
string File::getActiveFilePath(){
    return (activeFile == FIRST) ? firstPath : secondPath;
}

/// Метод, задающий одинаковую длину строки
/// вне зависимости от ввода пользователя
string File::checkForLength(string str, int targetLen) {
    if (str.size() < targetLen){
        for (int i = str.size(); i < targetLen; i++){
            str += " ";
        }
    } else if (str.size() > targetLen){
        str = str.substr(0, targetLen);
    }
    return str;
}


/// Метод заполнения файла случайными объектами класса Incurance
bool File::fillWith(int recordsNum) {
    fstream file;
    file.open(getActiveFilePath(), ios::binary | ios::out | ios::trunc);
    
    if (!file.is_open()) {
        cout << "\nОшибка открытия файла при заполнении" << endl;
        return false;
    }
    Insurance* record;
    for (int i = 0; i < recordsNum; i++){
        recordCount++;
        record = Generator::getRecord(); // Генерация новой записи
        file.write((char*)record, sizeof(Insurance));
    }
    file.close();
    return true;
}

/// Метод заполнения структуры данных информацией об объектах из файла
/// На вход принимает объект-наследник класса абстрактной СД
bool File::readTo(DataStructure* dataStruct) {
    string path = getActiveFilePath();
    
    fstream file;
    file.open(path, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "\nОшибка открытия файла при чтении в структуру данных" << endl;
    }

    int i = 0;
    Insurance* record = new Insurance();
    while (file.read((char*)record, sizeof(Insurance))){
        dataStruct->insert(record->num, i++);
    }
    file.close();
    return true;
}

/// Метод заполнения файла данными с возрастающими ключами
bool File::fillWithIncreasingSeq(int recordsNum) {
    fstream file;
    file.open(getActiveFilePath(), ios::binary | ios::out | ios::trunc);
    
    if (!file.is_open()) {
        cout << "\nОшибка открытия файла при заполнении" << endl;
        return false;
    }
    Insurance* record;
    for (int i = 0; i < recordsNum; i++){
        recordCount++;
        record = Generator::getRecord(); // Генерация новой записи
        record->num = i+1; // Замена поля-ключа значением счетчика
        file.write((char*)record, sizeof(Insurance));
    }
    file.close();
    return true;
}


/// Метод поиска данных в файле
/// На вход принимает позицию записи об объекте в файле
Insurance* File::find(int pos) {
    if (pos < 0){
        cout << "\nВ исходной структуре данных запись не найдена" << endl;
        return nullptr;
    }
    
    fstream file;
    file.open(getActiveFilePath(), ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "\nОшибка открытия файла при поиске" << endl;
        return nullptr;
    }
    
    file.seekg(sizeof(Insurance)*pos); // Перемещение указателя на нужную позицию
    
    Insurance* record = new Insurance();
    file.read((char*)record, sizeof(Insurance));
    return record;
}

/// Метод удаления записи из файла
/// На вход принимает позицию записи об удаляемом объекте в файле
/// и указатель на наследника абстрактного класса структуры данных
bool File::remove(int pos, DataStructure* dataStruct) {
    string oldPath, newPath;
    // Выбор пути к файлу с актуальной информацией об объектах
    if (activeFile == FIRST){
        oldPath = firstPath;
        newPath = secondPath;
    }
    else {
        oldPath = secondPath;
        newPath = firstPath;
    }
    
    // Из oldFile в newFile переписываются все записи кроме удаляемой
    fstream oldFile, newFile;
    oldFile.open(oldPath, ios::binary | ios::in);
    newFile.open(newPath, ios::binary | ios::out | ios::trunc);
    if (!oldFile.is_open() || !newFile.is_open()) {
        cout << "\nОшибка открытия файла при удалении" << endl;
    }
    else if (pos < 0) {
        cout << "\nВ исходной структуре данных запись не найдена" << endl;
    }
    else {
        Insurance* insuranceData = new Insurance();
        for (int i = 0; i < recordCount; i++){
            oldFile.read((char*)insuranceData, sizeof(Insurance));
            if (i == pos)
                break;
            newFile.write((char*)insuranceData, sizeof(Insurance));
        }
        // У записей, находившихся после удаленной нужно уменьшить номер позиции в файле на 1
        for (int i = pos+1; i < recordCount; i++){
            oldFile.read((char*)insuranceData, sizeof(Insurance));
            int key = insuranceData->num;
            Node* node = dataStruct->find(key);
            node->position--;
            newFile.write((char*)insuranceData, sizeof(Insurance));
        }
        oldFile.close(); newFile.close();
        delete insuranceData;
        recordCount--;
        // Изменение указания на файл с актуальными данными
        (activeFile == FIRST) ? activeFile = SECOND : activeFile = FIRST;
        return true;
    }
    return false;
}

/// Метод вставки новой записи в файл
/// На вход принимает данные, хранимые в структуре Insurance
int File::insert(int num, string company, string surname) {
    // Строковые поля записи всегда одинаковой длины
    Insurance* record = new Insurance(num, checkForLength(company, 16), checkForLength(surname, 9));
    
    fstream file;
    file.open(getActiveFilePath(), ios::binary | ios::out | ios::app);
    if (!file.is_open()) {
        cout << "\nОшибка открытия файла при вставке" << endl;
        return -1;
    }
    file.write((char*)record, sizeof(Insurance));
    file.close();
    
    return recordCount++;
}
