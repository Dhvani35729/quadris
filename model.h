#ifndef MVC_MODEL_H
#define MVC_MODEL_H

#include "subject.h"
#include "controller.h"
#include "level.h"
#include "score.h"
#include "board.h"

#include <vector>

// Model
class Model : public Subject
{
public:
    Model(int, int);
    ~Model();

    bool checkGameOver();
    void startGame();
    void playRound(Command);
    void resetGame(Command);
    void setLevel(Level *);
    Score getScore();

private:
    Level *level_;
    Board *board_;
    Score *score_;
};

#endif