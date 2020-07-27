#include "controller.h"
#include "model.h"
#include "interpreter.h"

#include <iostream>
#include <string>
#include <vector>

Controller::Controller(Model *m) : model_(m)
{
    std::cout << "Controller born" << std::endl;
    inter_ = new Interpreter();
}

Controller::~Controller()
{
    std::cout << "Controller died" << std::endl;
    delete inter_;
}

void Controller::getCommand()
{
    std::cout << "Controller: Getting command from user" << std::endl;
    std::string command;
    std::vector<Command> commands = inter_->processCommand(command);
    std::cout << "Controller: Received commands from Interpreter, length: " << commands.size() << std::endl;
}