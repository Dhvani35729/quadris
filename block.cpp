#include <iostream>
#include <vector>
#include <utility>
#include <queue>

#include "block.h"

using namespace std;

// constructor
Block::Block(BlockType type, pair<int, int> pos, int level, bool playable)
{
    this->type_ = type;
    this->coords_ = pos;
    this->level_ = level;
    this->playable_ = playable;

    // We initialize the blocks and their corresponding box (matrix)

    // All the blocks have 4 cells
    this->numCells_ = 4;

    // All the blocks can fit in a 3x3 matrix except for the I block
    this->mWidth_ = 3;
    this->mHeight_ = 3;
    this->matrix_.resize(this->mHeight_, vector<char>(this->mWidth_, ' '));

    if (type == I_BLK)
    {
        this->mWidth_ = 4;
        this->mHeight_ = 4;

        this->matrix_.clear();
        this->matrix_.resize(this->mHeight_, vector<char>(this->mWidth_, ' '));

        this->matrix_[0][0] = 'I';
        this->matrix_[0][1] = 'I';
        this->matrix_[0][2] = 'I';
        this->matrix_[0][3] = 'I';

        this->blockHeight_ = 1;
        this->blockWidth_ = 4;
    }
    else if (type == J_BLK)
    {
        this->matrix_[0][0] = 'J';
        this->matrix_[1][0] = 'J';
        this->matrix_[1][1] = 'J';
        this->matrix_[1][2] = 'J';

        this->blockHeight_ = 2;
        this->blockWidth_ = 3;
    }
    else if (type == L_BLK)
    {
        this->matrix_[0][2] = 'L';
        this->matrix_[1][0] = 'L';
        this->matrix_[1][1] = 'L';
        this->matrix_[1][2] = 'L';

        this->blockHeight_ = 2;
        this->blockWidth_ = 3;
    }
    else if (type == O_BLK)
    {
        this->matrix_[0][0] = 'O';
        this->matrix_[0][1] = 'O';
        this->matrix_[1][0] = 'O';
        this->matrix_[1][1] = 'O';

        this->blockHeight_ = 2;
        this->blockWidth_ = 2;
    }
    else if (type == S_BLK)
    {
        this->matrix_[0][1] = 'S';
        this->matrix_[0][2] = 'S';
        this->matrix_[1][0] = 'S';
        this->matrix_[1][1] = 'S';

        this->blockHeight_ = 2;
        this->blockWidth_ = 3;
    }
    else if (type == Z_BLK)
    {
        this->matrix_[0][0] = 'Z';
        this->matrix_[0][1] = 'Z';
        this->matrix_[1][1] = 'Z';
        this->matrix_[1][2] = 'Z';

        this->blockHeight_ = 2;
        this->blockWidth_ = 3;
    }
    else if (type == T_BLK)
    {
        this->matrix_[0][0] = 'T';
        this->matrix_[0][1] = 'T';
        this->matrix_[0][2] = 'T';
        this->matrix_[1][1] = 'T';

        this->blockHeight_ = 2;
        this->blockWidth_ = 3;
    }
};

// destructor
Block::~Block(){};

queue<Block> Block::moveBlock(Direction dir)
{
    queue<Block> blocks;

    // Copy current block and construct the
    //  "potential" block
    Block movedBlock{*this};

    if (dir == LEFT)
    {
        // Decrement col
        movedBlock.coords_.second -= 1;
    }
    else if (dir == RIGHT)
    {
        // Increment col
        movedBlock.coords_.second += 1;
    }
    else if (dir == DOWN)
    {
        // Increment row
        movedBlock.coords_.first += 1;
    }

    blocks.push(movedBlock);

    return blocks;
};

// NOTE: Only supports rotations on square matrix
queue<Block> Block::rotateBlock(Direction dir)
{
    queue<Block> blocks;

    // Copy current block and construct the
    //  "potential" block
    Block rotatedBlock{*this};

    // Prev top and bottom left corner
    pair<int, int> prevTCorner = rotatedBlock.getPos();
    pair<int, int> prevBCorner = make_pair(
        prevTCorner.first + rotatedBlock.getBlockHeight() - 1,
        prevTCorner.second);

    // Call helper methods to rotate the block
    if (dir == COUNTERCLOCKWISE)
    {
        rotatedBlock.rotateCounterclockwise();
    }
    else if (dir == CLOCKWISE)
    {
        rotatedBlock.rotateClockwise();
    }

    // Since we do a matrix rotation, and we want to preserve
    // the bottom left corner, we first fix any whitespace
    // i.e. left and top justify the block in the box (matrix)
    rotatedBlock.removeHorizWhitespace();
    rotatedBlock.removeVertWhitespace();

    // Recalculate the block height and width, as a rotation
    // may have changed it
    rotatedBlock.calcBlockSize();

    // We then construct the new top left corner by
    // preserving the bottom left corner
    pair<int, int> newBCorner = make_pair(
        prevTCorner.first + rotatedBlock.getBlockHeight() - 1,
        prevTCorner.second);
    int adjust = newBCorner.first - prevBCorner.first;
    pair<int, int> newTCorner = make_pair(prevTCorner.first - adjust, prevTCorner.second);

    rotatedBlock.setPos(newTCorner);

    blocks.push(rotatedBlock);

    return blocks;
};

