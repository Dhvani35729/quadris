#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <vector>
#include <utility>
#include <queue>

#include "constants.h"

// Different regular block types + special
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
    // constructor
    Block(BlockType type, std::pair<int, int> pos, int level, bool playable);

    // destructor
    virtual ~Block();

    // Since the Block itself does not know if
    // it's new orientation and position is valid
    // on the board, it returns a Block (or sequence of Blocks)
    // representing where it would be, if it was legal
    virtual std::queue<Block> moveBlock(Direction dir);
    virtual std::queue<Block> rotateBlock(Direction dir);

    // Returns true if the block has been completely cleared
    // Since a remove line will always be a legal move as it's
    // only called once a row is cleared, we do not return a "potential" Block
    // as in move and rotate
    bool removeLine(int h);

    // The following setter methods allow the Block to be updated
    // once Board confirms the block can move to the new spot
    void setType(BlockType type);
    void setMatrix(std::vector<std::vector<char>> mat, int mHeight, int mWidth);
    void setPos(std::pair<int, int> pos);

    // Getters
    std::vector<std::vector<char>> getCells() const;
    int getBoxHeight() const;
    int getBoxWidth() const;

    int getBlockHeight() const;
    int getBlockWidth() const;

    BlockType getBlockType() const;

    std::pair<int, int> getPos() const;
    bool isPlayable() const;
    int getLevelGen() const;

protected:
    // Helper methods for rotation
    void rotateClockwise();
    void rotateCounterclockwise();

    // Helper methods to apply fix ups
    // after rotations or line clears
    void calcBlockSize();
    void removeVertWhitespace();
    void removeHorizWhitespace();

    // Other helper methods
    bool isRowEmpty(int h) const;
    void removeRow(int h);

    bool isColEmpty(int w) const;
    void removeCol(int h);

    // A block has an enclosing box (matrix)
    // which the block may not fully take up
    std::vector<std::vector<char>> matrix_;
    int mWidth_;
    int mHeight_;

    // A block itself has a type, a width,
    // and height, and the number of cells
    // it takes up in the box (matrix)

    BlockType type_;
    int blockHeight_;
    int blockWidth_;

    int numCells_;

    // A block also has:

    // a position on the board
    // Represents the x,y of the top left corner
    // of the block
    std::pair<int, int> coords_;

    // the level it was generated on
    int level_;

    // if the block is playable or not
    // (eg. ' *' blocks are not playable)
    bool playable_;
};

// Output operator to print the Block (i.e. it's cells)
std::ostream &operator<<(std::ostream &sout, const Block &b);

// Returns true if the blocks are the same
bool operator==(const Block &lhs, const Block &rhs);

#endif