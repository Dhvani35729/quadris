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
    std::pair<int, int> moveBlock(Command);
    Block rotateBlock(Command);
    int getBoxWidth();
    int getBoxHeight();
    int getBlockHeight();
    int getBlockWidth();
    void dropBlock(int);
    void setMatrix(std::vector<std::vector<char>>);
    void setPos(std::pair<int, int>);

private:
    void rotateClockwise();
    void rotateCounterclockwise();
    void calcBlockSize();
    void removeWhitespace();

    int level_;
    BlockType type_;
    int aliveFor_;
    std::vector<std::vector<char>> matrix_;
    int mWidth_;
    int mHeight_;
    int blockHeight_;
    int blockWidth_;
    // top left
    std::pair<int, int> coords_;
};

class HeavyBlock : public Block
{
public:
    HeavyBlock();
};

#endif