bool Block::removeLine(int h)
{
    // Keep track of the number of cells cleared
    int cellsCleared = 0;

    // Iterate through the specificed row
    // and clear the cells if not empty
    for (int j = 0; j < this->blockWidth_; j++)
    {
        if (this->matrix_[h][j] != ' ')
        {
            this->matrix_[h][j] = ' ';
            cellsCleared += 1;
        }
    }

    // Update the number of cells of the block left
    this->numCells_ -= cellsCleared;

    // If the first row was cleared
    // we need to update the block position (increment row)
    if (h == 0)
    {
        this->coords_.first += 1;
    }

    bool cleared = false;

    // If we have no cells left, the block has been cleared
    // otherwise, we apply adjustments
    if (this->numCells_ == 0)
    {
        cleared = true;
    }
    else
    {
        // Since we may clear a middle row of a block
        // we need to fix any white space
        // i.e. left and top justify the block in the box (matrix)
        this->removeHorizWhitespace();

        // Recalculate the block height and width, as removing cells
        // may have changed it
        this->calcBlockSize();
    }

    return cleared;
}

// Setters

void Block::setType(BlockType type)
{
    this->type_ = type;

    // Update the cells in the matrix
    //  to the new type
    string blocks = "IJLSZOT";
    char newSymbol = blocks.at((int)type);

    for (int i = 0; i < this->mHeight_; i++)
    {
        for (int j = 0; j < this->mWidth_; j++)
        {
            if (this->matrix_[i][j] != ' ')
            {
                this->matrix_[i][j] = newSymbol;
            }
        }
    }
}

void Block::setMatrix(vector<vector<char>> mat, int mHeight, int mWidth)
{
    this->matrix_ = mat;
    this->mHeight_ = mHeight;
    this->mWidth_ = mWidth;

    // Recalculate the block size
    // as it may have changed
    this->calcBlockSize();
}

void Block::setPos(pair<int, int> pos)
{
    this->coords_ = pos;
}

// Helper methods

// Returns true if the row h is empty
bool Block::isRowEmpty(int h) const
{
    for (int j = 0; j < this->matrix_[h].size(); j++)
    {
        if (this->matrix_[h][j] != ' ')
        {
            return false;
        }
    }
    return true;
};

// Returns true if the col w is empty
bool Block::isColEmpty(int w) const
{
    for (int i = 0; i < this->matrix_.size(); i++)
    {
        if (this->matrix_[i][w] != ' ')
        {
            return false;
        }
    }
    return true;
};

// Calculate the block size from the matrix
void Block::calcBlockSize()
{
    // Go through all the rows from the bottom until a non empty row is found
    // if all the rows are empty, then the height is 0
    this->blockHeight_ = 0;

    for (int i = this->mHeight_ - 1; i >= 0; i--)
    {
        if (!isRowEmpty(i))
        {
            this->blockHeight_ = i + 1;
            break;
        }
    }

    // Go through all the cols from the right until a non empty col is found
    // if all the col are empty, then the width is 0
    this->blockWidth_ = 0;
    for (int j = this->mWidth_ - 1; j >= 0; j--)
    {
        if (!isColEmpty(j))
        {
            this->blockWidth_ = j + 1;
            break;
        }
    }
}

void Block::removeRow(int h)
{
    // Remove the row by moving up all the following rows
    for (int i = h; i < this->mHeight_ - 1; i++)
    {
        for (int j = 0; j < this->mWidth_; j++)
        {
            this->matrix_[i][j] = this->matrix_[i + 1][j];
        }
    }

    // Clear the bottom row as moved everything up from h by 1
    for (int j = 0; j < this->mWidth_; j++)
    {
        this->matrix_[this->mHeight_ - 1][j] = ' ';
    }
};

void Block::removeCol(int w)
{
    // Remove the col by moving left all the following cols
    for (int j = w; j < this->mWidth_ - 1; j++)
    {
        for (int i = 0; i < this->mHeight_; i++)
        {
            this->matrix_[i][j] = this->matrix_[i][j + 1];
        }
    }

    // Clear the last col as moved everything left from w by 1
    for (int i = 0; i < this->mHeight_; i++)
    {
        this->matrix_[i][this->mWidth_ - 1] = ' ';
    }
};

void Block::removeHorizWhitespace()
{
    int row = 0;
    int timesRemoved = 1;

    // Check each row to see if it's empty and remove it
    // since once we remove, we also move the following rows up,
    // check the same row again to see if its empty
    while (row < this->mHeight_)
    {
        if (isRowEmpty(row) && timesRemoved < this->mHeight_)
        {
            removeRow(row);
            timesRemoved += 1;
        }
        else
        {
            row += 1;
            timesRemoved = 0;
        }
    }
}

