#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"

#include <string>

// Level
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

#endif