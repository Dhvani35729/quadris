#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <queue>
#include <string>
#include <cstring>

#include "board.h"
#include "../blocks/block.h"
#include "../blocks/hintblock.h"
#include "cell.h"
#include "../support/constants.h"

using namespace std;

// constructor
Board::Board(int height, int width)
{
    this->height_ = height;
    this->width_ = width;

    // Create an empty board
    for (int i = 0; i < height; i++)
    {
        vector<shared_ptr<Cell>> newRow;
        this->board_.push_back(newRow);
        for (int j = 0; j < width; j++)
        {
            this->board_[i].push_back(make_unique<Cell>(i, j, ' '));
        }
    }

    this->currBlock_ = nullptr;

    // We make a placeholder hint block
    // and then reuse the same memory
    // each time we update the hint block
    this->hintBlock_ = make_shared<Block>(BAD_BLK, make_pair(-1, -1), 0, false);
};

// destructor
Board::~Board(){};

// Returns true if the block could be added (legal move)
bool Board::addBlock(shared_ptr<Block> block)
{
    // First, check if the block can be placed on the board
    bool canPlaceBlk = this->canPlace(*block);

    // If the block can be placed, make it the current block
    // and add it to the list of active blocks
    // Also, add it to the grid of cells (i.e. the board)
    if (canPlaceBlk)
    {
        this->currBlock_ = block;
        this->activeBlocks_.push_back(block);
        this->updateCells(block);
    }

    return canPlaceBlk;
};

// Returns true if the block could be moved (legal move)
bool Board::moveCurrentBlock(Direction dir)
{

    // First, we get the queue of "potential" blocks
    // resulting from the move operation
    queue<Block> newBlocks = this->currBlock_->moveBlock(dir);

    // For each block in the queue, we check if
    // it can be placed on the board and update
    // the grid of cells (i.e. the board) if it can

    bool canMove = true;
    while (!newBlocks.empty() && canMove)
    {
        Block newBlock = newBlocks.front();

        // Clear the current block from the grid of cells
        // so that we don't recheck it (there may be overlaps)
        this->clearCells(this->currBlock_);

        canMove = this->canPlace(newBlock);

        if (canMove)
        {
            // Update the current block's matrix and position
            this->currBlock_->setMatrix(
                newBlock.getCells(),
                newBlock.getBoxHeight(),
                newBlock.getBoxWidth());
            this->currBlock_->setPos(newBlock.getPos());
        }

        this->updateCells(this->currBlock_);

        newBlocks.pop();
    }

    return canMove;
};

// Returns true if the block could be rotated (legal move)
bool Board::rotateCurrentBlock(Direction dir)
{

    // First, we get the queue of "potential" blocks
    // resulting from the rotate operation
    queue<Block> newBlocks = this->currBlock_->rotateBlock(dir);

    // For each block in the queue, we check if
    // it can be placed on the board and update
    // the grid of cells (i.e. the board) if it can

    bool canRotate = true;
    while (!newBlocks.empty() && canRotate)
    {
        Block newBlock = newBlocks.front();

        // Clear the current block from the grid of cells
        // so that we don't recheck it (there may be overlaps)
        this->clearCells(this->currBlock_);

        canRotate = this->canPlace(newBlock);

        if (canRotate)
        {
            // Update the current block's matrix and position
            this->currBlock_->setMatrix(
                newBlock.getCells(),
                newBlock.getBoxHeight(),
                newBlock.getBoxWidth());
            this->currBlock_->setPos(newBlock.getPos());
        }

        this->updateCells(this->currBlock_);

        newBlocks.pop();
    }

    return canRotate;
};

// Returns the number of lines cleared
// and a list of blocks cleared
pair<int, vector<Block>> Board::dropCurrentBlock()
{
    pair<int, vector<Block>> metaData;

    // First, move the block down as much as we can
    bool moved = false;
    do
    {
        moved = this->moveCurrentBlock(DOWN);
    } while (moved);

    // Now, the block is where it should be once it is dropped
    // We check if any rows should be cleared and remove them

    bool rowFull = true;

    // We also keep track of the number of rows cleared
    // and the number of blocks cleared
    int rowsCleared = 0;
    vector<Block> totalBlocksCleared;

    // Check from the bottom up
    int h = this->height_ - 1;
    do
    {
        // Check if the row at h is full
        rowFull = this->isRowFull(h);

        // If the row is full, we remove the line
        // which will also move the rows above it down by 1
        if (rowFull)
        {
            rowsCleared += 1;
            vector<Block> blocksCleared = this->removeLine(h);

            // We add the blocks cleared from removing this line
            // to the total list of blocks cleared (from removing all lines)
            for (int i = 0; i < blocksCleared.size(); i++)
            {
                totalBlocksCleared.push_back(blocksCleared[i]);
            }

            // Since we move rows down by 1, we don't decrement h
            // as we need to check this h again
        }
        else
        {
            // Go up to the next row if the row was not full
            h--;
        }
    } while (rowFull || h >= 0);

    metaData.first = rowsCleared;
    metaData.second = totalBlocksCleared;

    return metaData;
};

