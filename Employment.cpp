//
// Created by AdisAlagic on 15.04.2020.
//

#include "Employment.h"

using namespace std;

Employment::Employment(const string &name,const string &surname,const  string &middleName,const string &function,const int &salary) {
    this->name = name;
    this->surname = surname;
    this->middleName = middleName;
    this->function = function;
    this->salary = salary;
}

string Employment::get_name() {
    return name;
}

string Employment::get_surname() {
    return surname;
}

string Employment::get_middle_name() {
    return middleName;
}

string Employment::get_function() {
    return function;
}

int Employment::get_salary() const {
    return salary;
}

void Employment::setName(const string &n) {
    Employment::name = n;
}

void Employment::setSurname(const string &sn) {
    Employment::surname = sn;
}

void Employment::setMiddleName(const string &mn) {
    Employment::middleName = mn;
}

void Employment::setFunction(const string &f) {
    Employment::function = f;
}

void Employment::setSalary(int s) {
    Employment::salary = s;
}

void Employment::clear() {
    name.clear();
    surname.clear();
    middleName.clear();
    function.clear();
    salary = -1;
}

Employment Employment::getEmpty() {
    Employment employment{"", "", "", ""};
    return employment;
}

