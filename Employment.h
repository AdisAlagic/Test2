//
// Created by AdisAlagic on 15.04.2020.
//

#ifndef TEST2_EMPLOYMENT_H
#define TEST2_EMPLOYMENT_H

#include <string>


using namespace std;

class Employment {
private:
    string name, surname, middleName, function;
    int salary = 0;
public:
    Employment(const string &name, const string &surname, const string &middleName, const string &function,
               const int &salary = 0);

    string get_name();

    string get_surname();

    string get_middle_name();

    string get_function();

    [[nodiscard]] int get_salary() const;

    void setName(const string &n);

    void setSurname(const string &sn);

    void setMiddleName(const string &mn);

    void setFunction(const string &f);

    void setSalary(int s);

    void clear();

    static Employment getEmpty();
};


#endif //TEST2_EMPLOYMENT_H
