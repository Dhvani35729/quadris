#include "controller.h"
#include "model.h"
#include "interpreter.h"

#include <iostream>
#include <string>
#include <vector>
#include <istream>
#include <memory>

Controller::Controller(std::shared_ptr<Model> m)
{
    std::cout << "Controller born" << std::endl;
    this->model_ = m;
    this->inter_ = std::make_shared<Interpreter>();
}

Controller::~Controller()
{
    std::cout << "Controller died" << std::endl;
}

void Controller::getCommand()
{
    // std::cout << "Controller: Getting command from user" << std::endl;
    // std::cout << std::endl;
    bool keepAsking = true;
    do
    {
        std::cout << ">";
        std::cin >> *inter_;
        std::vector<Command> commands = inter_->getCommands();

        if (!commands.empty())
        {
            keepAsking = false;
            // std::cout << "Controller: Received commands from Interpreter, length: " << commands.size() << std::endl;
            for (int i = 0; i < commands.size(); i++)
            {
                if (commands[i] == DROP)
                {
                    model_->dropBlock();
                }
                else if (commands[i] == CLOCKWISE || commands[i] == COUNTERCLOCKWISE)
                {
                    model_->rotateBlock(commands[i]);
                }
                else if (commands[i] == LEFT || commands[i] == RIGHT || commands[i] == DOWN)
                {
                    model_->moveBlock(commands[i]);
                }
                else if (commands[i] == RANDOM || commands[i] == NO_RANDOM_FILE)
                {
                    model_->toggleRandom(commands[i]);
                }
                else if (commands[i] == RESTART)
                {
                    model_->resetGame();
                }
                else if (commands[i] == LEVEL_UP)
                {
                    model_->levelUp();
                }
                else if (commands[i] == LEVEL_DOWN)
                {
                    model_->levelDown();
                }
                else if (commands[i] == I || commands[i] == J || commands[i] == L || commands[i] == S || commands[i] == Z || commands[i] == O || commands[i] == T)
                {
                    BlockType blkType;
                    // TODO: Should be a map or something better
                    if (commands[i] == I)
                    {
                        blkType = I_BLK;
                    }
                    else if (commands[i] == J)
                    {
                        blkType = J_BLK;
                    }
                    else if (commands[i] == L)
                    {
                        blkType = L_BLK;
                    }
                    else if (commands[i] == S)
                    {
                        blkType = S_BLK;
                    }
                    else if (commands[i] == Z)
                    {
                        blkType = Z_BLK;
                    }
                    else if (commands[i] == O)
                    {
                        blkType = O_BLK;
                    }
                    else if (commands[i] == T)
                    {
                        blkType = T_BLK;
                    }
                    model_->changeCurrentBlock(blkType);
                }
                else if (commands[i] == BAD_COMMAND)
                {
                    std::cout << "Invalid command!" << std::endl;
                }
            }
        }
        else
        {
            keepAsking = true;
        }
    } while (keepAsking);
}