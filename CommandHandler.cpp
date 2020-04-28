//
// Created by AdisAlagic on 15.04.2020.
//

#include "CommandHandler.h"
#include <iostream>


using namespace std;

void CommandHandler::parseCommand(const string &comm) {
    if (comm == "print") {
        print();
    } else if (comm == "exit") {
        return;
    } else if (comm == "clear") {
        clear();
    } else if (split(comm, " ").at(0) == "get") {
        get(comm);
    } else if (split(comm, " ").at(0) == "edit") {
        edit(comm);
    } else if (split(comm, " ").at(0) == "add") {
        add(comm);
    } else if (split(comm, " ").at(0) == "del" || split(comm, " ").at(0) == "delete") {
        del(comm);
    } else if (comm == "undo") {
        undo();
    } else if (comm == "redo") {
        redo();
    } else if (comm == "average") {
        average();
    } else if (comm == "drop") {
        drop();
    } else if (comm == "show") {
        show();
    } else {
        cout << "Unable to parse\n";
    }
}

CommandHandler::CommandHandler(vector<Department> *s, XMLHandler *xmlHandler) {
    if (s == nullptr){
        terminate();
    }
    this->s = s;
    state = NONE_SELECTED;
    this->handler = xmlHandler;

}

void CommandHandler::print() {
    for (int i = 0; i < s->size(); ++i) {
        printf("%d. %s\n", i + 1, get(i).get_name().c_str());
        for (int j = 0; j < get(i).get_amount_of_employments(); ++j) {
            Employment employment = get(i).get_employment(j);
            printf("\t%d. %s %s %s - \"%s\" (%i₽)\n", j + 1, employment.get_surname().c_str(),
                   employment.get_name().c_str(),
                   employment.get_middle_name().c_str(), employment.get_function().c_str(), employment.get_salary());
        }
    }
}

vector<string> CommandHandler::split(const string &basicString, const string &delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = basicString.find(delimiter, pos_start)) != string::npos) {
        token = basicString.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(basicString.substr(pos_start));
    return res;
}

Department CommandHandler::get(int index) {
    return s->at(index);
}

Employment CommandHandler::get(int first, int second) {
    return s->at(first).get_employment(second);
}


void CommandHandler::exit() {}

void CommandHandler::clear() {
    //How can I do it better?
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#else
    system("clear");
#endif
}

void CommandHandler::get(const string &comm) {
    vector<string> args = split(comm, " ");
    if (args.size() == 2) {
        int index = atoi(args.at(1).c_str()) - 1;
        if (index >= s->size()) {
            cout << "Not found\n";
            return;
        }
        depHolder = get(index);
        state = DEP_SELECTED;
        depIndexHolder = index;
        printf("Selected: %s\n", depHolder.get_name().c_str());
    } else if (args.size() == 3) {
        int index_one = atoi(args.at(1).c_str()) - 1;
        int index_two = atoi(args.at(2).c_str()) - 1;
        if (index_one >= s->size()) {
            cout << "Not found\n";
            return;
        }
        if (index_two >= s->at(index_one).get_amount_of_employments()) {
            cout << "Not found\n";
            return;
        }
        empHolder = get(index_one, index_two);
        depIndexHolder = index_one;
        empIndexHodler = index_two;
        state = EMP_SELECTED;
        printf("Selected: %s %s %s - \"%s\" (%i₽)\n", empHolder.get_surname().c_str(), empHolder.get_name().c_str(),
               empHolder.get_middle_name().c_str(), empHolder.get_function().c_str(), empHolder.get_salary());
    } else {
        cout << "'get <index>' or 'get <first index> <second index>'\n";
    }
}

void CommandHandler::add(const string &comm) {
    auto args = split(comm, " ");
    if (state == DEP_SELECTED) {
        Employment newEmployment = Employment::getEmpty();
        string item;
        cout << "surname> ";
        getline(cin, item);
        if (item == "!c") { return; }
        newEmployment.setSurname(item);
        cout << "name> ";
        getline(cin, item);
        if (item == "!c") { return; }
        newEmployment.setName(item);
        cout << "middleName> ";
        getline(cin, item);
        if (item == "!c") { return; }
        newEmployment.setMiddleName(item);
        cout << "function> ";
        getline(cin, item);
        if (item == "!c") { return; }
        newEmployment.setFunction(item);
        cout << "salary> ";
        getline(cin, item);
        if (item == "!c") { return; }
        newEmployment.setSalary(atoi(item.c_str()));
        handler->addEmployment(depIndexHolder, newEmployment);
    } else {
        string name;
        for (int i = 1; i < args.size(); i++) {
            if (args.size() == 2) {
                name += args.at(i);
            } else {
                name += args.at(i) + " ";
            }
        }
        depHolder.set_name(name);
        handler->addDepartment(depHolder);
    }
}

