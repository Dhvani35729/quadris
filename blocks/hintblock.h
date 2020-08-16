
#ifndef HINT_BLOCK_H
#define HINT_BLOCK_H

#include "block.h"

// HintBlock
// Inherits from Block
class HintBlock : public Block
{
public:
    // Copy constructor
    HintBlock(const Block &);

    // destructor
    ~HintBlock();
};

#endif