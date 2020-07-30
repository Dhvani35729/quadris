#include "level.h"

#include <iostream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <memory>

using namespace std;

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

LevelOne::LevelOne()
{
    std::cout << "LevelOne born" << std::endl;
    this->levelNum_ = 1;
}

LevelTwo::LevelTwo()
{
    std::cout << "LevelTwo born" << std::endl;
    this->levelNum_ = 2;
}

LevelThree::LevelThree()
{
    std::cout << "LevelThree born" << std::endl;
    this->levelNum_ = 3;
    this->isRandom_ = true;
}

LevelFour::LevelFour()
{
    std::cout << "LevelFour born" << std::endl;
    this->levelNum_ = 4;
    this->isRandom_ = true;
}

Level::~Level()
{
    std::cout << "Level died" << std::endl;
}

LevelZero::~LevelZero()
{
    std::cout << "LevelOne died" << std::endl;
}

LevelOne::~LevelOne()
{
    std::cout << "LevelOne died" << std::endl;
}

LevelTwo::~LevelTwo()
{
    std::cout << "LevelTwo died" << std::endl;
}

LevelThree::~LevelThree()
{
    std::cout << "LevelThree died" << std::endl;
}

LevelFour::~LevelFour()
{
    std::cout << "LevelFour died" << std::endl;
}

int Level::getLevelNum() const
{
    return this->levelNum_;
}

std::shared_ptr<Block> LevelZero::nextBlock()
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
        type = NUM_BLKS;
    }

    if (type != NUM_BLKS)
    {
        std::shared_ptr<Block> newBlock = std::make_shared<Block>(type, std::make_pair(3, 0), this->levelNum_);
        this->curIndex += 1;

        if (this->curIndex == this->blockSequence_.size())
        {
            this->curIndex = 0;
        }
        return newBlock;
    }
    return nullptr;
}

std::shared_ptr<Block> LevelOne::nextBlock()
{
    // TODO: Fix probability
    std::shared_ptr<Block> newBlock = std::make_shared<Block>(I_BLK, std::make_pair(3, 0), this->levelNum_);

    return newBlock;
}

std::shared_ptr<Block> LevelTwo::nextBlock()
{
    int blkInd = rand() % NUM_BLKS;
    // cout << "Random block: " << blkInd << endl;
    BlockType type = (BlockType)blkInd;

    std::shared_ptr<Block> newBlock = std::make_shared<Block>(type, std::make_pair(3, 0), this->levelNum_);

    return newBlock;
}

std::shared_ptr<Block> LevelThree::nextBlock()
{
    // TODO: Fix probability
    int blkInd = rand() % NUM_BLKS;
    // cout << "Random block: " << blkInd << endl;
    BlockType type = (BlockType)blkInd;

    std::shared_ptr<Block> newBlock = std::make_shared<HeavyBlock>(type, std::make_pair(3, 0), this->levelNum_);

    return newBlock;
}

std::shared_ptr<Block> LevelFour::nextBlock()
{
    // TODO: Fix probability
    int blkInd = rand() % NUM_BLKS;
    // cout << "Random block: " << blkInd << endl;
    BlockType type = (BlockType)blkInd;

    // std::shared_ptr<Block> newBlock = std::make_shared<HeavyBlock>(type, std::make_pair(3, 0), this->levelNum_);

    std::shared_ptr<Block> newBlock = std::make_shared<StarBlock>(std::make_pair(3, 0), this->levelNum_);

    return newBlock;
}
