
#ifndef HEAVY_BLOCK_H
#define HEAVY_BLOCK_H

#include <utility>
#include <queue>

#include "block.h"

// HeavyBlock
// Inherits from Block
class HeavyBlock : public Block
{
public:
    // constructor
    HeavyBlock(BlockType type, std::pair<int, int> pos, int level, bool playable);

    // destructor
    ~HeavyBlock();

    // Override move and rotate block
    std::queue<Block> moveBlock(Direction) override;
    std::queue<Block> rotateBlock(Direction) override;
};

#endif