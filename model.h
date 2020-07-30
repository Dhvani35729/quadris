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
    bool checkGameOver();

    void moveBlock(Command);
    void rotateBlock(Command);
    void dropBlock();
    void toggleRandom(Command);

    void resetGame();

    void levelUp();
    void levelDown();
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

    std::unique_ptr<Level> level_;
    std::unique_ptr<Board> board_;
    std::unique_ptr<Score> score_;
    std::shared_ptr<Block> nextBlock_;
    bool gameOver_;
    std::string scriptFile_;
};

#endif