
#include "interpreter.h"

#include <iostream>
#include <string>
#include <vector>

Interpreter::Interpreter()
{
    std::cout << "Interpreter born" << std::endl;
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

Command completer(std::string rawCommand)
{
    std::vector<std::string> commandNames = {
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
        "ai",
    };
    std::vector<Command> options;
    for (int i = 0; i < commandNames.size(); i++)
    {
        if (commandNames[i].rfind(rawCommand, 0) == 0)
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

        // std::cout << "Got multiplier: " << multiplier << std::endl;

        Command parsedCommand = completer(cmd);
        if (parsedCommand == BAD_COMMAND)
        {
            intp.addCommand(BAD_COMMAND, multiplier);
        }
        else
        {
            // TODO: Check if multiplier is valid
            for (int i = 0; i < multiplier; i++)
            {
                intp.addCommand(parsedCommand, multiplier);
            }
        }
    }

    return in;
}
