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

LevelZero::~LevelZero()
{
    std::cout << "LevelZero died" << std::endl;
}

int Level::getLevelNum() const
{
    return this->levelNum_;
}

Block *LevelZero::nextBlock() const
{
    Block *newBlock = new Block(T_BLK, std::make_pair(5, 0), this->levelNum_);
    return newBlock;
}