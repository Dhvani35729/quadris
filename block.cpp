#include "block.h"

#include <iostream>
#include <vector>
#include <utility>

Block::Block(BlockType t, std::pair<int, int> pos, int level)
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
    if (this->type_ == T_BLK)
    {
        cells.resize(3, std::vector<char>(3, ' '));
        cells[0][0] = 'T';
        cells[0][1] = 'T';
        cells[0][2] = 'T';
        cells[1][1] = 'T';
    }
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