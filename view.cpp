#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"

#include <iostream>

using namespace std;

View::View(Controller *c, Model *m) : model_(m), controller_(c)
{
    std::cout << "View born" << std::endl;

    // Register view as observer of model
    model_->subscribe(this);
}

View::~View()
{
    std::cout << "View died" << std::endl;
    model_->unsubscribe(this);
}

void View::update()
{
    std::cout << "Updating view" << std::endl;
    // Drawing

    std::cout << "Drawing board \n"
              << std::endl;
    this->draw();
    std::cout << std::endl;
}

void View::run()
{
    std::cout << "Running application" << std::endl;
    this->startGame();

    while (!this->model_->checkGameOver())
    {
        controller_->getCommand();
    }
}
void View::draw()
{
    // Draw score
    std::cout << "Level:     " << model_->getLevelNum() << std::endl;
    std::cout << "Score:     " << model_->getScore() << std::endl;
    std::cout << "Hi Score: " << model_->getHiScore() << std::endl;
    std::cout << "-----------" << std::endl;
    // TODO: Maybe use overloaded << operator
    std::vector<std::vector<char>> board = model_->getBoard();
    int height = model_->getBoardHeight();
    int width = model_->getBoardWidth();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << board[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << "-----------" << std::endl;
    std::cout << "Next:      " << std::endl;
    std::vector<std::vector<char>> nextBlock = model_->getNextBlock();
    for (int i = 0; i < nextBlock.size(); i++)
    {
        string row;
        bool emptyRow = true;
        for (int j = 0; j < nextBlock[i].size(); j++)
        {
            if (nextBlock[i][j] != ' ')
            {
                emptyRow = false;
            }
            row += nextBlock[i][j];
        }
        if (!emptyRow)
        {
            cout << row << endl;
        }
    }
}

void View::startGame()
{
    model_->startGame();
}