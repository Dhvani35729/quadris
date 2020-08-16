#ifndef SCORE_H
#define SCORE_H

// Score
class Score
{
public:
    // default constructor
    Score();

    // destructor
    ~Score();

    // Adds amount to current score
    // and updates the high score
    void addScore(int amount);

    // Reset current score to zero
    void resetScore();

    // Getters
    int getScore() const;
    int getHiScore() const;

private:
    // Current Score
    int currScore_;

    // High Score
    int hiScore_;
};

#endif