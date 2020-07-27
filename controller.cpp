#include "controller.h"
#include "model.h"
#include "interpreter.h"

#include <iostream>
#include <string>
#include <vector>
#include <istream>

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
    std::cout << std::endl;
    bool keepAsking = true;
    do
    {
        std::cout << ">";
        std::cin >> *inter_;
        std::vector<Command> commands = inter_->getCommands();

        if (!commands.empty())
        {
            keepAsking = false;
            std::cout
                << "Controller: Received commands from Interpreter, length: " << commands.size() << std::endl;
            for (int i = 0; i < commands.size(); i++)
            {
                if (commands[i] == DROP)
                {
                    model_->dropBlock();
                }
            }
        }
        else
        {
            keepAsking = true;
        }
    } while (keepAsking);
}