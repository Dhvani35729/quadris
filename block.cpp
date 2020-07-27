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

    if (t == T_BLK)
    {
        this->mWidth_ = 3;
        this->mHeight_ = 3;
        matrix_.resize(this->mHeight_, std::vector<char>(this->mWidth_, ' '));
        matrix_[0][0] = 'T';
        matrix_[0][1] = 'T';
        matrix_[0][2] = 'T';
        matrix_[1][1] = 'T';
    }
};

Block::~Block()
{
    std::cout << "Block died" << std::endl;
};

std::vector<std::vector<char>> Block::getCells()
{
    return this->matrix_;
};

int Block::getBoxWidth()
{
    return this->mWidth_;
};

int Block::getBoxHeight()
{
    return this->mHeight_;
};

std::pair<int, int> Block::getPos()
{
    return this->coords_;
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