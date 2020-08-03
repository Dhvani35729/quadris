#include "hintblock.h"

// Copy constructor
// Call parent block constructor
HintBlock::HintBlock(const Block &b) : Block(b)
{
    // Update the cells to be question marks
    for (int i = 0; i < this->mHeight_; i++)
    {
        for (int j = 0; j < this->mWidth_; j++)
        {
            if (this->matrix_[i][j] != ' ')
            {
                this->matrix_[i][j] = '?';
            }
        }
    }
};

HintBlock::~HintBlock(){};