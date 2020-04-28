//
// Created by AdisAlagic on 15.04.2020.
//

#include "Department.h"


Department::Department(const string &name) {
    this->name = name;
}

Department::Department(const string &name, vector<Employment> employments) {
    this->employments = std::move(employments);
}

void
Department::add_employment(const string &n, const string &surname, const string &middleName, const string &function,
                           const int &salary) {
    Employment employment(n, surname, middleName, function, salary);
    employments.push_back(employment);
}

void Department::add_employment(const Employment &employment) {
    employments.push_back(employment);
}

void Department::remove_employment(char *n) {
    for (auto it = employments.begin(); it != employments.end(); it++){
        if (it->get_name() == n || it->get_surname() == n || it->get_middle_name() == n){
            employments.erase(it);
        }
    }
}

void Department::remove_employment(int index) {
    employments.erase(employments.begin() + (index - 1));
}

Employment Department::get_employment(int index) {
    return employments.at(index);
}
/**
 * Why though I need enum?
 * @param n
 * @param searchBy
 * @return
 */
Employment Department::get_employment(char *n, Type searchBy) {
    switch (searchBy) {
        case NAME:
            for (auto it = employments.begin(); it != employments.end(); it++){
                if (it->get_name() == n){
                    return *it.base();
                }
            }
            break;
        case SURNAME:
            for (auto it = employments.begin(); it != employments.end(); it++){
                if (it->get_surname() == n){
                    return *it.base();
                }
            }
            break;
        case MIDDLE_NAME:
            for (auto it = employments.begin(); it != employments.end(); it++){
                if (it->get_middle_name() == n){
                    return *it.base();
                }
            }
            break;
        case FUNCTION:
            for (auto it = employments.begin(); it != employments.end(); it++){
                if (it->get_function() == n){
                    return *it.base();
                }
            }
            break;
        case SALARY:
            for (auto it = employments.begin(); it != employments.end(); it++){
                if (it->get_salary() == atoi(n)){
                    return *it.base();
                }
            }
            break;
    }
    throw exception();
}

void Department::remove_last_employment() {
    employments.erase(employments.end());
}

void Department::remove_first_employment() {
    employments.erase(employments.begin());
}

int Department::get_amount_of_employments() {
    return employments.size();
}

string Department::get_name() {
    return name;
}

void Department::set_name(string str) {
    name = std::move(str);
}

void Department::clear() {
    name.clear();
    employments.clear();
}

int Department::getAverageSalary() {
    int res = 0;
    if (employments.empty()){
        return 0;
    }
    for (auto & employment : employments) {
        res += employment.get_salary();
    }
    res /= employments.size();
    return res;
}


