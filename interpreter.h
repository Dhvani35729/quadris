#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <utility>
#include <string>

#include "constants.h"

// Controller
class Interpreter
{
public:
    Interpreter();
    ~Interpreter();
    std::vector<std::pair<Command, int>> getCommands();
    void addCommand(Command, int);
    void resetCommand();
    Command completer(std::string);
    bool renameCommad(std::string, std::string);
    void parseRaw(std::istream &in, std::string);

private:
    std::vector<std::pair<Command, int>> commands_;
    std::vector<std::string> commandNames_;
};

std::istream &operator>>(std::istream &, Interpreter &);

#endif
