
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
    else if (cmd == "clockwise")
    {
        i.addCommand(CLOCKWISE);
    }
    else if (cmd == "counterclockwise")
    {
        i.addCommand(COUNTERCLOCKWISE);
    }
    else if (cmd == "levelup")
    {
        i.addCommand(LEVEL_UP);
    }
    else if (cmd == "leveldown")
    {
        i.addCommand(LEVEL_DOWN);
    }
    else if (cmd == "restart")
    {
        i.addCommand(RESTART);
    }
    else if (cmd == "I")
    {
        i.addCommand(I);
    }
    else if (cmd == "J")
    {
        i.addCommand(J);
    }
    else if (cmd == "L")
    {
        i.addCommand(L);
    }
    else if (cmd == "S")
    {
        i.addCommand(S);
    }
    else if (cmd == "Z")
    {
        i.addCommand(Z);
    }
    else if (cmd == "O")
    {
        i.addCommand(O);
    }
    else if (cmd == "T")
    {
        i.addCommand(T);
    }
    else
    {
        i.addCommand(BAD_COMMAND);
    }

    assert(!in.fail());

    return in;
}
