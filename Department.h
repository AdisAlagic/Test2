//
// Created by AdisAlagic on 15.04.2020.
//

#ifndef TEST2_DEPARTMENT_H
#define TEST2_DEPARTMENT_H

#include <vector>
#include "Employment.h"

using namespace std;

enum Type{
    NAME,
    SURNAME,
    MIDDLE_NAME,
    FUNCTION,
    SALARY
};

class Department {
private:
    vector<Employment> employments;
    string name;
public:
    explicit Department(const string &name);

    Department(const string &name, vector<Employment> employments);

    void add_employment(const string &n, const string &surname, const string &middleName, const string &function,
                        const int &salary = 0);

    void add_employment(const Employment &employment);

    void remove_employment(char *n);

    void remove_employment(int index);

    void remove_last_employment();

    void remove_first_employment();

    Employment get_employment(int index);

    Employment get_employment(char *n, Type searchBy);

    int get_amount_of_employments();

    string get_name();

    void set_name(string str);

    void clear();

    int getAverageSalary();
};


#endif //TEST2_DEPARTMENT_H
