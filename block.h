#ifndef BLOCK_H
#define BLOCK_H

#include "interpreter.h"

#include <vector>
#include <utility>

enum BlockType
{
    I_BLK,
    J_BLK,
    L_BLK,
    O_BLK,
    S_BLK,
    Z_BLK,
    T_BLK
};

// Block
class Block
{
public:
    Block(BlockType, std::pair<int, int>, int);
    virtual ~Block();
    std::vector<std::vector<char>> getCells();
    std::pair<int, int> getBox();
    bool moveBlock(Command);
    bool rotateBlock(Command);
    void dropBlock();

private:
    int level_;
    BlockType type_;
    int aliveFor_;
    std::pair<int, int> coords_;
};

class HeavyBlock : public Block
{
public:
    HeavyBlock();
};

#endif