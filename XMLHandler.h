//
// Created by AdisAlagic on 16.04.2020.
//

#ifndef TEST2_XMLHANDLER_H
#define TEST2_XMLHANDLER_H

#include "Department.h"
#include "pugixml.hpp"
#include <stack>
#include <fstream>

enum HistoryType{
    UNDO,
    REDO
};

class XMLHandler {
public:
    XMLHandler(const char *name, vector<Department> &departments);

    void addDepartment(Department &department);

    void editDepartment(const int &index, const char *newName);

    void removeDepartment(const int &index);

    void addEmployment(const int &index, Employment &employment);

    void editEmployment(const int &index, Employment &empName, Type type, const char *newItem);

    void removeEmployment(const int &depIndex, const int &empIndex);

    void undoChange();

    void redoChange();
private:
    static void printResult(const bool &operation);

    pugi::xml_node findDepartment(Department &department);
    string name;

    void readXML(vector<Department> &d);

    void save(HistoryType type, bool deleteRedo);
    vector<Department> *departments;
    pugi::xml_document document;
    pugi::xml_parse_result result;
    stack<string> undo;
    stack<string> redo;
};


#endif //TEST2_XMLHANDLER_H
