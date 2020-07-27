#include "level.h"

#include <iostream>

Level::Level()
{
    std::cout << "Level born" << std::endl;
    this->levelNum_ = -1;
}

Level::~Level()
{
    std::cout << "Level died" << std::endl;
}

LevelZero::LevelZero()
{
    this->levelNum_ = 0;
}

int Level::getLevelNum() const
{
    return this->levelNum_;
}

Block *LevelZero::nextBlock() const
{
}