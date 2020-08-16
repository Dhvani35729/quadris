#include <utility>
#include <queue>

#include "heavyblock.h"

using namespace std;

// constructor
// call parent constructor
HeavyBlock::HeavyBlock(BlockType type, pair<int, int> pos, int level, bool playable)
    : Block(type, pos, level, playable)
{
}

// destructor
HeavyBlock::~HeavyBlock(){};

// Override move block
queue<Block> HeavyBlock::moveBlock(Direction c)
{
    // First call parent move block to get the queue of regular blocks
    queue<Block> blocks = Block::moveBlock(c);

    // Then, to the queue, we add the HeavyBlock property
    // (move down automatically by 1)

    // Get the last block from the queue
    Block newBlock = blocks.front();
    pair<int, int> pos = newBlock.getPos();
    // Increment row by 1
    pos.first += 1;
    newBlock.setPos(pos);

    // Add block to the queue of potential blocks
    blocks.push(newBlock);

    return blocks;
};

// Override rotate block
queue<Block> HeavyBlock::rotateBlock(Direction c)
{
    // First call parent move block to get the queue of regular blocks
    queue<Block> blocks = Block::rotateBlock(c);

    // Then, to the queue, we add the HeavyBlock property
    // (move down automatically by 1)

    // Get the last block from the queu
    Block newBlock = blocks.front();
    pair<int, int> pos = newBlock.getPos();
    // Increment row by 1
    pos.first += 1;
    newBlock.setPos(pos);

    // Add block to the queue of potential blocks
    blocks.push(newBlock);

    return blocks;
}