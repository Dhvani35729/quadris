#include "level.h"

#include <iostream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <time.h>

// TODO: Do this.
// #define START_ROW 3
// #define START_COL 0

using namespace std;

std::shared_ptr<Block> Level::addSpecialBlock(int blockCount)
{
    return nullptr;
};

BlockType Level::getFromSequence()
{
    BlockType type = this->blockSequence_[this->curIndex_];
    this->curIndex_ += 1;

    if (this->curIndex_ == this->blockSequence_.size())
    {
        this->curIndex_ = 0;
    }

    return type;
};

void Level::setSequenceFile(std::string f)
{
    std::string blockChars = "IJLOSZT";

    this->fileName_ = f;

    ifstream in(fileName_);

    string sequence(
        (std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());

    this->blockSequence_.clear();

    for (char &c : sequence)
    {
        if (c != ' ')
        {
            this->blockSequence_.push_back((BlockType)blockChars.find(c));
        }
    }
    this->curIndex_ = 0;
};

void Level::setIsRandom(bool r)
{
    this->isRandom_ = r;
};

LevelZero::LevelZero(std::string f)
{
    std::cout << "LevelZero born" << std::endl;
    this->levelNum_ = 0;
    Level::setSequenceFile(f);
    this->isRandom_ = false;
}

LevelOne::LevelOne()
{
    // Use current time as seed for random generator
    srand(time(0));
    std::cout << "LevelOne born" << std::endl;
    this->levelNum_ = 1;
    this->isRandom_ = true;
}

LevelTwo::LevelTwo()
{
    // Use current time as seed for random generator
    srand(time(0));
    std::cout << "LevelTwo born" << std::endl;
    this->levelNum_ = 2;
    this->isRandom_ = true;
}

LevelThree::LevelThree()
{
    // Use current time as seed for random generator
    srand(time(0));
    std::cout << "LevelThree born" << std::endl;
    this->levelNum_ = 3;
    this->isRandom_ = true;
}

LevelFour::LevelFour()
{
    // Use current time as seed for random generator
    srand(time(0));
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

void LevelZero::setSequenceFile(std::string f)
{
    // Do nothing
}

std::shared_ptr<Block> LevelZero::nextBlock()
{
    BlockType type = getFromSequence();
    std::shared_ptr<Block> newBlock = std::make_shared<Block>(type, std::make_pair(3, 0), this->levelNum_, true);

    return newBlock;
}

std::shared_ptr<Block> LevelOne::nextBlock()
{
    BlockType type;
    int blkInd = rand() % 6;
    if (blkInd == 5)
    {
        type = T_BLK;
    }
    else if (blkInd == 4)
    {
        blkInd = rand() % 2;
        blkInd = blkInd == 0 ? S_BLK : Z_BLK;
        type = (BlockType)blkInd;
    }
    else
    {
        type = (BlockType)blkInd;
    }

    std::shared_ptr<Block> newBlock = std::make_shared<Block>(type, std::make_pair(3, 0), this->levelNum_, true);

    return newBlock;
}

std::shared_ptr<Block> LevelTwo::nextBlock()
{
    int blkInd = rand() % NUM_BLKS;

    BlockType type = (BlockType)blkInd;

    std::shared_ptr<Block> newBlock = std::make_shared<Block>(type, std::make_pair(3, 0), this->levelNum_, true);

    return newBlock;
}

std::shared_ptr<Block> LevelThree::nextBlock()
{
    BlockType type;

    if (this->isRandom_)
    {
        int blkInd = rand() % 9;
        if (blkInd == 4)
        {
            type = T_BLK;
        }
        else if (blkInd == 5 || blkInd == 6)
        {
            type = S_BLK;
        }
        else if (blkInd == 7 || blkInd == 8)
        {
            type = Z_BLK;
        }
        else
        {
            type = (BlockType)blkInd;
        }
    }
    else
    {
        type = getFromSequence();
    }

    std::shared_ptr<Block> newBlock = std::make_shared<HeavyBlock>(type, std::make_pair(3, 0), this->levelNum_, true);

    return newBlock;
}

std::shared_ptr<Block> LevelFour::nextBlock()
{
    BlockType type;

    if (this->isRandom_)
    {
        int blkInd = rand() % 9;
        if (blkInd == 4)
        {
            type = T_BLK;
        }
        else if (blkInd == 5 || blkInd == 6)
        {
            type = S_BLK;
        }
        else if (blkInd == 7 || blkInd == 8)
        {
            type = Z_BLK;
        }
        else
        {
            type = (BlockType)blkInd;
        }
    }
    else
    {
        type = getFromSequence();
    }

    std::shared_ptr<Block> newBlock = std::make_shared<HeavyBlock>(type, std::make_pair(3, 0), this->levelNum_, true);

    return newBlock;
}

std::shared_ptr<Block> LevelFour::addSpecialBlock(int blockCount)
{
    if (blockCount != 0 && blockCount % 5 == 0)
    {
        std::shared_ptr<Block> newBlock = std::make_shared<StarBlock>(std::make_pair(3, 5), this->levelNum_, false);
        return newBlock;
    }
    else
    {
        return nullptr;
    }
};
