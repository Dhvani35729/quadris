#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"

#include <string>
#include <memory>

// Level
class Level
{
public:
    virtual ~Level();
    virtual std::shared_ptr<Block> nextBlock() = 0;
    virtual std::shared_ptr<Block> addSpecialBlock(int);
    int getLevelNum() const;

protected:
    int levelNum_;
};

class LevelZero : public Level
{
public:
    LevelZero(std::string);
    ~LevelZero();
    std::shared_ptr<Block> nextBlock() override;

private:
    std::string fileName_;
    std::vector<char> blockSequence_;
    int curIndex;
};

class LevelOne : public Level
{
public:
    LevelOne();
    ~LevelOne();
    std::shared_ptr<Block> nextBlock() override;

private:
};

class LevelTwo : public Level
{
public:
    LevelTwo();
    ~LevelTwo();
    std::shared_ptr<Block> nextBlock() override;

private:
};

class LevelThree : public Level
{
public:
    LevelThree();
    ~LevelThree();
    std::shared_ptr<Block> nextBlock() override;

private:
    bool isRandom_;
};

class LevelFour : public Level
{
public:
    LevelFour();
    ~LevelFour();
    std::shared_ptr<Block> nextBlock() override;
    std::shared_ptr<Block> addSpecialBlock(int) override;

private:
    bool isRandom_;
};

#endif