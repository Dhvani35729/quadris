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
    this->inter_ = std::make_unique<Interpreter>();
}

Controller::~Controller()
{
    std::cout << "Controller died" << std::endl;
}

bool Controller::getCommand()
{
    // std::cout << "Controller: Getting command from user" << std::endl;
    // std::cout << std::endl;
    bool keepAsking = true;
    do
    {
        std::cout << ">";
        std::cin >> *inter_;
        std::vector<std::pair<Command, int>> commands = inter_->getCommands();

        if (!commands.empty())
        {
            keepAsking = false;

            // std::cout << "Controller: Received commands from Interpreter, length: " << commands.size() << std::endl;
            for (int i = 0; i < commands.size(); i++)
            {
                Command cmd = commands[i].first;
                int multiplier = commands[i].second;
                if (cmd == EXIT)
                {
                    return true;
                }

                if (cmd == BOT_MODE)
                {
                    // while (true)
                    // {
                    while (!model_->checkGameOver())
                    {
                        model_->playAI();
                    }
                    // model_->resetGame();
                    // }
                }
                else
                {
                    // TODO: Should go away for bad command
                    model_->hideHint();
                }

                if (cmd == DROP)
                {
                    model_->dropBlock(multiplier);
                }
                else if (cmd == CLOCKWISE || cmd == COUNTERCLOCKWISE)
                {
                    model_->rotateBlock(cmd, multiplier);
                }
                else if (cmd == LEFT || cmd == RIGHT || cmd == DOWN)
                {
                    model_->moveBlock(cmd, multiplier);
                }
                else if (cmd == RANDOM || cmd == NO_RANDOM_FILE)
                {
                    model_->toggleRandom(cmd);
                }
                else if (cmd == RESTART)
                {
                    model_->resetGame();
                }
                else if (cmd == LEVEL_UP)
                {
                    model_->levelUp(multiplier);
                }
                else if (cmd == LEVEL_DOWN)
                {
                    model_->levelDown(multiplier);
                }
                else if (cmd == HINT)
                {
                    model_->showHint();
                }
                else if (cmd == I || cmd == J || cmd == L || cmd == S || cmd == Z || cmd == O || cmd == T)
                {
                    BlockType blkType = BAD_BLK;
                    // TODO: Should be a map or something better
                    if (cmd == I)
                    {
                        blkType = I_BLK;
                    }
                    else if (cmd == J)
                    {
                        blkType = J_BLK;
                    }
                    else if (cmd == L)
                    {
                        blkType = L_BLK;
                    }
                    else if (cmd == S)
                    {
                        blkType = S_BLK;
                    }
                    else if (cmd == Z)
                    {
                        blkType = Z_BLK;
                    }
                    else if (cmd == O)
                    {
                        blkType = O_BLK;
                    }
                    else if (cmd == T)
                    {
                        blkType = T_BLK;
                    }

                    if (blkType != BAD_BLK)
                    {
                        model_->changeCurrentBlock(blkType);
                    }
                }
                else if (cmd == BAD_COMMAND)
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

    return false;
}