void CommandHandler::edit(const string &comm) {
    vector<string> args = split(comm, " ");
    if (state == DEP_SELECTED) {
        if (args.size() < 2) {
            cout << "For Department editing available for \n\tname\n";
            return;
        }
        if (args.at(1) == "name") {
            cout << "name> ";
            string edited;
            getline(cin, edited);
            if (edited == "!c") { return; }
            handler->editDepartment(depIndexHolder, edited.c_str());
        } else {
            cout << "For Department editing available for \n\tname\n";
        }
    } else if (state == EMP_SELECTED) {
        if (args.size() < 2) {
            cout
                    << "For Employment editing available for:\n\tname\n\tsurname\n\tmiddle\n\tfunction\n\tsalary\n";
            return;
        }
        string item = args.at(1);
        string newChar;
        if (item == "name") {
            cout << "name> ";
            getline(cin, newChar);
            if (item == "!c") { return; }
            handler->editEmployment(depIndexHolder, empHolder, NAME, newChar.c_str());
        } else if (item == "surname") {
            cout << "surname> ";
            getline(cin, newChar);
            if (item == "!c") { return; }
            handler->editEmployment(depIndexHolder, empHolder, SURNAME, newChar.c_str());
        } else if (item == "middle" || item == "middlename" || item == "middleName") {
            cout << "middleName> ";
            getline(cin, newChar);
            if (item == "!c") { return; }
            handler->editEmployment(depIndexHolder, empHolder, MIDDLE_NAME, newChar.c_str());
        } else if (item == "function") {
            cout << "function> ";
            getline(cin, newChar);
            if (item == "!c") { return; }
            handler->editEmployment(depIndexHolder, empHolder, FUNCTION, newChar.c_str());
        } else if (item == "salary") {
            cout << "salary> ";
            getline(cin, newChar);
            if (item == "!c") { return; }
            handler->editEmployment(depIndexHolder, empHolder, SALARY, newChar.c_str());
        } else {
            cout
                    << "For Employment editing available for:\n\tname\n\tsurname\n\tmiddle\n\tfunction\n\tsalary";
        }
    }
}

void CommandHandler::del(const string &comm) {
    if (state == DEP_SELECTED) {
        handler->removeDepartment(depIndexHolder);
    } else if (state == EMP_SELECTED) {
        handler->removeEmployment(depIndexHolder, empIndexHodler);
    } else {
        auto args = split(comm, " ");
        handler->removeDepartment(atoi(args.at(1).c_str()) - 1);
    }
    state = NONE_SELECTED;
    depHolder.clear();
}

void CommandHandler::undo() {
    handler->undoChange();
}

void CommandHandler::redo() {
    handler->redoChange();
}

void CommandHandler::average() {
    switch (state) {
        case NONE_SELECTED:
            cout << "Nothing to show\n";
            break;
        case DEP_SELECTED:
            cout << "Average salary is " << depHolder.getAverageSalary() << endl;
            break;
        case EMP_SELECTED:
            printf("Salary of %s %s %s is %d\n", empHolder.get_surname().c_str(), empHolder.get_name().c_str(),
                   empHolder.get_middle_name().c_str(), empHolder.get_salary());
            break;
    }
}

void CommandHandler::drop() {
    switch (state) {
        case NONE_SELECTED:
            break;
        case DEP_SELECTED:
            depHolder.clear();
            depIndexHolder = -1;
            break;
        case EMP_SELECTED:
            depHolder.clear();
            depIndexHolder = -1;
            empHolder.clear();
            empIndexHodler = -1;
            break;
    }
    state = NONE_SELECTED;
    cout << "Dropped";
}

void CommandHandler::show() {
    switch (state) {
        case NONE_SELECTED:
            cout << "Nothing is selected\n";
            break;
        case DEP_SELECTED:
            printf("Selected: %s\n", depHolder.get_name().c_str());
            break;
        case EMP_SELECTED:
            printf("Selected: %s %s %s - \"%s\" (%i₽)\n", empHolder.get_surname().c_str(),
                   empHolder.get_name().c_str(),
                   empHolder.get_middle_name().c_str(), empHolder.get_function().c_str(), empHolder.get_salary());
            break;
    }

}




