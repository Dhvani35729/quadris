#include "block.h"

#include <iostream>
#include <vector>
#include <utility>

Block::Block(Type t, std::pair<int, int> pos, int level)
{
    this->type_ = t;
    this->coords_ = pos;
    this->level_ = level;
    aliveFor_ = 0;
    std::cout << "Block born" << std::endl;
};

Block::~Block()
{
    std::cout << "Block died" << std::endl;
};

std::vector<std::vector<char>> Block::getCells()
{
    std::vector<std::vector<char>> cells;
    return cells;
};

std::pair<int, int> Block::getBox()
{
    return coords_;
};

bool Block::moveBlock(Command)
{
    return true;
};
bool Block::rotateBlock(Command)
{
    return true;
};

void Block::dropBlock(){

};