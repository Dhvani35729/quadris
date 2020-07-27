
#include "interpreter.h"

#include <iostream>
#include <string>

Interpreter::Interpreter()
{
    std::cout << "Interpreter born" << std::endl;
}

Interpreter::~Interpreter()
{
    std::cout << "Interpreter died" << std::endl;
}

std::vector<Command> Interpreter::processCommand(std::string rawCommand)
{
    std::vector<Command> commands;
    std::cout << "Processing raw command" << std::endl;
    return commands;
}