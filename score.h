#ifndef SCORE_H
#define SCORE_H

// Score
class Score
{
public:
    Score();
    ~Score();
    int getScore();
    int getHiScore();
    void setScore(int);

private:
    int currScore_;
    int hiScore_;
};

#endif