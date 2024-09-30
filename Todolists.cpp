#include "Todolists.h"
#include "Action.h"
#include <fstream>
#include <sstream>
#include <string>


int Todolists::GetSize() { return Todolist.size(); }

void Todolists::ExecuteAction(std::unique_ptr<Action> action)
{
    action->execute();
    // Because of unique_ptr, need to use std::move, and it is faster
    undoStack.emplace_back(std::move(action));
    redoStack.clear();
}

void Todolists::Undo()
{
    if (!undoStack.empty())
    {
        std::unique_ptr<Action> action = std::move(undoStack.back());
        undoStack.pop_back();
        action->undo();
        redoStack.emplace_back(std::move(action));
        std::cout << "Undo Step" << std::endl;
    }else{
        std::cout << "Can't Undo" << std::endl;
    } 
}

void Todolists::Redo()
{
    if (!redoStack.empty())
    {
        std::unique_ptr<Action> action = std::move(redoStack.back());
        redoStack.pop_back();
        action->execute();
        undoStack.emplace_back(std::move(action));
        std::cout << "Redo Step" << std::endl;
    }else{
        std::cout << "Can't Redo" << std::endl;
    }
}

void Todolists::SortByRank()
{
    std::sort(Todolist.begin(), Todolist.end(), [](const Todo& a, const Todo& b)
        { return a.GetRank() > b.GetRank(); });
}


size_t Todolists::GetLongestLength() const
{
    // Initialize is really important. If don't initialize it then the program will break 
    size_t longestLength = 0;
    for (auto todo : Todolist)
    {
        longestLength = std::max(longestLength, todo.GetName().size());
    }
    return longestLength;
}

void Todolists::CleanerList() const
{
    unsigned int count = 1;
    size_t longestLength = GetLongestLength();
    for (Todo todo : Todolist) {
        std::cout << "No." << std::left << std::setw(5) << count 
        << std::setw(longestLength + 5) << todo.GetName() 
        << std::setw(10) << todo.GetStatus() 
        << todo.GetRank() << std::endl;
        count++;
    }
}


void Todolists::SaveToFile()
{
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (file.is_open()) {
        for (const Todo& todo : Todolist) {
            todo.Serialize(file);
        }
        file.close();
        std::cout << "Saved to " << filename << std::endl;
    } else {
        std::cout << "Can't open file" << std::endl;
    }
}

void Todolists::ReadFromFile()
{
    std::ifstream file (filename, std::ios::in);
    std::string line;
    if (file.is_open()){
        while(file.peek() != EOF)
        {
            Todo todo;
            todo.DeSerialize(file);
            Todolist.emplace_back(todo);
        }
        std::cout << "Read From " << filename << std::endl;
        file.close();
    }
}

void Todolists::ClearFile()
{
    std::ofstream file (filename, std::ios::out | std::ios::trunc);
    if (file.is_open()){
        std::cout << ">> " << filename << " Cleared" << std::endl;
    }else{
        std::cout << " >> Can't open file" << std::endl;
    }
}

void Todolists::UserInterface()
{       
    enum Command
    {
        ADD, LIST, DONE, DELETE, EXIT, UNDO, REDO, UNKNOW
    };

    auto hashit = [](const std::string& cmd) -> Command 
    {
        if (cmd == "add") return ADD;
        if (cmd == "list" || cmd == "ls") return LIST;
        if (cmd == "done") return DONE;
        if (cmd == "del") return DELETE;
        if (cmd == "esc"|| cmd == "exit"|| cmd == "quit" || cmd == "q") return EXIT;
        if (cmd == "undo" || cmd == "u") return UNDO;
        if (cmd == "redo" || cmd == "r") return REDO;
        return UNKNOW;
    };

    bool Esc = false;
    std::cout << "Welcome to Todolist" << std::endl;
    while(!Esc)
    {
        std::string input;
        std::string cmd;
        std::cout << "> "; 
        std::getline(std::cin, input);
        std::istringstream iss(input);
        iss >> cmd;
        switch(hashit(cmd))
        {
            case ADD:
            {
                int rank;
                std::string name;
                if (iss >> name >> rank)
                {
                    ExecuteAction(std::make_unique<AddAction>(*this, Todo(name, rank)));
                    break;
                }else{
                    std::cout << "Invalid Input" << std::endl;
                    break;
                }
            }

            case LIST:
                CleanerList();
                break;

            case DONE:
            {
                int index = 0;
                if (iss >> index) {
                    if(index > 0 && index <= static_cast<int>(GetSize())){
                        ExecuteAction(std::make_unique<DoneAction>(*this, index));
                        std::cout << "No." << index << " Marked Done" << std::endl;
                    } else { std::cout << "Invalid Input" << std::endl;}    
                }else{ std::cout << "Invalid Input" << std::endl; }
                break;
                // if (index > 0 || index <= static_cast<int>(todolist.v_todolist.size()))
            }

            case DELETE:
            {
                int index = 0;
                if (iss >> index) {
                    if(index > 0 && index <= static_cast<int>(GetSize()))
                    {
                        ExecuteAction(std::make_unique<DeleteAction>(*this, index));
                        // todolist.Delete(index);
                        std::cout << "No." << index << " Deleted"<< std::endl;
                        break;
                    } else{ std::cout << "Invalid Input" << std::endl; }    
                }else{ std::cout << "Invalid Input" << std::endl; }
                break;
            }

            case UNDO:
                Undo();
                break;

            case REDO:
                Redo();
                break;

            case EXIT:
                Esc = true;
                std::cout << "Saving Program..." << std::endl;
                SaveToFile();
                break;

            case UNKNOW:
                std::cout << "Unknow command" << std::endl;
                break;
        }
    }
}