
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
    else if (cmd == "random") //Relevant only during levels 3 and 4, this command restores randomness in these levels.
    {
        i.addCommand(RANDOM);
    }
        else if (cmd == "norandom file") //Relevant only during levels 3 and 4, this command restores randomness in these levels.
    {
        i.addCommand(NO_RANDOM_FILE);
    }
    else
    {
        i.addCommand(BAD_COMMAND);
    }

    assert(!in.fail());

    return in;
}
