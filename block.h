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

    Block moveBlock(Command);
    Block rotateBlock(Command);

    std::vector<std::vector<char>> getCells() const;
    std::pair<int, int> getPos() const;

    int getBoxWidth() const;
    int getBoxHeight() const;

    int getBlockHeight() const;
    int getBlockWidth() const;

    int getLevelGen() const;

    bool getScoreCounted() const;

    void setMatrix(std::vector<std::vector<char>>);
    void setPos(std::pair<int, int>);
    void setScoreCounted(bool);

private:
    void rotateClockwise();
    void rotateCounterclockwise();
    void calcBlockSize();
    void removeWhitespace();

    std::vector<std::vector<char>> matrix_;
    int mWidth_;
    int mHeight_;

    BlockType type_;
    int blockHeight_;
    int blockWidth_;

    // top left corner
    std::pair<int, int> coords_;
    int level_;
    bool scoredCounted_;
};

std::ostream &operator<<(std::ostream &sout, const Block &b);

class HeavyBlock : public Block
{
public:
    HeavyBlock();
};

#endif