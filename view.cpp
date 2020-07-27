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
}

void View::run()
{
    std::cout << "Running application" << std::endl;
    this->startGame();

    controller_->getCommand();
}

void View::startGame()
{
    std::cout << "Starting game" << std::endl;
    model_->startGame();
}