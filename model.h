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
#include <memory>
#include <string>

// Model (Quadris)
// Game object
class Model : public Subject
{
public:
    //define in-class exception object

    class LevelNotFoundException
    {
    public:
        LevelNotFoundException(int l) : level_(l){};
        int getLevelNum() const { return level_; }

    private:
        int level_;
    };

    Model(int h, int w, int levelNum, std::string fileName);
    ~Model();

    void startGame();
    void exitGame();
    bool checkGameOver();

    void playAI();

    void moveBlock(Command, int);
    void rotateBlock(Command, int);
    void dropBlock(int);
    void toggleRandom(Command);

    void resetGame();
    void showHint();
    void hideHint();

    void levelUp(int);
    void levelDown(int);
    void changeCurrentBlock(BlockType);

    int getBoardHeight() const;
    int getBoardWidth() const;
    int getLevelNum() const;
    int getScore() const;
    int getHiScore() const;

    Block getNextBlock() const;
    Board getBoard() const;

private:
    std::unique_ptr<Level> makeLevel(int levelNum);
    void dropBlockHelper();

    std::unique_ptr<Level> level_;
    std::unique_ptr<Board> board_;
    std::unique_ptr<Score> score_;
    std::shared_ptr<Block> nextBlock_;
    bool gameOver_;
    int blocksSinceClear_;
    std::string scriptFile_;
};

#endif