// Returns true if the block could be changed (legal move)
bool Board::changeCurrentBlock(BlockType newType)
{
    // Create the new "potential" block
    Block newBlock = Block(newType,
                           this->currBlock_->getPos(),
                           this->currBlock_->getLevelGen(),
                           true);

    // Clear the current block from the grid of cells
    // so that we don't recheck it (there may be overlaps)
    this->clearCells(this->currBlock_);

    // Then, we check if the block can be placed on the board
    bool canPlaceBlk = this->canPlace(newBlock);

    // If the block can be placed, update the current block
    // to this new block
    if (canPlaceBlk)
    {
        this->currBlock_->setType(newType);
        this->currBlock_->setMatrix(
            newBlock.getCells(), newBlock.getBoxHeight(), newBlock.getBoxWidth());
        this->currBlock_->setPos(newBlock.getPos());
    }

    // Re add the current block to the grid of cells
    // This will be the new block if it could be placed
    // or the original block if it couldn't
    this->updateCells(this->currBlock_);

    return canPlaceBlk;
}

void Board::resetBoard()
{
    // Clear the grid of cells and make it empty
    for (int i = 0; i < this->height_; i++)
    {
        for (int j = 0; j < this->width_; j++)
        {
            this->board_[i][j]->setSymbol(' ');
        }
    }

    // Clear the list of active and cleared blocks
    this->activeBlocks_.clear();
    this->clearedBlocks_.clear();

    // Reset the current block
    this->currBlock_ = nullptr;
};

// Helper methods

// Update a cell in the grid of cells
void Board::setCell(int row, int col, char symbol)
{
    this->board_[row][col]->setSymbol(symbol);
};

// Returns true if the given block can be placed
// on the board (legal move)
bool Board::canPlace(Block &newBlock)
{
    pair<int, int> newPos = newBlock.getPos();
    vector<vector<char>> newMatrix = newBlock.getCells();

    // First we check if the block is in bounds of the board
    bool rowOutBounds = newPos.first < 0 ||
                        newPos.first >= this->height_ ||
                        newPos.first + newBlock.getBlockHeight() > this->height_;
    bool colOutBounds = newPos.second < 0 ||
                        newPos.second >= this->width_ ||
                        newPos.second + newBlock.getBlockWidth() > this->width_;

    if (rowOutBounds || colOutBounds)
    {
        return false;
    }

    // Then, we check if the block does not overlap any existing blocks

    int bRow = newPos.first;
    int bCol = newPos.second;

    bool canPlace = true;
    for (int i = bRow; i < bRow + newMatrix.size(); i++)
    {
        for (int j = bCol; j < bCol + newMatrix[i - bRow].size(); j++)
        {
            if (newMatrix[i - bRow][j - bCol] != ' ' &&
                this->board_[i][j]->isOccupied())
            {
                canPlace = false;
                break;
            }
        }

        if (!canPlace)
        {
            break;
        }
    }

    return canPlace;
}

// Adds the given block to the grid of cells (i.e. the board)
void Board::updateCells(shared_ptr<Block> block)
{
    vector<vector<char>> cells = block->getCells();
    int cellWidth = block->getBoxWidth();
    int cellHeight = block->getBoxHeight();

    pair<int, int> topLeftCorner = block->getPos();

    int bRow = topLeftCorner.first;
    int bCol = topLeftCorner.second;

    // We iterate through the matrix of the block
    // by starting from the top left corner
    for (int i = bRow; i < bRow + cellHeight; i++)
    {
        for (int j = bCol; j < bCol + cellWidth; j++)
        {
            // if the spot in the matrix isn't empty
            // (i.e. this is where a block celll is)
            char symbol = cells[i - bRow][j - bCol];
            if (symbol != ' ')
            {
                // Bounds check
                if (i >= 0 && j >= 0 && i < this->height_ && j < this->width_)
                {
                    // Add it to the grid of cells (i.e. the board)
                    this->setCell(i, j, symbol);
                }
            }
        }
    }
}

