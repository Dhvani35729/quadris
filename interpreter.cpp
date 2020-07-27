
#include "interpreter.h"

#include <iostream>
#include <string>
#include <cassert>

Interpreter::Interpreter()
{
    std::cout << "Interpreter born" << std::endl;
}

Interpreter::~Interpreter()
{
    std::cout << "Interpreter died" << std::endl;
}

std::vector<Command> Interpreter::getCommands()
{
    return this->commands_;
}

void Interpreter::addCommand(Command c)
{
    this->commands_.push_back(c);
}

void Interpreter::resetCommand()
{
    this->commands_.clear();
}

std::istream &operator>>(std::istream &in, Interpreter &i)
{

    std::string cmd;
    in >> cmd;
    i.resetCommand();

    if (cmd == "left")
    {
        i.addCommand(LEFT);
    }
    else if (cmd == "right")
    {
        i.addCommand(RIGHT);
    }
    else if (cmd == "down")
    {
        i.addCommand(DOWN);
    }
    else if (cmd == "drop")
    {
        i.addCommand(DROP);
    }

    assert(!in.fail());

    return in;
}
