

#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include "block.h"

#include "interpreter.h"

#include <vector>
#include <memory>

// Board
class Board
{
public:
    Board(int, int);
    ~Board();

    bool addBlock(std::shared_ptr<Block>);

    bool moveCurrentBlock(Command);
    bool rotateCurrentBlock(Command);

    // Returns the number of rows dropped
    // and a list of blocks cleared
    std::pair<int, std::vector<Block>> dropCurrentBlock();

    bool changeCurrentBlock(BlockType);

    std::vector<std::vector<char>> getBoard() const;

    void resetBoard();
    void showHint();

    int getHeight() const;
    int getWidth() const;

private:
    void setCell(int, int, char);

    void updateCells(std::shared_ptr<Block>);
    void clearCells(std::shared_ptr<Block>);

    bool canPlace(Block &);

    bool isOccupied(int, int);
    bool isLineFull(int);
    bool isLineEmpty(int);
    int calcPenalty();

    std::vector<Block> removeLine(int h);

    int width_;
    int height_;

    std::vector<std::vector<std::shared_ptr<Cell>>> board_;

    std::vector<std::shared_ptr<Block>> activeBlocks_;
    std::vector<std::shared_ptr<Block>> clearedBlocks_;

    std::shared_ptr<Block> currBlock_;
};

std::ostream &operator<<(std::ostream &sout, const Board &b);

#endif