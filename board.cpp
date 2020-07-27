
#include "board.h"
#include "cell.h"
#include "block.h"
#include "controller.h"

#include <vector>
#include <iostream>

Board::Board(int h, int w)
{
    std::cout << "Board born" << std::endl;
    this->height_ = h;
    this->width_ = w;
    for (int i = 0; i < h; i++)
    {
        std::vector<Cell *> newRow;
        this->board_.push_back(newRow);
        for (int j = 0; j < w; j++)
        {
            Cell *newCell = new Cell(i, j, ' ');
            this->board_[i].push_back(newCell);
        }
    }
};

Board::~Board()
{
    std::cout << "Board died" << std::endl;
    for (int i = 0; i < this->height_; i++)
    {
        for (int j = 0; j < this->width_; j++)
        {
            Cell *cell = this->board_[i][j];
            delete cell;
        }
    }
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

std::vector<std::vector<char>> Board::getBoard()
{
    std::vector<std::vector<char>> printBoard;
    for (int i = 0; i < this->height_; i++)
    {
        std::vector<char> newRow;
        printBoard.push_back(newRow);
        for (int j = 0; j < this->width_; j++)
        {
            Cell *cell = this->board_[i][j];
            printBoard[i].push_back(cell->getSymbol());
        }
    }
    return printBoard;
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

int Board::getHeight() const
{
    return this->height_;
};
int Board::getWidth() const
{
    return this->width_;
};