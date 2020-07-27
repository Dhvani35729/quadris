#include "level.h"

#include <iostream>

Level::Level()
{
    std::cout << "Level born" << std::endl;
}

Level::~Level()
{
    std::cout << "Level died" << std::endl;
}

Block *LevelZero::nextBlock() const
{
}