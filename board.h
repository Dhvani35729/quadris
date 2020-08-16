#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>

#include "blocks/block.h"
#include "cell.h"

#include "constants.h"

// Board
class Board
{
public:
    // constructor
    Board(int height, int width);

    // destructor
    ~Board();

    // Adds a block to the board
    // Current block becomes this new block
    // Returns true if the block could be added (legal move)
    bool addBlock(std::shared_ptr<Block> block);

    // Move current block
    // Returns true if the block could be moved (legal move)
    bool moveCurrentBlock(Direction dir);

    // Rotate current block
    // Returns true if the block could be rotated (legal move)
    bool rotateCurrentBlock(Direction dir);

    // Drops the current block
    // Returns the number of lines cleared
    // and a list of blocks cleared
    std::pair<int, std::vector<Block>> dropCurrentBlock();

    // Changes the current block's type
    // Returns true if the block could be changed (legal move)
    bool changeCurrentBlock(BlockType type);

    // Resets the board by clearing the grid of cells and blocks
    void resetBoard();

    // Show the hint block on the board
    void showHint();

    // Remove the hint block from the board
    void hideHint();

    // Play the hint block as a turn
    void playHint();

    // Getters
    std::vector<std::vector<char>> getBoard() const;

    int getHeight() const;
    int getWidth() const;

private:
    // Helper methods

    // Update a cell in the grid of cells
    void setCell(int row, int col, char symbol);

    // Returns true if the given block can be placed
    // on the board (legal move)
    bool canPlace(Block &newBlock);

    // Adds the given block to the grid of cells (i.e. the board)
    void updateCells(std::shared_ptr<Block> block);

    // Removes the given block from the grid of cells (i.e. the board)
    void clearCells(std::shared_ptr<Block> block);

    // Returns true if the row is full
    bool isRowFull(int h);

    // Removes the given h from the grid of cells (i.e. the board)
    // and returns the blocks that were cleared by doing that
    std::vector<Block> removeLine(int h);

    // Calculates the penalty for the current grid of cells
    int calcPenalty();

    // The board is made up of a grid of cells
    std::vector<std::vector<std::shared_ptr<Cell>>> board_;

    // The grid has a size: height and width
    int height_;
    int width_;

    // The board also keeps track of the active blocks on the board
    // and the cleared blocks that were previously on this board
    std::vector<std::shared_ptr<Block>> activeBlocks_;
    std::vector<std::shared_ptr<Block>> clearedBlocks_;

    // 2 special blocks are also tracked:
    // The current block, on which all operations
    // (such as move, rotate, drop) are done
    std::shared_ptr<Block> currBlock_;

    // and the hint block, as it is a special block
    std::shared_ptr<Block> hintBlock_;
};

// Output operator to print the Board
// (i.e. the grid of cells containing the blocks)
std::ostream &operator<<(std::ostream &sout, const Board &b);

#endif