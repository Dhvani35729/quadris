#include "block.h"

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

Block::Block(BlockType t, std::pair<int, int> pos, int level)
{
    this->type_ = t;
    this->coords_ = pos;
    this->level_ = level;
    aliveFor_ = 0;
    std::cout << "Block born" << std::endl;

    this->mWidth_ = 3;
    this->mHeight_ = 3;
    matrix_.resize(this->mHeight_, std::vector<char>(this->mWidth_, ' '));

    if (t == I_BLK)
    {
        this->mWidth_ = 4;
        this->mHeight_ = 4;
        this->matrix_.clear();
        this->matrix_.resize(this->mHeight_, std::vector<char>(this->mWidth_, ' '));
        matrix_[0][0] = 'I';
        matrix_[0][1] = 'I';
        matrix_[0][2] = 'I';
        matrix_[0][3] = 'I';
        this->blockHeight_ = 1;
        this->blockWidth_ = 4;
    }
    else if (t == J_BLK)
    {
        matrix_[0][0] = 'J';
        matrix_[1][0] = 'J';
        matrix_[1][1] = 'J';
        matrix_[1][2] = 'J';
        this->blockHeight_ = 2;
        this->blockWidth_ = 3;
    }
    else if (t == L_BLK)
    {
        matrix_[0][2] = 'L';
        matrix_[1][0] = 'L';
        matrix_[1][1] = 'L';
        matrix_[1][2] = 'L';
        this->blockHeight_ = 2;
        this->blockWidth_ = 3;
    }
    else if (t == O_BLK)
    {
        matrix_[0][0] = 'O';
        matrix_[0][1] = 'O';
        matrix_[1][0] = 'O';
        matrix_[1][1] = 'O';
        this->blockHeight_ = 2;
    }
    else if (t == S_BLK)
    {
        matrix_[0][1] = 'S';
        matrix_[0][2] = 'S';
        matrix_[1][0] = 'S';
        matrix_[1][1] = 'S';
        this->blockHeight_ = 2;
        this->blockWidth_ = 3;
    }
    else if (t == Z_BLK)
    {
        matrix_[0][0] = 'Z';
        matrix_[0][1] = 'Z';
        matrix_[1][1] = 'Z';
        matrix_[1][2] = 'Z';
        this->blockHeight_ = 2;
        this->blockWidth_ = 3;
    }
    else if (t == T_BLK)
    {
        matrix_[0][0] = 'T';
        matrix_[0][1] = 'T';
        matrix_[0][2] = 'T';
        matrix_[1][1] = 'T';
        this->blockHeight_ = 2;
        this->blockWidth_ = 3;
    }
};

Block::~Block()
{
    std::cout << "Block died" << std::endl;
};

std::vector<std::vector<char>> Block::getCells()
{
    return this->matrix_;
};

int Block::getBoxWidth()
{
    return this->mWidth_;
};

int Block::getBoxHeight()
{
    return this->mHeight_;
};

std::pair<int, int> Block::getPos()
{
    return this->coords_;
};

Block Block::moveBlock(Command c)
{
    // Copy current block
    Block movedBlock{*this};

    if (c == LEFT)
    {
        movedBlock.coords_.second -= 1;
    }
    else if (c == RIGHT)
    {
        movedBlock.coords_.second += 1;
    }
    else if (c == DOWN)
    {
        movedBlock.coords_.first += 1;
    }
    return movedBlock;
};

void print(std::vector<std::vector<char>> &mat)
{
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[i].size(); j++)
        {
            cout << mat[i][j];
        }
        cout << endl;
    }
}

bool isRowEmpty(int h, std::vector<std::vector<char>> &mat)
{
    for (int j = 0; j < mat[h].size(); j++)
    {
        if (mat[h][j] != ' ')
        {
            return false;
        }
    }
    return true;
};

bool isColEmpty(int w, std::vector<std::vector<char>> &mat)
{
    for (int i = 0; i < mat.size(); i++)
    {
        if (mat[i][w] != ' ')
        {
            return false;
        }
    }
    return true;
};

void removeRow(int h, std::vector<std::vector<char>> &mat)
{
    // Move everything up by 1
    // cout << "Before" << endl;
    // print(mat);
    for (int i = h; i < mat.size() - 1; i++)
    {
        for (int j = 0; j < mat[i].size(); j++)
        {
            mat[i][j] = mat[i + 1][j];
        }
    }
    // cout << "After" << endl;
    // print(mat);

    // Clear bottom row
    for (int j = 0; j < mat[mat.size() - 1].size(); j++)
    {
        mat[mat.size() - 1][j] = ' ';
    }
};

void removeCol(int w, std::vector<std::vector<char>> &mat)
{
    // Move everything left by 1
    // cout << "Before" << endl;
    // print(mat);
    for (int j = w; j < mat[w].size() - 1; j++)
    {
        for (int i = 0; i < mat.size(); i++)
        {
            mat[i][j] = mat[i][j + 1];
        }
    }
    // cout << "After" << endl;
    // print(mat);

    // Clear right col
    for (int i = 0; i < mat.size(); i++)
    {
        mat[i][mat[w].size() - 1] = ' ';
    }
};