void Block::removeVertWhitespace()
{
    int col = 0;
    int timesRemoved = 1;

    // Check each column to see if it's empty and remove it
    // since once we remove, we also move the following cols left,
    // check the same column again to see if its empty
    while (col < this->mWidth_)
    {
        if (isColEmpty(col) && timesRemoved < this->mWidth_)
        {
            removeCol(col);
            timesRemoved += 1;
        }
        else
        {
            col += 1;
            timesRemoved = 0;
        }
    }
}

// Applies a inplace matrix clockwise rotation
void Block::rotateClockwise()
{
    int N = this->mWidth_;

    for (int i = 0; i < N / 2; i++)
    {
        for (int j = i; j < N - i - 1; j++)
        {
            // Store current cell as temp
            int temp = this->matrix_[i][j];

            // Move cells from the top to right
            this->matrix_[i][j] = this->matrix_[N - 1 - j][i];

            // Move cells from the right to bottom
            this->matrix_[N - 1 - j][i] = this->matrix_[N - 1 - i][N - 1 - j];

            // Move cells from the bottom to left
            this->matrix_[N - 1 - i][N - 1 - j] = this->matrix_[j][N - 1 - i];

            // Assign temp to right
            this->matrix_[j][N - 1 - i] = temp;
        }
    }
};

// Applies a inplace matrix counterclockwise rotation
void Block::rotateCounterclockwise()
{
    int N = this->mWidth_;

    for (int i = 0; i < N / 2; i++)
    {
        for (int j = i; j < N - i - 1; j++)
        {
            // Store current cell as temp
            int temp = this->matrix_[i][j];

            // Move cells from the top to left
            this->matrix_[i][j] = this->matrix_[j][N - 1 - i];

            // Move values from the left to bottom
            this->matrix_[j][N - 1 - i] = this->matrix_[N - 1 - i][N - 1 - j];

            // Move values from the bottom to right
            this->matrix_[N - 1 - i][N - 1 - j] = this->matrix_[N - 1 - j][i];

            // Assign temp to left
            this->matrix_[N - 1 - j][i] = temp;
        }
    }
};

// Output operator to print the Block (i.e. it's cells)
// Does not print the entire box (matrix), only the rows
// that are needed
ostream &operator<<(ostream &sout, const Block &b)
{
    vector<vector<char>> cells = b.getCells();
    for (int i = 0; i < cells.size(); i++)
    {
        string row;
        bool emptyRow = true;
        for (int j = 0; j < cells[i].size(); j++)
        {
            if (cells[i][j] != ' ')
            {
                emptyRow = false;
            }
            row += cells[i][j];
        }
        if (!emptyRow)
        {
            sout << row << endl;
        }
    }
    return sout;
};

// Returns true if the blocks are the same
bool operator==(const Block &lhs, const Block &rhs)
{

    const pair<int, int> lhsPos = lhs.getPos();
    const pair<int, int> rhsPos = rhs.getPos();

    // If the blocks are of different type return false
    if (lhs.getBlockType() != rhs.getBlockType())
    {
        return false;
    }

    // If the blocks are in different positons, return false
    if (lhsPos.first != rhsPos.first || lhsPos.second != rhsPos.second)
    {
        return false;
    }

    // If the block box size or block size do not match, return false
    if (lhs.getBoxHeight() != rhs.getBoxHeight() || lhs.getBoxWidth() != rhs.getBoxWidth())
    {
        return false;
    }
    if (lhs.getBlockHeight() != rhs.getBlockHeight() || lhs.getBlockWidth() != rhs.getBlockWidth())
    {
        return false;
    }

    // Finally, compare individual cells
    const vector<vector<char>> lhsCells = lhs.getCells();
    const vector<vector<char>> rhsCells = rhs.getCells();

    for (int i = 0; i < lhs.getBoxHeight(); i++)
    {
        for (int j = 0; j < lhs.getBoxWidth(); j++)
        {
            if (lhsCells[i][j] != rhsCells[i][j])
            {
                return false;
            }
        }
    }

    return true;
};

// Getters

vector<vector<char>> Block::getCells() const
{
    return this->matrix_;
};

int Block::getBoxHeight() const
{
    return this->mHeight_;
};

int Block::getBoxWidth() const
{
    return this->mWidth_;
};

int Block::getBlockHeight() const
{
    return this->blockHeight_;
};

int Block::getBlockWidth() const
{
    return this->blockWidth_;
};

BlockType Block::getBlockType() const
{
    return this->type_;
};

pair<int, int> Block::getPos() const
{
    return this->coords_;
};

bool Block::isPlayable() const
{
    return this->playable_;
}

int Block::getLevelGen() const
{
    return this->level_;
};
