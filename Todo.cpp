#include "Todo.h"

Todo::Todo() : name("none"), rank(0), done(false) {}
Todo::Todo(std::string n, int r) : name(n), rank(r), done(false) {}

std::string Todo::GetName() const { return name; }
std::string Todo::GetStatus() const { return done ? "[x]" : "[ ]"; }
int Todo::GetRank() const { return rank; }
int Todo::GetStatusNum() const { return done; }

void Todo::Done()  { rank = 0; done = true; }
void Todo::UnDone(int r) { rank = r; done = false;}
void Todo::Modify(const std::string& newName)  { name = newName;   }
void Todo::Modify(const int& newRank)  { rank = newRank; }

void Todo::Serialize(std::ofstream& ofs) {
    ofs << name << "\n" << rank << "\n" << done << "\n"; }

void Todo::DeSerialize(std::ifstream& ifs) {
    std::getline(ifs, name);
    ifs >> rank;
    ifs >> done;
    ifs.ignore();
}
