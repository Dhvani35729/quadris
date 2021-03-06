#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <utility>
#include <string>

#include "../support/constants.h"

// Interpreter
class Interpreter
{
public:
    // default constructor
    Interpreter();

    // destructor
    ~Interpreter();

    // Get the list of commands generated by the Interpreter
    // Each command also has a multiplier
    std::vector<std::pair<Command, int>> getCommands();

    // Process input and generate commands
    friend std::istream &operator>>(std::istream &in, Interpreter &intp);

private:
    // Helper methods

    // Add a command and its multiplier to the list of commands
    void addCommand(Command command, int multiplier);

    // Takes in a string and returns the associated command
    // Performs auto complete
    Command completer(std::string rawCommand);

    // Renames the command
    bool renameCommad(std::string from, std::string to);

    // Parses the raw command from the stream
    // Separated from instream operator as it is recursive
    void parseRaw(std::istream &in, std::string rawCommand);

    // List of commands and their corresponding multiplier
    std::vector<std::pair<Command, int>> commands_;

    // List of command names mapping to Command enum
    std::vector<std::string> commandNames_;
};

#endif
