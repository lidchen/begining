cmake_minimum_required(VERSION 3.5.0)
project(Todolist VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Todolist 
Todolists.cpp
Action.cpp
Todo.cpp
main.cpp)

