#include "Action.h"
#include "Todolists.h"

AddAction::AddAction(Todolists& todolists, const Todo& todo) : todo(todo), todolists(todolists) {
    std::cout << "AddAction Created" << std::endl;
}

AddAction::~AddAction() { std::cout << "AddAction Deleted" << std::endl; }

void AddAction::execute()
{
    std::vector<Todo>::iterator it = std::lower_bound(todolists.Todolist.begin(), todolists.Todolist.end(), todo, 
        [](const Todo& a, const Todo& b){ 
            return a.GetRank() > b.GetRank(); });
    insertPos = std::distance(todolists.Todolist.begin(),it);

    todolists.Todolist.insert(it, todo);
}

void AddAction::undo()
{
    todolists.Todolist.erase(todolists.Todolist.begin() + insertPos);
}

DeleteAction::DeleteAction(Todolists& todolists, int index) : todolists(todolists), index(index) {
    std::cout << "DeleteAction Created" << std::endl;
    deletedTodo = todolists.Todolist[index - 1];
}

DeleteAction::~DeleteAction() { std::cout << "DeletedAction Deleted" << std::endl; }

void DeleteAction::execute() {
    todolists.Todolist.erase(todolists.Todolist.begin() + index - 1);
}

void DeleteAction::undo() {
    todolists.Todolist.insert(todolists.Todolist.begin() + index - 1 , deletedTodo);
}

DoneAction::DoneAction(Todolists& todolists, int index) : todolists(todolists), index(index) {
    deletedRank = todolists.Todolist[index - 1].GetRank();
} 

void DoneAction::execute() {
    todolists.Todolist[index - 1].Done();
    todolists.Todolist.push_back(todolists.Todolist[index - 1]);
    todolists.Todolist.erase(todolists.Todolist.begin() + index - 1);
    // std::swap(todolists.Todolist[index - 1], todolists.Todolist.back()); 
}

void DoneAction::undo() {
    todolists.Todolist.back().UnDone(deletedRank);
    auto it = todolists.Todolist.begin() + index - 1;
    std::rotate(it, todolists.Todolist.end() - 1, todolists.Todolist.end());
}