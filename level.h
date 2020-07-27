#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"

// Level
class Level
{
public:
    Level();
    ~Level();
    virtual Block *nextBlock() const = 0;
};

class LevelZero : public Level
{
public:
    Block *nextBlock() const override;
};

#endif