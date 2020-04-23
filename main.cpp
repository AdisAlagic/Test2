#include <iostream>
#include "pugixml.hpp"
#include <vector>
#include "Department.h"
#include "CommandHandler.h"
#include "XMLHandler.h"

using namespace std;


int main() {
    vector<Department> departments;
    XMLHandler xmlHandler("tst.xml", departments);
    CommandHandler handler(&departments, &xmlHandler);
    string command;
    do{
        cout << "> ";
        getline(cin, command);
        handler.parseCommand(command);
    }while (command != "exit");
    return 0;
}

