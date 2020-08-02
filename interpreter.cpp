
#include "interpreter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>

Interpreter::Interpreter()
{
    std::cout << "Interpreter born" << std::endl;
    this->commandNames_ = {
        "left",
        "right",
        "down",
        "clockwise",
        "counterclockwise",
        "drop",
        "levelup",
        "leveldown",
        "norandom",
        "random",
        "sequence",
        "restart",
        "hint",
        "I",
        "J",
        "L",
        "S",
        "Z",
        "O",
        "T",
        "exit",
        "rename",
        "ai",
    };
}

Interpreter::~Interpreter()
{
    std::cout << "Interpreter died" << std::endl;
}

std::vector<std::pair<Command, int>> Interpreter::getCommands()
{
    return this->commands_;
}

void Interpreter::addCommand(Command c, int m)
{
    this->commands_.push_back(std::make_pair(c, m));
}

void Interpreter::resetCommand()
{
    this->commands_.clear();
}

Command Interpreter::completer(std::string rawCommand)
{
    std::vector<Command> options;
    for (int i = 0; i < this->commandNames_.size(); i++)
    {
        if (this->commandNames_[i].rfind(rawCommand, 0) == 0)
        {
            // commandNames[i] starts with rawCommand
            options.push_back((Command)i);
        }
    }

    if (options.size() == 1)
    {
        return options.front();
    }
    else
    {
        return BAD_COMMAND;
    }
}

bool Interpreter::renameCommad(std::string from, std::string to)
{
    for (int i = 0; i < this->commandNames_.size(); i++)
    {
        if (std::strcmp(this->commandNames_[i].c_str(), from.c_str()) == 0)
        {
            this->commandNames_[i] = to;
            std::cout << "Succesfully renamed command!" << std::endl;
            return true;
        }
    }
    return false;
};

void Interpreter::parseRaw(std::istream &in, std::string cmd)
{
    int multiplier = 1;

    // Check if there is a multiplier prefix
    int cmdStartIndex = 0;
    for (int i = 0; i < cmd.length(); i++)
    {
        if (!std::isdigit(cmd[i]))
        {
            cmdStartIndex = i;
            break;
        }
    }

    // There is a multiplier prefix
    if (cmdStartIndex > 0)
    {
        multiplier = std::stoi(cmd.substr(0, cmdStartIndex));
        // crop out prefix before checking auto completer
        cmd = cmd.substr(cmdStartIndex);
    }

    Command parsedCommand = this->completer(cmd);
    if (parsedCommand == RENAME)
    {
        std::string renameFrom;
        in >> renameFrom;
        std::string renameTo;
        in >> renameTo;
        this->renameCommad(renameFrom, renameTo);
    }
    else if (parsedCommand == SEQUENCE_FILE)
    {
        std::string sequenceFile;
        in >> sequenceFile;

        std::string newRawCommand;
        std::ifstream infile(sequenceFile);
        while (std::getline(infile, newRawCommand))
        {
            std::istringstream iss(newRawCommand);
            // std::cout << "Got command: " << newRawCommand << std::endl;
            if (newRawCommand.find(" ") != -1)
            {
                newRawCommand = newRawCommand.substr(0, newRawCommand.find(" "));
            }
            parseRaw(iss, newRawCommand);
        }
    }
    else
    {
        this->addCommand(parsedCommand, multiplier);
    }
}

std::istream &operator>>(std::istream &in, Interpreter &intp)
{

    std::string cmd;
    in >> cmd;
    intp.resetCommand();

    int multiplier = 1;

    if (in.eof())
    {
        intp.addCommand(EXIT, multiplier);
    }
    else
    {
        intp.parseRaw(in, cmd);
    }

    return in;
}
