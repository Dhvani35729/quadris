#include "level.h"

#include <iostream>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

Level::Level()
{
    std::cout << "Level born" << std::endl;
    this->levelNum_ = -1;
}

Level::~Level()
{
    std::cout << "Level died" << std::endl;
}

LevelTwo::LevelTwo()
{
    std::cout << "LevelTwo born" << std::endl;
    this->levelNum_ = 2;
}

LevelZero::LevelZero(std::string f)
{
    std::cout << "LevelZero born" << std::endl;
    this->fileName_ = f;
    this->levelNum_ = 0;

    ifstream in(fileName_);

    string sequence(
        (std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());

    for (char &c : sequence)
    {
        if (c != ' ')
        {
            this->blockSequence_.push_back(c);
        }
    }

    this->curIndex = 0;
}

LevelZero::~LevelZero()
{
    std::cout << "LevelZero died" << std::endl;
}

LevelTwo::~LevelTwo()
{
    std::cout << "LevelTwo died" << std::endl;
}

int Level::getLevelNum() const
{
    return this->levelNum_;
}

Block *LevelZero::nextBlock()
{
    char nextBlock = this->blockSequence_[this->curIndex];
    BlockType type;
    if (nextBlock == 'I')
    {
        type = I_BLK;
    }
    else if (nextBlock == 'J')
    {
        type = J_BLK;
    }
    else if (nextBlock == 'L')
    {
        type = L_BLK;
    }
    else if (nextBlock == 'O')
    {
        type = O_BLK;
    }
    else if (nextBlock == 'S')
    {
        type = S_BLK;
    }
    else if (nextBlock == 'Z')
    {
        type = Z_BLK;
    }
    else if (nextBlock == 'T')
    {
        type = T_BLK;
    }
    else
    {
        type = BAD_BLK;
    }

    if (type != BAD_BLK)
    {
        Block *newBlock = new Block(type, std::make_pair(3, 0), this->levelNum_);
        this->curIndex += 1;

        if (this->curIndex == this->blockSequence_.size())
        {
            this->curIndex = 0;
        }
        return newBlock;
    }
    return nullptr;
}

Block *LevelTwo::nextBlock()
{
    int blkInd = rand() % BAD_BLK;
    cout << "Random block: " << blkInd << endl;
    BlockType type = (BlockType)blkInd;

    Block *newBlock = new Block(type, std::make_pair(3, 0), this->levelNum_);

    return newBlock;
}