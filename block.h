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
    Block moveBlock(Command);
    Block rotateBlock(Command);

    int getBoxWidth();
    int getBoxHeight();

    int getBlockHeight();
    int getBlockWidth();

    int getLevelGen();
    bool getScoreCounted();

    void setMatrix(std::vector<std::vector<char>>);
    void setPos(std::pair<int, int>);
    void setScoreCounted(bool);

private:
    void rotateClockwise();
    void rotateCounterclockwise();
    void calcBlockSize();
    void removeWhitespace();

    int level_;
    BlockType type_;
    bool scoredCounted_;

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