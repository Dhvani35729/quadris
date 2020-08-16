#include <utility>

#include "starblock.h"

using namespace std;

// constructor
// call parent constructor
StarBlock::StarBlock(pair<int, int> pos, int level, bool playable)
    : Block(SPECIAL_BLK, pos, level, playable)
{
    // Update the box (matrix) of the block for this special block
    this->mWidth_ = 1;
    this->mHeight_ = 1;

    this->matrix_.resize(this->mHeight_, vector<char>(this->mWidth_, ' '));
    // Update the symbol
    matrix_[0][0] = '*';

    this->blockHeight_ = 1;
    this->blockWidth_ = 1;

    this->numCells_ = 1;
}

StarBlock::~StarBlock(){};