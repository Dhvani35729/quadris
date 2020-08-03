#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <memory>

#include "controller.h"
#include "model.h"
#include "interpreter.h"
#include "level.h"

#include "fileexception.h"

using namespace std;

// constructor
Controller::Controller(shared_ptr<Model> model)
{
    this->model_ = model;
    this->inter_ = make_unique<Interpreter>();
}

// destructor
Controller::~Controller() {}

// Get the next command
void Controller::getCommand()
{
    // Keep asking for a command if the user enters a bad command
    // Otherwise, run the corresponding model method
    bool keepAsking = true;
    do
    {
        cout << ">";

        // Input into the interpreter
        try
        {
            cin >> *inter_;
        }
        catch (FileNotFoundException e)
        {
            throw move(e);
        }

        // Get the commands interpreted by the interpreter
        vector<pair<Command, int>> commands = inter_->getCommands();

        if (!commands.empty())
        {
            keepAsking = false;

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
                    while (!model_->isGameOver())
                    {
                        model_->playAI();
                    }
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
                    model_->moveBlock((Direction)cmd, multiplier);
                }
                else if (cmd == RANDOM)
                {
                    model_->randomOn();
                }
                else if (cmd == NO_RANDOM_FILE)
                {
                    string seqFileName;
                    cin >> seqFileName;
                    try
                    {
                        model_->randomOff(seqFileName);
                    }
                    catch (FileNotFoundException e)
                    {
                        throw move(e);
                    }
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
                else if (cmd == I ||
                         cmd == J ||
                         cmd == L ||
                         cmd == S ||
                         cmd == Z ||
                         cmd == O ||
                         cmd == T)
                {
                    string blkTypes = "IJLSZOT";
                    // Block type starts at index 0
                    BlockType blkType = (BlockType)(cmd - I);
                    model_->changeCurrentBlock(blkType);
                }
                else if (cmd == BAD_COMMAND)
                {
                    cout << "Invalid command!" << endl;
                    keepAsking = true;
                }
            }
        }
        else
        {
            keepAsking = true;
        }

    } while (keepAsking);
}