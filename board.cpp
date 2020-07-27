
#include "board.h"
#include "cell.h"
#include "block.h"
#include "controller.h"

#include <vector>
#include <iostream>

Board::Board(int h, int w)
{
    this->height_ = h;
    this->width_ = w;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            Cell *newCell = new Cell(i, j, ' ');
            this->board_[i][j] = newCell;
        }
    }
    std::cout << "Board born" << std::endl;
};

Board::~Board()
{
    std::cout << "Board died" << std::endl;
};

void Board::addBlock(Block *){

};

void Board::setCell(int, int, char){

};

bool Board::moveCurrentBlock(Command)
{
    return true;
};

bool Board::rotateCurrentBlock(Command)
{
    return true;
};

int Board::dropCurrentBlock()
{
    return -1;
};

std::vector<std::vector<Cell *>> Board::getBoard()
{
    return board_;
};

bool Board::isOccupied(int, int)
{
    return true;
};

bool Board::isLineFull(int)
{
    return true;
};

bool Board::removeLine(int)
{
    return true;
};

void Board::resetBoard(){};

void Board::showHint(){};