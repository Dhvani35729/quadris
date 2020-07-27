#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"

// Level
class Level
{
public:
    Level();
    virtual ~Level();
    virtual Block *nextBlock() const = 0;
    int getLevelNum() const;

protected:
    int levelNum_;
};

class LevelZero : public Level
{
public:
    LevelZero();
    ~LevelZero();
    Block *nextBlock() const override;
};

#endif