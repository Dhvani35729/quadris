#include "controller.h"
#include "model.h"
#include "interpreter.h"

#include <iostream>
#include <string>
#include <vector>
#include <istream>
#include <memory>

#include <chrono>
#include <thread>

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

void Controller::getCommand()
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
                    model_->exitGame();
                }

                if (cmd == BOT_MODE)
                {
                    // while (true)
                    // {
                    while (!model_->checkGameOver())
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        model_->playAI();
                    }
                    // model_->resetGame();
                    // }
                }
                else
                {
                    model_->hideHint();
                }

                if (cmd == DROP)
                {
                    model_->dropBlock(multiplier);
                }
                else if (cmd == CLOCKWISE || cmd == COUNTERCLOCKWISE)
                {
                    model_->rotateBlock((Direction)cmd, multiplier);
                }
                else if (cmd == LEFT || cmd == RIGHT || cmd == DOWN)
                {
                    std::cout << cmd << std::endl;
                    model_->moveBlock((Direction)cmd, multiplier);
                }
                else if (cmd == RANDOM)
                {
                    model_->randomOn();
                }
                else if (cmd == NO_RANDOM_FILE)
                {
                    std::string seqFile;
                    std::cin >> seqFile;
                    model_->randomOff(seqFile);
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
                    std::string blkTypes = "IJLSZOT";
                    // Block type starts at index 0
                    BlockType blkType = (BlockType)(cmd - I);
                    model_->changeCurrentBlock(blkType);
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
}