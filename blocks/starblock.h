
#ifndef STAR_BLOCK_H
#define STAR_BLOCK_H

#include <utility>

#include "block.h"

// StarBlock
// Inherits from Block
class StarBlock : public Block
{
public:
    // constructor
    StarBlock(std::pair<int, int> pos, int level, bool playable);

    // destructor
    ~StarBlock();
};

#endif