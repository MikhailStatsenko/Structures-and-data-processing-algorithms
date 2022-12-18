#include "Generator.h"

/// Инициализация статического массива названий компаний
string Generator::companyNames[19] = {"Walmart         ", "Amazon          ", "Apple           ", "AT&T            ",
    "Exxon mobile    ", "JPMorgan Chase  ", "Phillips        ", "Wells Fargo     ", "Intel           ",
    "AMD             ", "IBM             ", "HP              ", "Boeing          ", "Tesla           ",
    "Cisco           ", "Nike            ", "Morgan Stanley  ", "Procter & Gamble", "FedEx           "};

/// Инициализация статического массива фамилий
string Generator::surnames[20] = {"Smith    ", "Johnson  ", "Williams ", "Brown    ", "Jones    ", "Garcia   ",
          "Miller   ", "Davis    ", "Rodriguez", "Martinez ", "Hernandez", "Lopez    ", "Gonzalez ",
          "Wilson   ", "Anderson ", "Thomas   ", "Taylor   ", "Moore    ", "Jackson  ", "Martin   "};

/// Статический метод генерации новой записи
Insurance* Generator::getRecord(){
    int insuranceNum = rand()%1000000000;
    return new Insurance(insuranceNum, companyNames[rand()%19], surnames[rand()%20]);
}


