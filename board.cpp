
#include "board.h"
#include "cell.h"
#include "block.h"
#include "controller.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <queue>

using namespace std;

Board::Board(int h, int w)
{
    // std::cout << "Board born" << std::endl;
    this->height_ = h;
    this->width_ = w;

    // Create empty board
    for (int i = 0; i < h; i++)
    {
        std::vector<std::shared_ptr<Cell>> newRow;
        this->board_.push_back(newRow);
        for (int j = 0; j < w; j++)
        {
            this->board_[i].push_back(std::make_unique<Cell>(i, j, ' '));
        }
    }
    this->currBlock_ = nullptr;
};

Board::~Board(){
    // std::cout << "Board died" << std::endl;
};

bool Board::changeCurrentBlock(BlockType newType)
{

    Block newBlock = Block(newType, this->currBlock_->getPos(), this->currBlock_->getLevelGen(), true);

    this->clearCells(this->currBlock_);
    // Check if there's space
    bool canPlaceBlk = this->canPlace(newBlock);

    if (canPlaceBlk)
    {
        this->currBlock_->setMatrix(newBlock.getCells(), newBlock.getBoxHeight(), newBlock.getBlockWidth());
        this->currBlock_->setPos(newBlock.getPos());
    }

    this->updateCells(this->currBlock_);

    return canPlaceBlk;
}

bool Board::addBlock(std::shared_ptr<Block> block)
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

void Board::clearCells(std::shared_ptr<Block> block)
{
    std::vector<std::vector<char>> cells = block->getCells();
    int cellWidth = block->getBoxWidth();
    int cellHeight = block->getBoxHeight();
    // cout << "cellWidth: " << cellWidth << endl;
    // cout << "cellHeight: " << cellHeight << endl;

    std::pair<int, int> topLeftCorner = block->getPos();

    // Set cells
    int bRow = topLeftCorner.first;
    int bCol = topLeftCorner.second;

    // cout << "bRow: " << bRow << endl;
    // cout << "bCol: " << bCol << endl;
    for (int i = bRow; i < bRow + cellHeight; i++)
    {
        for (int j = bCol; j < bCol + cellWidth; j++)
        {
            if (cells[i - bRow][j - bCol] != ' ')
            {
                if (i >= 0 && j >= 0 && i < this->height_ && j < this->width_)
                {
                    this->setCell(i, j, ' ');
                }
            }
        }
    }
}

