#include "score.h"

// default constructor
Score::Score()
{
    // Start with a score of 0
    this->currScore_ = 0;
    this->hiScore_ = 0;
};

// destructor
Score::~Score(){};

// Adds amount to current score
// and updates the high score
void Score::addScore(int amount)
{
    int newScore = this->currScore_ + amount;
    if (newScore > this->hiScore_)
    {
        this->hiScore_ = newScore;
    }
    this->currScore_ = newScore;
};

// Reset current score to zero
void Score::resetScore()
{
    this->currScore_ = 0;
}

// Getters

int Score::getScore() const
{
    return this->currScore_;
};

int Score::getHiScore() const
{
    return this->hiScore_;
};