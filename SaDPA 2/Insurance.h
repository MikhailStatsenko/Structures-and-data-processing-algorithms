#pragma once
#ifndef INSURANCE_H
#define INSURANCE_H

#include <string>

using namespace std;

struct Insurance {
	int num;
	string company, surname;
    Insurance();
	Insurance(int num, string company, string surname);
};

#endif

