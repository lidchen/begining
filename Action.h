#ifndef ACTION_H
#define ACTION_H

#include "Todo.h"
#include <cstddef> // for size_t

class Todolists;

class Action
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Action() = default;
};

class AddAction : public Action
{
private:
    Todo todo;
    Todolists& todolists;
    size_t insertPos;
public:
    AddAction(Todolists& todolists, const Todo& todo);
    ~AddAction();

    void execute() override;
    void undo() override;
};

class DeleteAction : public Action
{
private:
    int index;
    Todo deletedTodo;
    Todolists& todolists;
public:
    DeleteAction(Todolists& todolists, int index);
    ~DeleteAction();
    void execute() override;
    void undo() override;
};

class DoneAction: public Action
{
private:
    int index;
    Todolists& todolists;
    unsigned int deletedRank;
public:
    DoneAction(Todolists& todolists, int index);
    void execute() override;
    void undo() override;
};

#endif