// Removes the given block from the grid of cells (i.e. the board)
void Board::clearCells(shared_ptr<Block> block)
{
    vector<vector<char>> cells = block->getCells();
    int cellWidth = block->getBoxWidth();
    int cellHeight = block->getBoxHeight();

    pair<int, int> topLeftCorner = block->getPos();

    int bRow = topLeftCorner.first;
    int bCol = topLeftCorner.second;

    // We iterate through the matrix of the block
    // by starting from the top left corner
    for (int i = bRow; i < bRow + cellHeight; i++)
    {
        for (int j = bCol; j < bCol + cellWidth; j++)
        {
            // if the spot in the matrix isn't empty
            // (i.e. this is where a block celll is)
            char symbol = cells[i - bRow][j - bCol];
            if (symbol != ' ')
            {
                // Bounds check
                if (i >= 0 && j >= 0 && i < this->height_ && j < this->width_)
                {
                    // Clear the cell from the grid  (i.e. the board)
                    this->setCell(i, j, ' ');
                }
            }
        }
    }
}

// Returns true if the row is full
bool Board::isRowFull(int h)
{
    // Iterate through the cols for the row h
    // and check if each cell is occupied
    for (int j = 0; j < this->width_; j++)
    {
        if (!this->board_[h][j]->isOccupied())
        {
            return false;
        }
    }
    return true;
};

// Removes the given h from the grid of cells (i.e. the board)
// and returns the blocks that were cleared by doing that
vector<Block> Board::removeLine(int h)
{
    vector<Block> clearedBlocks;

    // Iterate through all the active blocks
    // and check if they are in range of the row being cleared
    // If they are, call the block's corresponding removeLine method
    for (int i = 0; i < this->activeBlocks_.size(); i++)
    {
        shared_ptr<Block> placedBlock = this->activeBlocks_[i];

        pair<int, int> curPos = placedBlock->getPos();
        int bHeight = placedBlock->getBlockHeight();
        int rowStart = curPos.first;
        int rowEnd = rowStart + bHeight - 1;

        // If h in range
        if (h >= rowStart && h <= rowEnd)
        {
            // Clear the current block from the grid of cells
            // so that we don't recheck it (there may be overlaps)
            this->clearCells(placedBlock);

            bool clearedBlock = placedBlock->removeLine(h - rowStart);

            // Re add the placed block to the grid of cells
            this->updateCells(placedBlock);

            // If the block was cleared, we remove it from active blocks
            // and add it to the list of cleared blocks
            if (clearedBlock)
            {
                this->activeBlocks_.erase(this->activeBlocks_.begin() + i);
                i--;
                clearedBlocks.push_back(*placedBlock);
            }
        }
    }

    // At this point, we have updated the blocks that were in range
    // of the row being cleared
    // Now we move all the blocks that are above the row that was cleared
    // down by 1
    for (int i = 0; i < this->activeBlocks_.size(); i++)
    {
        shared_ptr<Block> placedBlock = this->activeBlocks_[i];

        pair<int, int> curPos = placedBlock->getPos();
        int rowStart = curPos.first;

        if (rowStart < h)
        {
            // Clear the current block from the grid of cells
            // so that we don't recheck it (there may be overlaps)
            this->clearCells(placedBlock);

            // Move down the block down by 1
            // Note: we know this will be a valid move
            // as we have just cleared a row
            curPos.first += 1;
            placedBlock->setPos(curPos);

            // Re add the placed block to the grid of cells
            this->updateCells(placedBlock);
        }
    }

    return clearedBlocks;
};

// Remove the hint block from the board
void Board::hideHint()
{
    // Check if we have a valid hint block
    if (this->hintBlock_->getPos().first != -1)
    {
        this->clearCells(this->hintBlock_);
        this->hintBlock_->setPos(make_pair(-1, -1));
    }
}

