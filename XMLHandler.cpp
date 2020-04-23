//
// Created by AdisAlagic on 16.04.2020.
//

#include <iostream>
#include "XMLHandler.h"

XMLHandler::XMLHandler(const char *name, vector<Department> &departments) {
    this->name = name;
    this->departments = &departments;
    readXML(departments);
}

void XMLHandler::readXML(vector<Department> &d) {
    result = document.load_file(name.c_str());
    if (!result) {
        cout << "Unable to load xml file";
        exit(0);
    }

    d.clear();
    for (pugi::xml_node tool: document.child("departments")) {
        Department department(tool.attribute("name").as_string());
        for (pugi::xml_node node: tool.child("employments")) {
            department.add_employment(
                    node.child_value("name"),
                    node.child_value("surname"),
                    node.child_value("middleName"),
                    node.child_value("function"),
                    atoi(node.child_value("salary"))
            );
        }
        d.push_back(department);
    }
}

void XMLHandler::addDepartment(Department &department) {
    save(UNDO, true);
    auto node = document.child("departments").append_child("department");
    if (!node.append_attribute("name").set_value(department.get_name().c_str())) {
        cout << "DEBUG: ERROR ADDING ATR\n";
    }
    auto emps = node.append_child("employments");
    for (int i = 0; i < department.get_amount_of_employments(); i++) {
        auto empss = emps.append_child("employment");
        Employment employment = department.get_employment(i);
        empss.append_child("surname").set_value(employment.get_surname().c_str());
        empss.append_child("name").set_value(employment.get_name().c_str());
        empss.append_child("middleName").set_value(employment.get_middle_name().c_str());
        empss.append_child("function").set_value(employment.get_function().c_str());
        char number[50];
        sprintf(number, "%d", employment.get_salary());
        empss.append_child("salary").set_value(number);
    }
    auto success = document.save_file("tst.xml");
    readXML(*departments);
    printResult(success);
    save(UNDO, true);
}

void XMLHandler::removeDepartment(const int &index) {
    if (index >= departments->size()) {
        cout << "Not found\n";
        return;
    }
    save(UNDO, true);
    Department department = departments->at(index);
    auto node = findDepartment(department);
    if (node.attribute("name").value() == department.get_name()) {
        printResult(node.parent().remove_child(node));
        document.save_file(name.c_str());
        readXML(*departments);
    }
}

void XMLHandler::editDepartment(const int &index, const char *newName) {
    if (index >= departments->size()) {
        cout << "Not found\n";
        return;
    }
    save(UNDO, true);
    Department department = departments->at(index);
    auto node = findDepartment(department);
    printResult(node.attribute("name").set_value(newName));
    document.save_file(name.c_str());
    readXML(*departments);
}

void XMLHandler::addEmployment(const int &index, Employment &employment) {
    save(UNDO, true);
    Department department = departments->at(index);
    auto node = findDepartment(department);
    auto emp = node.child("employments").append_child("employment");
    emp.append_child("surname").append_child(pugi::node_pcdata).set_value(employment.get_surname().c_str());
    emp.append_child("name").append_child(pugi::node_pcdata).set_value(employment.get_name().c_str());
    emp.append_child("middleName").append_child(pugi::node_pcdata).set_value(
            employment.get_middle_name().c_str());
    emp.append_child("function").append_child(pugi::node_pcdata).set_value(employment.get_function().c_str());
    char sal[50];
    sprintf(sal, "%d", employment.get_salary());
    emp.append_child("salary").append_child(pugi::node_pcdata).set_value(sal);
    document.save_file(name.c_str());
    readXML(*departments);
}

/**
 *
 * @param index Department index
 * @param empName Employment holder
 * @param type Type of Redacting
 * @param newItem New name
 */
void XMLHandler::editEmployment(const int &index, Employment &empName, Type type, const char *newItem) {
    Department department = departments->at(index);
    save(UNDO, true);
    pugi::xml_node emp;
    auto node = findDepartment(department);
    for (auto second: node.child("employments")) {
        if (empName.get_surname() == second.child_value("surname") &&
            empName.get_name() == second.child_value("name") &&
            empName.get_middle_name() == second.child_value("middleName") &&
            empName.get_function() == second.child_value("function")) {
            emp = second;
        }
    }
    switch (type) {
        case NAME:
            printResult(emp.remove_child("name") &&
                        emp.append_child("name").append_child(pugi::node_pcdata).set_value(newItem));
            break;
        case SURNAME:
            printResult(emp.remove_child("surname") &&
                        emp.append_child("surname").append_child(pugi::node_pcdata).set_value(newItem));
            break;
        case MIDDLE_NAME:
            printResult(emp.remove_child("middleName") &&
                        emp.append_child("middleName").append_child(pugi::node_pcdata).set_value(newItem));
            break;
        case FUNCTION:
            printResult(emp.remove_child("function") &&
                        emp.append_child("function").append_child(pugi::node_pcdata).set_value(newItem));
            break;
        case SALARY:
            printResult(emp.remove_child("salary") &&
                        emp.append_child("salary").append_child(pugi::node_pcdata).set_value(newItem));
            break;
    }
    document.save_file(name.c_str());
    readXML(*departments);

}

void XMLHandler::printResult(const bool &operation) {
    if (operation) {
        cout << "Success!\n";
    } else {
        cout << "Failed!\n";
    }
}

void XMLHandler::removeEmployment(const int &depIndex, const int &empIndex) {
    if (depIndex >= departments->size() || empIndex >= departments->at(depIndex).get_amount_of_employments()) {
        cout << "Not found\n";
        return;
    }
    save(UNDO, true);
    auto node = findDepartment(departments->at(depIndex));
    Employment empName = departments->at(depIndex).get_employment(empIndex);
    for (auto emp : node.child("employments")) {
        if (empName.get_surname() == emp.child_value("surname") &&
            empName.get_name() == emp.child_value("name") &&
            empName.get_middle_name() == emp.child_value("middleName") &&
            empName.get_function() == emp.child_value("function")) {
            printResult(emp.parent().remove_child(emp));
            document.save_file(name.c_str());
            readXML(*departments);
        }
    }
}

void XMLHandler::undoChange() {
    if (undo.empty()) {
        cout << "No change\n";
        return;
    }
    save(REDO, false);
    document.reset();
    ofstream file(name);
    if (file.is_open()) {
        file << undo.top();

        undo.pop();
    }
    file.close();
    printResult(true);
    readXML(*departments);
}

void XMLHandler::save(HistoryType type, bool deleteRedo) {
    ifstream file(name);
    string data, line;
    if (file.is_open()) {
        while (getline(file, line)) {
            data += line + "\n";
        }
    }
    file.close();
    if (type == UNDO) {
        undo.push(data);
        if (deleteRedo) {
            redo = stack<string>();
        }
    } else if (type == REDO) {
        redo.push(data);
    }

}

void XMLHandler::redoChange() {
    if (redo.empty()) {
        cout << "Nothing to restore\n";
        return;
    }
    save(UNDO, false);
    document.reset();
    ofstream file(name);
    if (file.is_open()) {
        file << redo.top();
        redo.pop();
    }
    file.close();
    printResult(true);
    readXML(*departments);
}

pugi::xml_node XMLHandler::findDepartment(Department &department) {
    for (auto node : document.child("departments")) {
        if (node.attribute("name").value() == department.get_name()) {
            return node;
        }
    }
    throw exception();
}


