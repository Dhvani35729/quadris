#include "controller.h"
#include "model.h"

#include <iostream>

Controller::Controller(Model *m) : model_(m)
{
    std::cout << "Controller born" << std::endl;
}

Controller::~Controller()
{
    std::cout << "Controller died" << std::endl;
}