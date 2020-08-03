#include <iostream>
#include <fstream>
#include <cstdlib>

#include <memory>

#include "level.h"
#include "heavyblock.h"
#include "starblock.h"

#define START_ROW 3
#define START_COL 0
#define CENTER_COL 5

using namespace std;

// Global seed
int seed = 1;

// default constructor
Level::Level()
{
    // Set the seed
    srand(seed);
}

// destructor
Level::~Level() {}

// By default, returns no blocks, but can be overriden as needed
shared_ptr<Block> Level::addSpecialBlock(int blockCount)
{
    return nullptr;
};

// Set the file name to take the sequence from
// Updates the block sequence vector
void Level::setSequenceFile(string fileName)
{
    string blockChars = "IJLSZOT";

    this->fileName_ = fileName;

    // We turn a file separated by spaces into a string
    ifstream in(fileName_);

    string sequence(
        (istreambuf_iterator<char>(in)),
        istreambuf_iterator<char>());

    // We map each char to a BlockType
    // and add it to the sequence vector
    this->blockSequence_.clear();

    for (char &c : sequence)
    {
        if (c != ' ')
        {
            this->blockSequence_.push_back((BlockType)blockChars.find(c));
        }
    }

    // Start from index 0
    this->curIndex_ = 0;
};

void Level::setIsRandom(bool r)
{
    this->isRandom_ = r;
};

BlockType Level::getFromSequence()
{
    // Return the block at the current index
    BlockType type = this->blockSequence_[this->curIndex_];

    // Increment the index
    this->curIndex_ += 1;

    // Loop back once we are done
    if (this->curIndex_ == this->blockSequence_.size())
    {
        this->curIndex_ = 0;
    }

    return type;
};

// Getter

int Level::getLevelNum() const
{
    return this->levelNum_;
}

// LevelZero constructor
LevelZero::LevelZero(string fileName)
{
    this->levelNum_ = 0;
    Level::setSequenceFile(fileName);
    this->isRandom_ = false;
}

// LevelOne constructor
LevelOne::LevelOne()
{
    this->levelNum_ = 1;
    this->isRandom_ = true;
}

// LevelTwo constructor
LevelTwo::LevelTwo()
{
    this->levelNum_ = 2;
    this->isRandom_ = true;
}

// LevelThree constructor
LevelThree::LevelThree()
{
    this->levelNum_ = 3;
    this->isRandom_ = true;
}

// LevelFour constructor
LevelFour::LevelFour()
{
    this->levelNum_ = 4;
    this->isRandom_ = true;
}

// LevelZero destructor
LevelZero::~LevelZero() {}

// LevelOne destructor
LevelOne::~LevelOne() {}

// LevelTwo destructor
LevelTwo::~LevelTwo() {}

// LevelThree destructor
LevelThree::~LevelThree() {}

// LevelFour destructor
LevelFour::~LevelFour() {}

// Override the default implementation of sequence file
// As LevelZero is a special level, and uses a provided scriptfile
// Used only for testing
void LevelZero::setSequenceFile(string fileName) {}

// LevelZero - Concrete Strategy method
// Returns a block from the script file
shared_ptr<Block> LevelZero::nextBlock()
{
    BlockType type = getFromSequence();
    shared_ptr<Block> newBlock = make_shared<Block>(
        type, make_pair(START_ROW, START_COL), this->levelNum_, true);

    return newBlock;
}

// LevelOne - Concrete Strategy method
// Randomly choose a block with probabilities
// skewed such that S and Z blocks are selected with a
// probability of 1/12 each, and the other blocks
// are selected with a probability of 1/6 each
shared_ptr<Block> LevelOne::nextBlock()
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

    shared_ptr<Block> newBlock = make_shared<Block>(
        type, make_pair(START_ROW, START_COL), this->levelNum_, true);

    return newBlock;
}

// LevelTwo - Concrete Strategy method
// All blocks are selected with equal probability
shared_ptr<Block> LevelTwo::nextBlock()
{
    int blkInd = rand() % NUM_BLKS;

    BlockType type = (BlockType)blkInd;

    shared_ptr<Block> newBlock = make_shared<Block>(
        type, make_pair(START_ROW, START_COL), this->levelNum_, true);

    return newBlock;
}

// LevelThree - Concrete Strategy method
// If the level is random:
// Randomly choose a block with probabilities
// skewed such that S and Z blocks are selected with
// a probability of 2/9 each, and the other blocks
// are selected with a probability of 1/9 each
// If the level is not random:
// returns blocks in a sequence from a file
// Note: this level also generates heavy blocks
shared_ptr<Block> LevelThree::nextBlock()
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

    shared_ptr<Block> newBlock = make_shared<HeavyBlock>(
        type, make_pair(START_ROW, START_COL), this->levelNum_, true);

    return newBlock;
}

// LevelFour - Concrete Strategy method
// If the level is random:
// Same as level 3
// If the level is not random:
// returns blocks in a sequence from a file
// Note: this level also generates heavy blocks
shared_ptr<Block> LevelFour::nextBlock()
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

    shared_ptr<Block> newBlock = make_shared<HeavyBlock>(
        type, make_pair(START_ROW, START_COL), this->levelNum_, true);

    return newBlock;
}

// Returns a star block (1x1) every time a multiple of
// 5 blocks are placed without clearing at least one row
shared_ptr<Block> LevelFour::addSpecialBlock(int blockCount)
{
    if (blockCount != 0 && blockCount % 5 == 0)
    {
        // The Star Block will be placed in the centre column
        // and will also not be playable (i.e. dropped immediately)

        shared_ptr<Block> newBlock = make_shared<StarBlock>(
            make_pair(START_ROW, CENTER_COL), this->levelNum_, false);
        return newBlock;
    }
    else
    {
        return nullptr;
    }
};
