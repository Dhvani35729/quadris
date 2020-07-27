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
        matrix_[1][0] = 'I';
        matrix_[1][1] = 'I';
        matrix_[1][2] = 'I';
        matrix_[1][3] = 'I';
    }
    else if (t == J_BLK)
    {
        matrix_[0][0] = 'J';
        matrix_[1][0] = 'J';
        matrix_[1][1] = 'J';
        matrix_[1][2] = 'J';
    }
    else if (t == L_BLK)
    {
        matrix_[0][2] = 'L';
        matrix_[1][0] = 'L';
        matrix_[1][1] = 'L';
        matrix_[1][2] = 'L';
    }
    else if (t == O_BLK)
    {
        matrix_[0][0] = 'O';
        matrix_[0][1] = 'O';
        matrix_[1][0] = 'O';
        matrix_[1][1] = 'O';
    }
    else if (t == S_BLK)
    {
        matrix_[0][1] = 'S';
        matrix_[0][2] = 'S';
        matrix_[1][0] = 'S';
        matrix_[1][1] = 'S';
    }
    else if (t == Z_BLK)
    {
        matrix_[0][0] = 'Z';
        matrix_[0][1] = 'Z';
        matrix_[1][1] = 'Z';
        matrix_[1][2] = 'Z';
    }
    else if (t == T_BLK)
    {
        matrix_[0][0] = 'T';
        matrix_[0][1] = 'T';
        matrix_[0][2] = 'T';
        matrix_[1][1] = 'T';
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

bool Block::moveBlock(Command)
{
    return true;
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

bool Block::rotateBlock(Command c)
{
    std::vector<std::vector<char>> mat = this->matrix_;
    cout << "Initial" << endl;
    print(mat);
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

    cout << "Rotate" << endl;
    print(mat);
};

void Block::dropBlock(int h)
{
    this->coords_.first = h;
};