// Helper method for showHint() to generate permutations
// Takes in a list of base commands
// and appends new commands to newCommands
// i.e. a previous command such as "RIGHT RIGHT DOWN"
// Would create 5 new commands:
// "RIGHT RIGHT DOWN DOWN"
// "RIGHT RIGHT DOWN LEFT"
// "RIGHT RIGHT DOWN RIGHT"
// "RIGHT RIGHT DOWN CLOCKWISE"
// "RIGHT RIGHT DOWN COUNTERCLOCKWISE"
void genPermutations(
    vector<char> &baseCommands,
    vector<string> &newCommands,
    vector<string> &prevCommands)
{
    for (int i = 0; i < prevCommands.size(); i++)
    {
        for (int j = 0; j < baseCommands.size(); j++)
        {
            string newCmd = prevCommands[i];
            string newSuffix = newCmd.substr(newCmd.size() - 1) + baseCommands[j];
            const char *cmpString = newSuffix.c_str();

            // We do not allow consecutive complementary commands such as "left right"
            // as these bring the block to the same spot
            if (strcmp(cmpString, "lr") != 0 &&
                strcmp(cmpString, "rl") != 0 &&
                strcmp(cmpString, "cj") != 0 &&
                strcmp(cmpString, "jc") != 0)
            {
                newCmd += baseCommands[j];
                newCommands.push_back(newCmd);
            }
        }
    }
}

// Show the hint block on the board
// Hint works in the following way:
// We start with the base commands.
// Then we generate permutations for each one by adding
// one of each base command
// We check which commands generate valid blocks, and keep track of them
// For the valid commands, we generate more permutations, and repeat
// We keep doing this until, no valid commands are generated
void Board::showHint()
{
    string decodeDir = "lrdcj";

    vector<char> baseCommands{'l', 'r', 'd', 'c', 'j'};

    vector<pair<Block, int>> totalLegalBlocks;
    vector<Block> addedBlocks;
    int lowestPenalty = -1;

    // Start Trials

    vector<pair<Block, int>> legalBlocks;

    // Save current block so that we can replace it
    // after each trial
    Block savedBlock = *this->currBlock_;

    // Check valid permutations of length 1
    int permNum = 1;
    vector<string> newCommands = {"r", "l", "d", "c", "j"};
    do
    {
        if (permNum > 1)
        {
            // Generate the permutations of commands
            // and store them in newCommands
            vector<string> prevCommands = newCommands;
            genPermutations(baseCommands, newCommands, prevCommands);
        }

        // Clear the list of previously generated legal blocks
        legalBlocks.clear();

        // Execute each command and check if it produces a legal block
        for (int i = 0; i < newCommands.size(); i++)
        {
            bool validCommand = false;

            for (int j = 0; j < newCommands[i].size(); j++)
            {

                // Decode the char into the command
                char cmdCode = newCommands[i][j];
                Direction cmd = (Direction)decodeDir.find(cmdCode);

                if (cmd == LEFT || cmd == RIGHT || cmd == DOWN)
                {
                    validCommand = this->moveCurrentBlock(cmd);
                }
                if (cmd == CLOCKWISE || cmd == COUNTERCLOCKWISE)
                {
                    validCommand = this->rotateCurrentBlock(cmd);
                }

                if (!validCommand)
                {
                    break;
                }
            }

            if (validCommand)
            {
                // If the command was valid, drop the block
                bool moved = false;
                do
                {
                    moved = this->moveCurrentBlock(DOWN);
                } while (moved);

                // We check if, a different command
                // in the past has already produced the same block
                if (find(addedBlocks.begin(), addedBlocks.end(), *this->currBlock_) !=
                    addedBlocks.end())
                {
                    // If it does, remove this permutation
                    newCommands.erase(newCommands.begin() + i);
                    i--;
                }
                else
                {
                    // Now we have a legal, new block

                    // Calculate the penalty with this new block placed
                    int penalty = this->calcPenalty();

                    // Keep track of the lowest penalty
                    if (lowestPenalty == -1)
                    {
                        lowestPenalty = penalty;
                    }
                    if (penalty < lowestPenalty)
                    {
                        lowestPenalty = penalty;
                    }

                    pair<Block, int> legalBlk = make_pair(*this->currBlock_, penalty);
                    legalBlocks.push_back(legalBlk);
                    totalLegalBlocks.push_back(legalBlk);
                    addedBlocks.push_back(*this->currBlock_);
                }
            }
            else
            {
                // If the command is invalid, remove this permutation
                newCommands.erase(newCommands.begin() + i);
                i--;
            }

            // Remove the trial block
            this->clearCells(this->currBlock_);

            // Restore the current block for the next trial
            this->currBlock_->setMatrix(
                savedBlock.getCells(),
                savedBlock.getBoxHeight(),
                savedBlock.getBoxWidth());
            this->currBlock_->setPos(savedBlock.getPos());

            this->updateCells(this->currBlock_);
        }

        // Increment our perm number
        permNum += 1;

    } while (legalBlocks.size() > 0);

    // End Trials

    // At this point, we have a list of legal blocks,
    // each with their own corresponding penalty

    // Take the first legal block with the lowest penalty
    for (int i = 0; i < totalLegalBlocks.size(); i++)
    {
        if (totalLegalBlocks[i].second <= lowestPenalty)
        {
            HintBlock hintBlock(totalLegalBlocks[i].first);

            // Update the hint block
            this->hintBlock_->setType(hintBlock.getBlockType());
            this->hintBlock_->setMatrix(
                hintBlock.getCells(),
                hintBlock.getBoxHeight(),
                hintBlock.getBoxWidth());
            this->hintBlock_->setPos(hintBlock.getPos());

            // Show the hint block on the board
            this->updateCells(this->hintBlock_);

            break;
        }
    }
}

