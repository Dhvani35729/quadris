#include "score.h"

#include <iostream>

Score::Score()
{
    currScore_ = 0;
    hiScore_ = 0;
    std::cout << "Score born" << std::endl;
};

Score::~Score()
{
    std::cout << "Score died" << std::endl;
};

int Score::getScore()
{
    return currScore_;
};

int Score::getHiScore()
{
    return hiScore_;
};

void Score::setScore(int newScore)
{
    if (newScore > hiScore_)
    {
        hiScore_ = newScore;
    }
    currScore_ = newScore;
};