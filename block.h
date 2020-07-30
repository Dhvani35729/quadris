#ifndef BLOCK_H
#define BLOCK_H

#include "interpreter.h"

#include <vector>
#include <utility>
#include <queue>

enum BlockType
{
    I_BLK,
    J_BLK,
    L_BLK,
    O_BLK,
    S_BLK,
    Z_BLK,
    T_BLK,
    NUM_BLKS,
    BAD_BLK,
    SPECIAL_BLK
};

// Block
class Block
{
public:
    Block(BlockType, std::pair<int, int>, int, bool);
    virtual ~Block();

    virtual std::queue<Block> moveBlock(Command);
    virtual std::queue<Block> rotateBlock(Command);

    std::vector<std::vector<char>> getCells() const;
    std::pair<int, int> getPos() const;

    bool isPlayable() const;

    int getBoxWidth() const;
    int getBoxHeight() const;

    int getBlockHeight() const;
    int getBlockWidth() const;

    int getLevelGen() const;

    void setMatrix(std::vector<std::vector<char>>, int mHeight, int mWidth);
    void setPos(std::pair<int, int>);

    bool removeLine(int h);

protected:
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

    int numCells_;

    // top left corner
    std::pair<int, int> coords_;
    int level_;

    bool playable_;
};

std::ostream &operator<<(std::ostream &sout, const Block &b);

class HeavyBlock : public Block
{
public:
    HeavyBlock(BlockType, std::pair<int, int>, int, bool);
    ~HeavyBlock();
    std::queue<Block> moveBlock(Command) override;
    std::queue<Block> rotateBlock(Command) override;
};

class StarBlock : public Block
{
public:
    StarBlock(std::pair<int, int>, int, bool);
    ~StarBlock();
};

#endif