// Calculates the penalty for the current grid of cells
// The penalty is calculated as follows
// penalty = # of holes + height of placed block + # of long empty cols
// This way, a grid with a low number of holes, a low height
// and a low number of long empty cols, will have a low penalty
// We penalize the # of holes more by giving it a weight of 2
int Board::calcPenalty()
{
    int penalty = 0;

    // Check #1
    // Num of holes left after block is placed

    int holes = 0;

    for (int i = 0; i < this->height_; i++)
    {
        for (int j = 0; j < this->width_; j++)
        {
            if (!this->board_[i][j]->isOccupied())
            {
                // Is the col above it empty
                bool spaceAbove = true;
                for (int r = 0; r < i; r++)
                {
                    if (this->board_[r][j]->isOccupied())
                    {
                        spaceAbove = false;
                        break;
                    }
                }
                if (!spaceAbove)
                {
                    holes += 1;
                }
            }
        }
    }

    // Check #2
    // Penalize columns with 3 or more empty cells
    int iCols = 0;
    for (int j = 0; j < this->width_; j++)
    {
        int rowEmpty = 0;
        for (int i = this->height_ - 1; i >= 0; i--)
        {
            if (!this->board_[i][j]->isOccupied())
            {
                rowEmpty += 1;
            }
            else
            {
                break;
            }
        }
        if (rowEmpty >= 3)
        {
            iCols += 1;
        }
    }

    penalty += iCols;

    // Weight holes more
    penalty += holes * 2;

    // Check 3:
    // Add the height of the placed block. The lower the better
    penalty += this->height_ - this->currBlock_->getPos().first;

    return penalty;
}

// Play the hint block as a turn
void Board::playHint()
{
    this->clearCells(this->hintBlock_);

    // Update the type of the hint block to the current block
    this->hintBlock_->setType(this->currBlock_->getBlockType());

    // Clear the current block from the grid of cells
    // so that we don't recheck it (there may be overlaps)
    this->clearCells(this->currBlock_);

    this->currBlock_->setMatrix(
        this->hintBlock_->getCells(),
        this->hintBlock_->getBoxHeight(),
        this->hintBlock_->getBoxWidth());
    this->currBlock_->setPos(this->hintBlock_->getPos());

    // Readd the current block to the grid of cell (i.e. the board)
    // in the new spot
    this->updateCells(this->currBlock_);
};

// Output operator to print the Board (i.e. it's grid of cells)
ostream &operator<<(ostream &sout, const Board &b)
{
    vector<vector<char>> board = b.getBoard();
    int height = b.getHeight();
    int width = b.getWidth();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sout << board[i][j];
        }
        sout << endl;
    }
    return sout;
}

// Getters

vector<vector<char>> Board::getBoard() const
{
    // Turn the grid of cells into a 2D grid of char's
    vector<vector<char>> printBoard;
    for (int i = 0; i < this->height_; i++)
    {
        vector<char> newRow;
        printBoard.push_back(newRow);
        for (int j = 0; j < this->width_; j++)
        {
            printBoard[i].push_back(this->board_[i][j]->getSymbol());
        }
    }
    return printBoard;
};

int Board::getHeight() const
{
    return this->height_;
};
int Board::getWidth() const
{
    return this->width_;
};