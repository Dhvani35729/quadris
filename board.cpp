#include "board.h"
#include "cell.h"
#include "block.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <cstring>

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
    this->hintBlock_ = make_shared<Block>(BAD_BLK, make_pair(-1, -1), 0, false);
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
        this->currBlock_->setType(newType);
        this->currBlock_->setMatrix(newBlock.getCells(), newBlock.getBoxHeight(), newBlock.getBoxWidth());
        this->currBlock_->setPos(newBlock.getPos());
    }

    this->updateCells(this->currBlock_);

    return canPlaceBlk;
}

bool Board::addBlock(std::shared_ptr<Block> block)
{
    // std::cout << "Adding block to board" << std::endl;

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

bool Board::moveCurrentBlock(Direction c)
{

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
            this->currBlock_->setMatrix(newBlock.getCells(), newBlock.getBoxHeight(), newBlock.getBoxWidth());
            this->currBlock_->setPos(newBlock.getPos());
        }

        this->updateCells(this->currBlock_);

        newBlocks.pop();
    }

    return canMove;
};

bool Board::rotateCurrentBlock(Direction c)
{
    // cout << "Rotating block" << endl;

    std::queue<Block> newBlocks = this->currBlock_->rotateBlock(c);

    // cout << newBlocks.size() << endl;
    bool canRotate = true;
    while (!newBlocks.empty() && canRotate)
    {
        Block newBlock = newBlocks.front();

        // Clear old cells so we dont recheck it
        this->clearCells(this->currBlock_);

        canRotate = this->canPlace(newBlock);

        if (canRotate)
        {
            this->currBlock_->setMatrix(newBlock.getCells(), newBlock.getBoxHeight(), newBlock.getBoxWidth());
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

void Board::playHint()
{

    this->clearCells(this->hintBlock_);
    this->hintBlock_->setType(this->currBlock_->getBlockType());

    this->clearCells(this->currBlock_);
    this->currBlock_->setMatrix(this->hintBlock_->getCells(), this->hintBlock_->getBoxHeight(), this->hintBlock_->getBoxWidth());
    this->currBlock_->setPos(this->hintBlock_->getPos());
    // cout << "Hinted block pos: " << this->currBlock_->getPos().first << ":" << this->currBlock_->getPos().second << endl;

    this->updateCells(this->currBlock_);
};
std::pair<int, std::vector<Block>> Board::dropCurrentBlock()
{
    // cout << "Dropping block: " << endl;
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

bool Board::isLineEmpty(int h)
{
    for (int j = 0; j < this->width_; j++)
    {
        if (this->board_[h][j]->isOccupied())
        {
            return false;
        }
    }
    return true;
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
        // cout << "Block pos: " << curPos.first << ":" << curPos.second << endl;
        // cout << "Block end: " << rowEnd << endl;
        // Removing top row == block is cleared
        // cout << "Checking block" << endl;

        if (h >= rowStart && h <= rowEnd)
        {
            // move down
            // cout << "Block in range" << endl;
            this->clearCells(placedBlock);
            bool clearedBlock = placedBlock->removeLine(h - rowStart);

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

int Board::calcPenalty()
{
    // We will assign a penalty to each list of commands
    // The hint will then be the command with the lowest penalty

    // cout << "Calcing penalty for: " << endl;
    // cout << *this << endl;

    int penalty = 0;
    // Check #1
    // Num of holes left after block is placed

    // Otherwise no lines full and no chances of holes
    int holes = 0;
    // Check all rows beneath this and count number of holes
    for (int i = 0; i < this->height_; i++)
    {
        for (int j = 0; j < this->width_; j++)
        {
            if (!this->board_[i][j]->isOccupied())
            {
                // cout << "Check if space above for: " << i << ":" << j << endl;
                // Is the col above it empty
                bool spaceAbove = true;
                for (int r = 0; r < i; r++)
                {
                    if (this->board_[r][j]->isOccupied())
                    {
                        // cout << "Occupied!: " << r << ":" << j << endl;
                        spaceAbove = false;
                        break;
                    }
                }
                if (!spaceAbove)
                {
                    // cout << "Counting hole" << endl;
                    holes += 1;
                }
            }
        }
    }

    // Penalize columns with 3 or more empty holes
    // Bot is waiting for an I block
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

    // cout << "Adding holes: " << holes << endl;
    // Weight holes more:
    penalty += holes * 2;

    // Check 2: Add height to penalty. The lower the better
    penalty += this->height_ - this->currBlock_->getPos().first;

    // cout << "Penalty: " << penalty << endl;

    return penalty;
}

void Board::hideHint()
{
    if (this->hintBlock_->getPos().first != -1)
    {
        this->clearCells(this->hintBlock_);
        this->hintBlock_->setPos(make_pair(-1, -1));
    }
}

void genPermutations(char baseCommands[], int totalCommands, vector<string> &newCommands, vector<string> &prevCommands)
{
    for (int i = 0; i < prevCommands.size(); i++)
    {
        for (int j = 0; j < totalCommands; j++)
        {
            // cout << "old: " << prevCommands[i] << endl;
            string newCmd = prevCommands[i];
            string newSuffix = newCmd.substr(newCmd.size() - 1) + baseCommands[j];
            const char *cmpString = newSuffix.c_str();
            // cout << "new: " << newCmd + baseCommands[j] << endl;
            if (std::strcmp(cmpString, "lr") != 0 && std::strcmp(cmpString, "rl") != 0 && std::strcmp(cmpString, "cj") != 0 && std::strcmp(cmpString, "jc") != 0)
            {
                newCmd += baseCommands[j];
                newCommands.push_back(newCmd);
            }
        }
    }
}

Direction decodePerm(char cmdCode)
{
    Direction cmd;
    if (cmdCode == 'l')
    {
        cmd = LEFT;
    }
    else if (cmdCode == 'r')
    {
        cmd = RIGHT;
    }
    else if (cmdCode == 'd')
    {
        cmd = DOWN;
    }
    else if (cmdCode == 'c')
    {
        cmd = CLOCKWISE;
    }
    else if (cmdCode == 'j')
    {
        cmd = COUNTERCLOCKWISE;
    }
    return cmd;
}

void Board::showHint()
{
    // cout << "Showing hint" << endl;

    // Setup
    char commands[] = {'l', 'r', 'd', 'c', 'j'};
    int numCommands = 5;

    // -------------------------------
    vector<pair<Block, int>> totalLegalBlocks;
    vector<Block> addedBlocks;
    int lowestPenalty = -1;

    // Start Trials
    vector<pair<Block, int>> legalBlocks;

    // Save current block
    Block savedBlock = *this->currBlock_;

    int permNum = 1;
    vector<string> newCommands = {"r", "l", "d", "c", "j"};
    do
    {
        // cout << "prev commands: " << newCommands.size() << endl;
        // for (int i = 0; i < newCommands.size(); i++)
        // {
        //     cout << newCommands[i] << endl;
        // }
        if (permNum > 1)
        {
            vector<string> rawCommands;
            // cout << "Getting commands of length: " << permNum << endl;
            // generateCharCommands(commands, rawCommands, "", numCommands, permNum);
            vector<string> prevCommands = newCommands;
            genPermutations(commands, numCommands, rawCommands, prevCommands);
            // for (int i = 0; i < rawCommands.size(); i++)
            // {
            //     cout << rawCommands[i] << endl;
            // }
            // cout << "Trying list of commands #: " << rawCommands.size() << endl;
            newCommands = rawCommands;
        }

        legalBlocks.clear();

        // Need to execute each command and see if it is possilble
        // cout << "Trying list of commands #: " << newCommands.size() << endl;

        for (int i = 0; i < newCommands.size(); i++)
        {
            // cout << "Checking perm #: " << i << endl;
            string cmdPrint = "";
            // List of commands to try
            bool validCommand = false;

            for (int j = 0; j < newCommands[i].size(); j++)
            {
                // cout << newCommands[i][j] << " ";

                // Decode
                char cmdCode = newCommands[i][j];
                Direction cmd = decodePerm(cmdCode);

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
                    // cout << "invalid!" << endl;
                    // cout << "Removing from trie" << endl;
                    // remove(root, newCommands[i]);
                    break;
                }
            }

            if (validCommand)
            {
                // cout << "valid!" << endl;
                bool moved = false;
                do
                {
                    moved = this->moveCurrentBlock(DOWN);
                } while (moved);

                if (std::find(addedBlocks.begin(), addedBlocks.end(), *this->currBlock_) != addedBlocks.end())
                {
                    // cout << "Block already there" << endl;
                    newCommands.erase(newCommands.begin() + i);
                    i--;
                }
                else
                {
                    // cout << "New block!" << endl;
                    // cout << newCommands[i] << endl;

                    // Calculate penalty of legal commands
                    int penalty = this->calcPenalty();
                    // cout << "Penalty: " << penalty << endl;
                    if (lowestPenalty == -1)
                    {
                        lowestPenalty = penalty;
                    }
                    if (penalty < lowestPenalty)
                    {
                        lowestPenalty = penalty;
                    }

                    // cout << "Valid ^^ " << endl;
                    pair<Block, int> legalBlk = make_pair(*this->currBlock_, penalty);
                    legalBlocks.push_back(legalBlk);
                    totalLegalBlocks.push_back(legalBlk);
                    addedBlocks.push_back(*this->currBlock_);
                }
            }
            else
            {
                // cout << "Invalid" << endl;
                // cout << newCommands[i] << endl;
                newCommands.erase(newCommands.begin() + i);
                i--;
            }

            this->clearCells(this->currBlock_);
            // Restore current block
            this->currBlock_->setMatrix(savedBlock.getCells(), savedBlock.getBoxHeight(), savedBlock.getBoxWidth());
            this->currBlock_->setPos(savedBlock.getPos());
            this->updateCells(this->currBlock_);
        }

        permNum += 1;

    } while (legalBlocks.size() > 0);

    // cout << "Legal list of blocks #: " << totalLegalBlocks.size() << endl;

    // End Trials

    // Take the first legal block with the lowest penalty
    for (int i = 0; i < totalLegalBlocks.size(); i++)
    {
        if (totalLegalBlocks[i].second <= lowestPenalty)
        {
            // cout << "Block found" << endl;
            // cout << "Pos: " << totalLegalBlocks[i].first.getPos().first << ":" << totalLegalBlocks[i].first.getPos().second << endl;
            HintBlock hintBlock(totalLegalBlocks[i].first);

            this->hintBlock_->setType(hintBlock.getBlockType());
            this->hintBlock_->setMatrix(hintBlock.getCells(), hintBlock.getBoxHeight(), hintBlock.getBoxWidth());
            this->hintBlock_->setPos(hintBlock.getPos());

            this->updateCells(this->hintBlock_);
            break;
        }
    }
}

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