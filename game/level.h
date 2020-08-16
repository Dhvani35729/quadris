#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <memory>

#include "../blocks/block.h"

// Global seed for the randomness of block generation
extern int seed;

// Level - Strategy Pattern
// Level is an abstract class
class Level
{
public:
    // default constructor
    Level();

    // destructor
    virtual ~Level();

    // Pure virtual - nextBlock method (Strategy method)
    // Returns a new block to be played
    virtual std::shared_ptr<Block> nextBlock() = 0;

    // Takes in the number of blocks
    // placed since the last clear
    // Returns a special block to be played
    // By default, returns no blocks, but can be overriden
    virtual std::shared_ptr<Block> addSpecialBlock(int blockCount);

    // Set the file name to take the sequence from
    // Updates the block sequence vector
    virtual void setSequenceFile(std::string fileName);

    virtual void setIsRandom(bool r);

    // Getters
    int getLevelNum() const;

protected:
    // Helper method to get the next block
    // from the sequence
    BlockType getFromSequence();

    // Every level has a level number
    // Every level also has a bool representing
    // if it is random or not
    // Anytime a level is non random, it will
    // use the block sequence instead which
    // is generated from the file
    // NOTE: LevelZero is an exception to this,
    // but is only used for testing and thus we use this design.
    int levelNum_;
    std::string fileName_;

    std::vector<BlockType> blockSequence_;
    int curIndex_;

    bool isRandom_;
};

// LevelZero
// Derived from Level
// Note: Only used for testing purposes
class LevelZero : public Level
{
public:
    // constructor
    LevelZero(std::string fileName);

    // destructor
    ~LevelZero();

    // Concrete Strategy method
    std::shared_ptr<Block> nextBlock() override;

    // SetSequenceFile is overriden to an empty function
    // as this is a special level only for testing, and instead
    // uses the sequence.txt or provided -scriptfile
    void setSequenceFile(std::string) override;

private:
};

// LevelOne
// Derived from Level
class LevelOne : public Level
{
public:
    // default constructor
    LevelOne();

    // destructor
    ~LevelOne();

    // Concrete Strategy method
    std::shared_ptr<Block> nextBlock() override;
};

// LevelTwo
// Derived from Level
class LevelTwo : public Level
{
public:
    // default constructor
    LevelTwo();

    // destructor
    ~LevelTwo();

    // Concrete Strategy method
    std::shared_ptr<Block> nextBlock() override;
};

// LevelThree
// Derived from Level
class LevelThree : public Level
{
public:
    // default constructor
    LevelThree();

    // destructor
    ~LevelThree();

    // Concrete Strategy method
    std::shared_ptr<Block> nextBlock() override;
};

// LevelFour
// Derived from Level
class LevelFour : public Level
{
public:
    // default constructor
    LevelFour();

    // destructor
    ~LevelFour();

    // Concrete Strategy method
    std::shared_ptr<Block> nextBlock() override;

    // Returns a star block (1x1) every time a multiple of
    // 5 blocks are placed without clearing at least one row
    std::shared_ptr<Block> addSpecialBlock(int blockCount) override;
};

#endif