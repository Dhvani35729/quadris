#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"

#include <iostream>

View::View(Controller *c, Model *m) : model_(m), controller_(c)
{
    std::cout << "View born" << std::endl;
}

View::~View()
{
    std::cout << "View died" << std::endl;
}

void View::update()
{
    std::cout << "Updating view" << std::endl;
    // Drawing
}

void View::run()
{
    std::cout << "Running application" << std::endl;
    this->startGame();

    controller_->getCommand();

    this->draw();
}
void View::draw()
{
    // Draw score
    std::cout << "Level:     " << model_->getLevelNum() << std::endl;
    std::cout << "Score:     " << model_->getScore().getScore() << std::endl;
    std::cout << "Hi Score: " << model_->getScore().getHiScore() << std::endl;
    std::cout << "-----------" << std::endl;
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
}

void View::startGame()
{
    std::cout << "Starting game" << std::endl;
    model_->startGame();
}