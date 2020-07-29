
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

    // Create empty board
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
    this->currBlock_ = nullptr;
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
    for (int i = 0; i < this->activeBlocks_.size(); i++)
    {
        Block *block = this->activeBlocks_[i];
        delete block;
    }
    for (int i = 0; i < this->clearedBlocks_.size(); i++)
    {
        Block *block = this->clearedBlocks_[i];
        delete block;
    }
};

bool Board::addBlock(Block *block)
{
    std::cout << "Adding block to board" << std::endl;

    // Check if there's space
    bool canPlaceBlk = this->canPlace(*block);

    if (canPlaceBlk)
    {
        this->currBlock_ = block;
        this->activeBlocks_.push_back(block);
        this->updateCells(block);
    }
    return canPlaceBlk;
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

bool Board::moveCurrentBlock(Command c)
{
    cout << "Moving block" << endl;

    Block newBlock = this->currBlock_->moveBlock(c);

    // Clear old cells so we dont recheck it
    this->clearCells(this->currBlock_);

    bool canMove = this->canPlace(newBlock);

    if (canMove)
    {
        this->currBlock_->setMatrix(newBlock.getCells());
        this->currBlock_->setPos(newBlock.getPos());
    }

    this->updateCells(this->currBlock_);

    return canMove;
};

bool Board::canPlace(Block &newBlock)
{
    std::pair<int, int> newPos = newBlock.getPos();
    std::vector<std::vector<char>> newMatrix = newBlock.getCells();
    // cout << "Checking in place: " << newPos.first << ":" << newPos.second << endl;

    // cout << "BH: " << newBlock.getBlockHeight() << endl;
    // cout << "BW: " << newBlock.getBlockWidth() << endl;
    bool rowOutBounds = newPos.first < 0 || newPos.first >= this->height_ || newPos.first + newBlock.getBlockHeight() > this->height_;
    bool colOutBounds = newPos.second < 0 || newPos.second >= this->width_ || newPos.second + newBlock.getBlockWidth() > this->width_;

    if (rowOutBounds || colOutBounds)
    {
        return false;
    }

    // cout << "In bounds" << endl;

    int bRow = newPos.first;
    int bCol = newPos.second;

    bool canPlace = true;
    for (int i = bRow; i < bRow + newMatrix.size(); i++)
    {
        for (int j = bCol; j < bCol + newMatrix[i - bRow].size(); j++)
        {
            // cout << "Checking matrix: " << i - bRow << ":" << j - bCol << endl;
            // cout << "Checking board: " << i << ":" << j << endl;
            if (newMatrix[i - bRow][j - bCol] != ' ' && this->board_[i][j]->isOccupied())
            {
                canPlace = false;
                break;
            }
        }
    }
    // cout << "Place? " << canPlace << endl;
    return canPlace;
}

bool Board::rotateCurrentBlock(Command c)
{
    cout << "Rotating block" << endl;

    Block newBlock = this->currBlock_->rotateBlock(c);

    // Clear old cells so we dont recheck it
    this->clearCells(this->currBlock_);

    bool canRotate = this->canPlace(newBlock);
    if (canRotate)
    {
        this->currBlock_->setMatrix(newBlock.getCells());
        this->currBlock_->setPos(newBlock.getPos());
    }

    this->updateCells(this->currBlock_);

    return canRotate;
};

std::pair<int, std::vector<Block>> Board::dropCurrentBlock()
{
    cout << "Dropping block: " << endl;
    std::pair<int, std::vector<Block>> metaData;

    bool moved = false;
    do
    {
        moved = this->moveCurrentBlock(DOWN);
    } while (moved);

    // Check if any row full
    bool rowFull = true;
    int rowsCleared = 0;
    int h = this->height_ - 1;
    std::vector<Block> totalBlocksCleared;
    do
    {
        // Check last row full
        rowFull = this->isLineFull(h);

        // Clear bottm row
        if (rowFull)
        {
            // cout << "Removing h: " << h << endl;
            rowsCleared += 1;
            std::vector<Block> blocksCleared = this->removeLine(h);
            for (int i = 0; i < blocksCleared.size(); i++)
            {
                totalBlocksCleared.push_back(blocksCleared[i]);
            }
        }
        else
        {
            h--;
        }
    } while (rowFull || h >= 0);

    // cout << "Active blocks: " << this->activeBlocks_.size() << endl;
    // for (int i = 0; i < this->activeBlocks_.size(); i++)
    // {
    //     cout << *this->activeBlocks_[i] << endl;
    // }
    // cout << "Cleared blocks: " << this->clearedBlocks_.size() << endl;
    // for (int i = 0; i < this->clearedBlocks_.size(); i++)
    // {
    //     cout << *this->clearedBlocks_[i] << endl;
    // }

    metaData.first = rowsCleared;
    metaData.second = totalBlocksCleared;

    return metaData;
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
    for (int j = 0; j < this->width_; j++)
    {
        if (!this->board_[h][j]->isOccupied())
        {
            return false;
        }
    }
    return true;
};

vector<Block> Board::removeLine(int h)
{
    // Move everything down by 1
    for (int i = h - 1; i >= 0; i--)
    {
        for (int j = 0; j < this->width_; j++)
        {
            this->setCell(i + 1, j, this->board_[i][j]->getSymbol());
        }
    }
    // Clear top row
    for (int j = 0; j < this->width_; j++)
    {
        this->setCell(0, j, ' ');
    }

    // Need to check which blocks were placed at this
    // h. These blocks are now completely celeared

    vector<Block> clearedBlocks;
    for (int i = 0; i < this->activeBlocks_.size(); i++)
    {
        Block *placedBlock = this->activeBlocks_[i];
        pair<int, int> curPos = placedBlock->getPos();
        int rowStart = curPos.first;
        int rowEnd = rowStart + placedBlock->getBlockHeight() - 1;
        // cout << "Block first: " << curPos.first << endl;
        // Removing top row == block is cleared
        if (h == rowStart)
        {
            this->activeBlocks_.erase(this->activeBlocks_.begin() + i);
            this->clearedBlocks_.push_back(placedBlock);
            clearedBlocks.push_back(*placedBlock);
            i--;
        }
        else if (h > rowStart && h <= rowEnd)
        {
            // Clearing a portion
            // Move block down by 1
            curPos.first += 1;
            placedBlock->setPos(curPos);
        }
    }
    return clearedBlocks;
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

std::vector<Block *> Board::getClearedBlocks()
{
    return this->clearedBlocks_;
};