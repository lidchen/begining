#include "Todolists.h"
#include "Action.h"

std::string filename = "Todolist.txt";

int main()
{
    Todolists todolist;
    todolist.ReadFromFile();
    todolist.UserInterface();
}
