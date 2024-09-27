#ifndef TODOLISTS_H
#define TODOLISTS_H

#include "Todo.h"
#include <vector>
#include <memory>
#include <string>

extern std::string filename;

// Forward declarations
class Action;
class AddAction;
class DeleteAction;
class DoneAction;
class Todolists

{
    friend class Action;
    friend class AddAction;
    friend class DeleteAction;
    friend class DoneAction;

private:
    std::vector<Todo> Todolist;
    std::vector<std::unique_ptr<Action>> undoStack;
    std::vector<std::unique_ptr<Action>> redoStack;

public:
    int GetSize();
    void ExecuteAction(std::unique_ptr<Action> action);
    void Undo();
    void Redo();
    void SortByRank();
    size_t GetLongestLength() const;
    void CleanerList() const;
    void SaveToFile();
    void ReadFromFile();
    void ClearFile();
    void UserInterface();
};

#endif