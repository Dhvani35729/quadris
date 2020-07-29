

#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include "block.h"

#include "interpreter.h"

#include <vector>

// Board
class Board
{
public:
    Board(int, int);
    ~Board();

    bool addBlock(Block *);

    bool moveCurrentBlock(Command);
    bool rotateCurrentBlock(Command);
    int dropCurrentBlock();

    std::vector<std::vector<char>> getBoard();
    std::vector<Block *> getClearedBlocks();

    void resetBoard();
    void showHint();
    int getHeight() const;
    int getWidth() const;

private:
    void setCell(int, int, char);
    void updateCells(Block *);
    void clearCells(Block *);
    bool canPlace(Block &);

    bool isOccupied(int, int);
    bool isLineFull(int);
    void removeLine(int);

    int width_;
    int height_;
    std::vector<std::vector<Cell *>> board_;

    std::vector<Block *> activeBlocks_;
    std::vector<Block *> clearedBlocks_;

    Block *currBlock_;
};

#endif