#ifndef MVC_MODEL_H
#define MVC_MODEL_H

#include "subject.h"
#include "controller.h"
#include "level.h"
#include "score.h"
#include "block.h"
#include "board.h"
#include "cell.h"

#include <vector>

// Model (Quadris)
// Game object
class Model : public Subject
{
public:
    Model(int, int);
    ~Model();

    void startGame();
    bool checkGameOver();

    void moveBlock(Command);
    void rotateBlock(Command);
    void dropBlock();

    void resetGame();

    void levelUp();
    void levelDown();
    void changeCurrentBlock(BlockType);

    int getBoardHeight() const;
    int getBoardWidth() const;
    int getLevelNum() const;
    int getScore() const;
    int getHiScore() const;

    std::vector<std::vector<char>> getNextBlock() const;
    std::vector<std::vector<char>> getBoard() const;

private:
    Level *level_;
    Board *board_;
    Score *score_;
    Block *nextBlock_;
    bool gameOver_;
};

#endif