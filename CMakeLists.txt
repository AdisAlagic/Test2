cmake_minimum_required(VERSION 3.17)
project(Test2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Test2 main.cpp pugixml.cpp pugixml.hpp pugiconfig.hpp Employment.cpp Employment.h Department.cpp Department.h CommandHandler.cpp CommandHandler.h XMLHandler.cpp XMLHandler.h)