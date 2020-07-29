#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"

#include <string>

// Level
// TODO: Pure virtual check
class Level
{
public:
    Level();
    virtual ~Level();
    virtual Block *nextBlock() = 0;
    int getLevelNum() const;

protected:
    int levelNum_;
};

class LevelZero : public Level
{
public:
    LevelZero(std::string);
    ~LevelZero();
    Block *nextBlock() override;

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
    Block *nextBlock() override;

private:
};

class LevelTwo : public Level
{
public:
    LevelTwo();
    ~LevelTwo();
    Block *nextBlock() override;

private:
};

#endif