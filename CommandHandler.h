//
// Created by AdisAlagic on 15.04.2020.
//

#ifndef TEST2_COMMANDHANDLER_H
#define TEST2_COMMANDHANDLER_H

#include <string>
#include <vector>
#include <map>
#include "Department.h"
#include "XMLHandler.h"


using namespace std;

enum State {
    NONE_SELECTED,
    DEP_SELECTED,
    EMP_SELECTED
};

class CommandHandler {
public:
    CommandHandler(vector<Department> *s, XMLHandler *xmlHandler);

    void parseCommand(const string &comm);

private:
    vector<Department> *s;


    static vector<string> split(const string &basicString, const string &delimiter);

    /**
     * Тоже самое, что и <code>s->at(index)</code>
     * @param index
     * @return
     */
    Department get(int index);
    /**
     * Тоже самое, что и <code>s->at(first).get_employment(second)</code>
     * @param first
     * @param second
     * @return
     */
    Employment get(int first, int second);

    Department depHolder{""};
    Employment empHolder{"", "", "", ""};

    State state;
    XMLHandler *handler;
    int depIndexHolder = -1;
    int empIndexHodler = -1;
//    Использовать мап, чтобы парсить команды. Удобно, но я не понял,
//    как это лучше всего реализовать
//    map<string, void(CommandHandler::*)()> commands;

    //Команды для парса
    void print();

    void exit();

    void clear();

    void get(const string &comm);

    void add(const string &comm);

    void edit(const string &comm);

    void del(const string &comm);

    void undo();

    void redo();

    void average();

    void drop();

    void show();
};


#endif //TEST2_COMMANDHANDLER_H
