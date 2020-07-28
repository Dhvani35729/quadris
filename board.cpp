
#include "board.h"
#include "cell.h"
#include "block.h"
#include "controller.h"

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

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
    for (int i = 0; i < this->blocks_.size(); i++)
    {
        Block *block = this->blocks_[i];
        delete block;
    }
};

void Board::addBlock(Block *block)
{
    std::cout << "Adding block to board" << std::endl;

    this->currBlock_ = block;
    // TODO: Need to check if CAN add block
    this->blocks_.push_back(block);
    this->updateCells(block);
};

void Board::clearCells(Block *block)
{
    std::vector<std::vector<char>> cells = block->getCells();
    int cellWidth = block->getBoxWidth();
    int cellHeight = block->getBoxHeight();

    std::pair<int, int> topLeftCorner = block->getPos();

    // TODO: SHOULD BE ITERATOR PATTERN?
    // Set cells
    int bRow = topLeftCorner.first;
    int bCol = topLeftCorner.second;

    for (int i = bRow; i < bRow + cellHeight; i++)
    {
        for (int j = bCol; j < bCol + cellWidth; j++)
        {
            if (cells[i - bRow][j - bCol] != ' ')
            {
                this->setCell(i, j, ' ');
            }
        }
    }
}

void Board::updateCells(Block *block)
{
    std::vector<std::vector<char>> cells = block->getCells();
    int cellWidth = block->getBoxWidth();
    int cellHeight = block->getBoxHeight();

    std::pair<int, int> topLeftCorner = block->getPos();

    // Set cells
    int bRow = topLeftCorner.first;
    int bCol = topLeftCorner.second;

    for (int i = bRow; i < bRow + cellHeight; i++)
    {
        for (int j = bCol; j < bCol + cellWidth; j++)
        {
            if (cells[i - bRow][j - bCol] != ' ')
            {
                this->setCell(i, j, cells[i - bRow][j - bCol]);
            }
        }
    }
}

void Board::setCell(int i, int j, char c)
{
    this->board_[i][j]->setSymbol(c);
};

bool Board::moveCurrentBlock(Command)
{
    return true;
};

bool Board::canPlace(std::pair<int, int> newPos, std::vector<std::vector<char>> newMatrix)
{
    pair<int, int> curPos = this->currBlock_->getPos();
    std::vector<std::vector<char>> currMatrix = this->currBlock_->getCells();

    // Clear old cells so we dont recheck it
    this->clearCells(this->currBlock_);

    int cellWidth = this->currBlock_->getBoxWidth();
    int cellHeight = this->currBlock_->getBoxHeight();

    int bRow = newPos.first;
    int bCol = newPos.second;

    int k = cellHeight - 1;
    bool canPlace = true;
    for (int i = bRow; i < bRow + cellHeight; i++)
    {
        for (int j = bCol; j < bCol + cellWidth; j++)
        {
            if (newMatrix[i - bRow][j - bCol] != ' ' && this->board_[i][j]->isOccupied())
            {
                canPlace = false;
                break;
            }
        }
    }

    // Clear old cells so we dont recheck it
    this->updateCells(this->currBlock_);

    return canPlace;
}

bool Board::rotateCurrentBlock(Command c)
{
    std::vector<std::vector<char>> newMatrix = this->currBlock_->rotateBlock(c);
    // this->canPlace(this->currBlock_->getCells(), newMatrix);
    return true;
};

int Board::dropCurrentBlock()
{
    cout << "Dropping block: " << endl;
    // Get what we need
    pair<int, int> curPos = this->currBlock_->getPos();
    cout << "Curr: " << curPos.first << ":" << curPos.second << endl;
    int blockHeight = this->currBlock_->getBlockHeight();
    cout << "Block H: " << blockHeight << endl;
    int boxWidth = this->currBlock_->getBoxWidth();

    // Figure out the new height
    int newH;
    for (newH = curPos.first + blockHeight; newH <= this->height_ - blockHeight; newH++)
    {
        bool occupied = false;
        for (int j = 0; j < boxWidth; j++)
        {
            cout << "Checked: " << newH << ":" << j << endl;
            if (this->board_[newH][j]->isOccupied())
            {
                occupied = true;
                break;
            }
        }
        if (occupied)
        {
            break;
        }
    }
    newH--;
    cout << "New height before: " << newH << endl;
    if (newH != this->height_ - 1)
    {
        cout << "adjusting" << endl;
        newH -= blockHeight - 1;
    }

    cout << "New height: " << newH << endl;
    // Potential new pos
    pair<int, int> newPos = make_pair(newH, curPos.second);
    cout << "New: " << newPos.first << ":" << newPos.second << endl;

    // Need to check if the new spot conficts
    bool canPlaceBlk = this->canPlace(newPos, this->currBlock_->getCells());

    if (canPlaceBlk)
    {
        this->clearCells(this->currBlock_);

        this->currBlock_->dropBlock(newH);

        this->updateCells(this->currBlock_);
    }
    else
    {
        cout << "ERROR: COULD NOT PLACE BLOCK!!" << endl;
    }

    // Check if last row full
    bool rowFull = true;
    int rowsCleared = 0;
    // do
    // {
    //     for (int j = 0; j < this->width_; j++)
    //     {
    //         if (this->board_[this->height_ - 1][j]->getSymbol() != ' ')
    //         {
    //             rowFull = false;
    //             break;
    //         }
    //     }
    //     // Clear bottm row
    //     if (rowFull)
    //     {
    //         rowsCleared += 1;
    //         for (int i = this->height_ - 2; i >= 0; i--)
    //         {
    //             for (int j = 0; j < this->height_; j++)
    //             {
    //                 this->setCell(i + 1, j, this->board_[i][j]->getSymbol());
    //             }
    //         }
    //         for (int j = 0; j < this->width_; j++)
    //         {
    //             this->setCell(0, j, ' ');
    //         }
    //     }
    // } while (rowFull);

    return rowsCleared;
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

bool Board::isOccupied(int i, int j)
{
    return this->board_[i][j]->isOccupied();
};

bool Board::isLineFull(int h)
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