void Block::removeWhitespace()
{
    std::vector<std::vector<char>> &mat = this->matrix_;
    // Remove empty horizontal rows by moving up

    int row = 0;
    // cout << "Remove line?: " << row << endl;
    // print(mat);
    while (isRowEmpty(row, mat))
    {
        removeRow(row, mat);
    }

    int col = 0;
    while (isColEmpty(col, mat))
    {
        removeCol(col, mat);
    }
}

void Block::calcBlockSize()
{
    this->blockHeight_ = this->matrix_.size();

    for (int i = this->matrix_.size() - 1; i >= 0; i--)
    {
        if (!isRowEmpty(i, this->matrix_))
        {
            this->blockHeight_ = i + 1;
            break;
        }
    }

    this->blockWidth_ = 0;
    for (int j = this->matrix_[0].size() - 1; j >= 0; j--)
    {
        if (!isColEmpty(j, this->matrix_))
        {
            this->blockWidth_ = j + 1;
            break;
        }
    }
}

void Block::rotateClockwise()
{
    std::vector<std::vector<char>> &mat = this->matrix_;
    int N = this->mWidth_;

    // Consider all squares one by one
    for (int x = 0; x < N / 2; x++)
    {
        // Consider elements in group
        // of 4 in current square
        for (int y = x; y < N - x - 1; y++)
        {
            // Store current cell in
            // temp variable
            int temp = mat[x][y];

            // Move values from top to right
            mat[x][y] = mat[N - 1 - y][x];

            // Move values from right to bottom
            mat[N - 1 - y][x] = mat[N - 1 - x][N - 1 - y];

            // Move values from bottom to left
            mat[N - 1 - x][N - 1 - y] = mat[y][N - 1 - x];

            // Assign temp to right
            mat[y][N - 1 - x] = temp;
        }
    }
};

void Block::rotateCounterclockwise()
{
    std::vector<std::vector<char>> &mat = this->matrix_;
    int N = this->mWidth_;

    // Consider all squares one by one
    for (int x = 0; x < N / 2; x++)
    {
        // Consider elements in group
        // of 4 in current square
        for (int y = x; y < N - x - 1; y++)
        {
            // Store current cell in
            // temp variable
            int temp = mat[x][y];

            // Move values from right to top
            mat[x][y] = mat[y][N - 1 - x];

            // Move values from bottom to right
            mat[y][N - 1 - x] = mat[N - 1 - x][N - 1 - y];

            // Move values from left to bottom
            mat[N - 1 - x][N - 1 - y] = mat[N - 1 - y][x];

            // Assign temp to left
            mat[N - 1 - y][x] = temp;
        }
    }
};

// Only supports rotations on square matrix
Block Block::rotateBlock(Command c)
{
    // Copy current block
    Block rotatedBlock{*this};

    // Prev top left corner
    pair<int, int> prevTCorner = rotatedBlock.getPos();
    // cout << "Old T Corner: " << prevTCorner.first << ":" << prevTCorner.second << endl;
    // Prev bottom left corner
    pair<int, int> prevBCorner = make_pair(prevTCorner.first + rotatedBlock.getBlockHeight() - 1, prevTCorner.second);
    // cout << "Old B Corner: " << prevBCorner.first << ":" << prevBCorner.second << endl;
    // cout << "Old height: " << rotatedBlock.getBlockHeight() << endl;

    if (c == COUNTERCLOCKWISE)
    {

        rotatedBlock.rotateCounterclockwise();
        rotatedBlock.removeWhitespace();
        rotatedBlock.calcBlockSize();
    }
    else if (c == CLOCKWISE)
    {
        rotatedBlock.rotateClockwise();
        rotatedBlock.removeWhitespace();
        rotatedBlock.calcBlockSize();
    }
    else
    {
        //  Assert should not be here
    }

    // New bottom left corner
    // cout << "New height: " << rotatedBlock.getBlockHeight() << endl;
    pair<int, int> newBCorner = make_pair(prevTCorner.first + rotatedBlock.getBlockHeight() - 1, prevTCorner.second);
    // cout << "New B Corner: " << newBCorner.first << ":" << newBCorner.second << endl;

    // New top left corner
    int diff = newBCorner.first - prevBCorner.first;
    pair<int, int> newTCorner = make_pair(prevTCorner.first - diff, prevTCorner.second);
    // cout << "New T Corner: " << newTCorner.first << ":" << newTCorner.second << endl;

    rotatedBlock.setPos(newTCorner);

    return rotatedBlock;
};

int Block::getBlockHeight()
{
    return this->blockHeight_;
};

int Block::getBlockWidth()
{
    return this->blockWidth_;
};

void Block::setMatrix(std::vector<std::vector<char>> m)
{
    this->matrix_ = m;
    this->calcBlockSize();
}

void Block::setPos(std::pair<int, int> m)
{
    this->coords_ = m;
}