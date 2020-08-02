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
    S_BLK,
    Z_BLK,
    O_BLK,
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

    virtual std::queue<Block> moveBlock(Direction);
    virtual std::queue<Block> rotateBlock(Direction);

    std::vector<std::vector<char>> getCells() const;
    std::pair<int, int> getPos() const;

    bool isPlayable() const;

    int getBoxWidth() const;
    int getBoxHeight() const;

    int getBlockHeight() const;
    int getBlockWidth() const;

    int getLevelGen() const;
    BlockType getBlockType() const;

    void setType(BlockType);
    void setMatrix(std::vector<std::vector<char>>, int mHeight, int mWidth);
    void setPos(std::pair<int, int>);

    bool removeLine(int h);

protected:
    void rotateClockwise();
    void rotateCounterclockwise();
    void calcBlockSize();
    void removeVertWhitespace();
    void removeHorizWhitespace();

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
bool operator==(const Block &lhs, const Block &rhs);

class HeavyBlock : public Block
{
public:
    HeavyBlock(BlockType, std::pair<int, int>, int, bool);
    ~HeavyBlock();
    std::queue<Block> moveBlock(Direction) override;
    std::queue<Block> rotateBlock(Direction) override;
};

class StarBlock : public Block
{
public:
    StarBlock(std::pair<int, int>, int, bool);
    ~StarBlock();
};

class HintBlock : public Block
{
public:
    HintBlock(const Block &);
};

#endif