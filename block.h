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
    T_BLK,
    BAD_BLK,
};

// Block
class Block
{
public:
    Block(BlockType, std::pair<int, int>, int);
    virtual ~Block();
    std::vector<std::vector<char>> getCells();
    std::pair<int, int> getPos();
    bool moveBlock(Command);
    bool rotateBlock(Command);
    int getBoxWidth();
    int getBoxHeight();
    void dropBlock(int);

private:
    int level_;
    BlockType type_;
    int aliveFor_;
    std::vector<std::vector<char>> matrix_;
    int mWidth_;
    int mHeight_;
    std::pair<int, int> coords_;
};

class HeavyBlock : public Block
{
public:
    HeavyBlock();
};

#endif