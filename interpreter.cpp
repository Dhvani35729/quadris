
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

std::istream &operator>>(std::istream &in, Interpreter &i)
{

    std::string cmd;
    in >> cmd;

    if (cmd == "LEFT")
    {
        i.addCommand(LEFT);
    }
    else if (cmd == "RIGHT")
    {
        i.addCommand(RIGHT);
    }
    else if (cmd == "DOWN")
    {
        i.addCommand(DOWN);
    }

    assert(!in.fail());

    return in;
}
