#ifndef TODO_H
#define TODO_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <memory>


class Todo
{
private:
    std::string name;
    int rank;
    bool done;
public:
    Todo();
    Todo(std::string n, int r);
    std::string GetName() const;
    std::string GetStatus() const;
    int GetRank() const;
    int GetStatusNum() const;
    void Modify(const std::string& newName);
    void Modify(const int& newRank);
    void Serialize(std::ofstream& ofs) const;
    void DeSerialize(std::ifstream& ifs);
    void Done();
    void UnDone(int r);
};

#endif