void Board::updateCells(std::shared_ptr<Block> block)
{
    std::vector<std::vector<char>> cells = block->getCells();
    int cellWidth = block->getBoxWidth();
    int cellHeight = block->getBoxHeight();
    // cout << "cellWidth: " << cellWidth << endl;
    // cout << "cellHeight: " << cellHeight << endl;

    std::pair<int, int> topLeftCorner = block->getPos();

    // Set cells
    int bRow = topLeftCorner.first;
    int bCol = topLeftCorner.second;
    // cout << "bRow: " << bRow << endl;
    // cout << "bCol: " << bCol << endl;

    for (int i = bRow; i < bRow + cellHeight; i++)
    {
        // cout << "Rows: " << cells.size() << endl;
        for (int j = bCol; j < bCol + cellWidth; j++)
        {
            // cout << "Checking: " << i - bRow << ":" << j - bCol << endl;
            // cout << "Cols: " << cells[i - bRow].size() << endl;
            if (cells[i - bRow][j - bCol] != ' ')
            {
                if (i >= 0 && j >= 0 && i < this->height_ && j < this->width_)
                {
                    this->setCell(i, j, cells[i - bRow][j - bCol]);
                }
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

    std::queue<Block> newBlocks = this->currBlock_->moveBlock(c);

    bool canMove = true;
    while (!newBlocks.empty() && canMove)
    {
        Block newBlock = newBlocks.front();

        // Clear old cells so we dont recheck it
        this->clearCells(this->currBlock_);

        canMove = this->canPlace(newBlock);

        if (canMove)
        {
            this->currBlock_->setMatrix(newBlock.getCells(), newBlock.getBoxHeight(), newBlock.getBlockWidth());
            this->currBlock_->setPos(newBlock.getPos());
        }

        this->updateCells(this->currBlock_);

        newBlocks.pop();
    }

    return canMove;
};

bool Board::rotateCurrentBlock(Command c)
{
    cout << "Rotating block" << endl;

    std::queue<Block> newBlocks = this->currBlock_->rotateBlock(c);

    bool canRotate = true;
    while (!newBlocks.empty() && canRotate)
    {
        Block newBlock = newBlocks.front();

        // Clear old cells so we dont recheck it
        this->clearCells(this->currBlock_);

        canRotate = this->canPlace(newBlock);

        if (canRotate)
        {
            this->currBlock_->setMatrix(newBlock.getCells(), newBlock.getBoxHeight(), newBlock.getBlockWidth());
            this->currBlock_->setPos(newBlock.getPos());
        }

        this->updateCells(this->currBlock_);

        newBlocks.pop();
    }

    return canRotate;
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

        // Clear bottom row
        if (rowFull)
        {
            // cout << "Removing h: " << h << endl;
            rowsCleared += 1;
            std::vector<Block> blocksCleared = this->removeLine(h);
            // cout << "Blockes cleared: " << blocksCleared.size() << endl;

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

    metaData.first = rowsCleared;
    metaData.second = totalBlocksCleared;

    return metaData;
};

std::vector<std::vector<char>> Board::getBoard() const
{
    std::vector<std::vector<char>> printBoard;
    for (int i = 0; i < this->height_; i++)
    {
        std::vector<char> newRow;
        printBoard.push_back(newRow);
        for (int j = 0; j < this->width_; j++)
        {
            printBoard[i].push_back(this->board_[i][j]->getSymbol());
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
    vector<Block> clearedBlocks;

    for (int i = 0; i < this->activeBlocks_.size(); i++)
    {

        std::shared_ptr<Block> placedBlock = this->activeBlocks_[i];

        pair<int, int> curPos = placedBlock->getPos();
        int bHeight = placedBlock->getBlockHeight();
        int rowStart = curPos.first;
        int rowEnd = rowStart + bHeight - 1;
        // cout << "Block first: " << curPos.first << endl;
        // cout << "Block end: " << rowEnd << endl;
        // Removing top row == block is cleared
        // cout << "Checking block" << endl;

        if (h >= rowStart && h <= rowEnd)
        {
            // move down
            // cout << "Block in range" << endl;
            this->clearCells(placedBlock);
            bool clearedBlock = placedBlock->removeLine(h - rowStart);
            // TODO: Check if this is safe
            this->updateCells(placedBlock);
            if (clearedBlock)
            {
                // cout << "Cleared block" << endl;
                this->activeBlocks_.erase(this->activeBlocks_.begin() + i);
                i--;
                clearedBlocks.push_back(*placedBlock);
            }
        }
    }

    // cout << "Moving down" << endl;
    for (int i = 0; i < this->activeBlocks_.size(); i++)
    {
        std::shared_ptr<Block> placedBlock = this->activeBlocks_[i];

        pair<int, int> curPos = placedBlock->getPos();
        int rowStart = curPos.first;

        // cout << "Block start: " << rowStart << endl;
        // cout << "h: " << h << endl;
        if (rowStart < h)
        {
            this->clearCells(placedBlock);
            curPos.first += 1;
            placedBlock->setPos(curPos);
            this->updateCells(placedBlock);
        }
    }

    return clearedBlocks;
};

void Board::resetBoard()
{
    for (int i = 0; i < this->height_; i++)
    {
        for (int j = 0; j < this->width_; j++)
        {
            this->board_[i][j]->setSymbol(' ');
        }
    }

    this->activeBlocks_.clear();
    this->clearedBlocks_.clear();

    this->currBlock_ = nullptr;
};

void Board::showHint(){};

int Board::getHeight() const
{
    return this->height_;
};
int Board::getWidth() const
{
    return this->width_;
};

std::ostream &operator<<(std::ostream &sout, const Board &b)
{
    std::vector<std::vector<char>> board = b.getBoard();
    int height = b.getHeight();
    int width = b.getWidth();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sout << board[i][j];
        }
        sout << std::endl;
    }
    return sout;
}