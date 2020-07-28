

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
    void addBlock(Block *);
    void setCell(int, int, char);
    bool moveCurrentBlock(Command);
    bool rotateCurrentBlock(Command);
    int dropCurrentBlock();
    std::vector<std::vector<char>> getBoard();
    bool isOccupied(int, int);
    bool isLineFull(int);
    bool removeLine(int);
    void resetBoard();
    void showHint();
    int getHeight() const;
    int getWidth() const;

private:
    void updateCells(Block *);
    void clearCells(Block *);
    bool canPlace(std::pair<int, int> newPos, std::vector<std::vector<char>> newMatrix);

    int width_;
    int height_;
    std::vector<std::vector<Cell *>> board_;
    std::vector<Block *> blocks_;
    Block *currBlock_;
};

#endif
