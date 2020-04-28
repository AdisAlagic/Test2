#include <iostream>
#include "pugixml.hpp"
#include <vector>
#include "Department.h"
#include "CommandHandler.h"

using namespace std;

/*
 * Не особо вижу здесь каких-то паттернов программирования.
 * Только если сделать XMLHandler и CommandHandler синглетонами,
 * Но я не особо люблю этот паттерн.
 */
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

