#ifndef MVC_MODEL_H
#define MVC_MODEL_H

#include <vector>
#include <memory>
#include <string>

#include "../support/subject.h"
#include "../game/level.h"
#include "../game/score.h"
#include "../blocks/block.h"
#include "../board/board.h"

// Model (Quadris)
// Represents the game object
class Model : public Subject
{
public:
    // LevelNotFoundException in-class exception
    class LevelNotFoundException
    {
    public:
        LevelNotFoundException(int l) : level_(l){};
        int getLevelNum() const { return level_; }

    private:
        int level_;
    };

    // constructor
    Model(int height, int width, int levelNum, std::string fileName);

    // destructor
    ~Model();

    // Start the game
    void startGame();

    // End the game
    void exitGame();

    // Reset the game
    void resetGame();

    // Returns true if the game is over
    bool isGameOver() const;

    // Move the current block in the
    // specified direction x multiplier times
    void moveBlock(Direction dir, int multiplier);

    // Rotate the current block in the
    // specified direction x multiplier times
    void rotateBlock(Direction dir, int multiplier);

    // Drop the current block
    // This will also trigger an update of score
    // and the generation of the next current block
    // Do this x multiplier times
    void dropBlock(int multiplier);

    // Change the current block to the new type
    void changeCurrentBlock(BlockType type);

    // Show the hint block
    void showHint();

    // Hide the hint block
    void hideHint();

    // Level up by 1
    // Do this x multiplier times
    void levelUp(int multiplier);

    // Level down by 1
    // Do this x multiplier times
    void levelDown(int multiplier);

    // Turn on randomness in the level
    void randomOn();

    // Turn off randomness in the level
    // and take input from file
    void randomOff(std::string seqFileName);

    // Special method (not part of spec)
    // Plays the hint block
    void playAI();

    // Getters
    Board getBoard() const;
    int getBoardHeight() const;
    int getBoardWidth() const;

    Block getNextBlock() const;
    int getLevelNum() const;
    int getScore() const;
    int getHiScore() const;

private:
    // Helper methods

    // Maps level numbers to Level classes
    std::unique_ptr<Level> makeLevel(int levelNum);

    // Helper recursive drop block method
    void dropBlockHelper();

    // Each game object has a level, a board, a score
    std::unique_ptr<Level> level_;
    std::unique_ptr<Board> board_;
    std::unique_ptr<Score> score_;

    // The game object also keeps track of:

    // the next block
    std::shared_ptr<Block> nextBlock_;

    // if the game is over
    bool gameOver_;

    // how many blocks have been placed
    // since the last time a line was cleared
    int blocksSinceClear_;

    // The script file for LevelZero
    // Note: This is a special case for LevelZero only
    // Only added for test purposes,
    // can remove once LevelZero is removed
    std::string scriptFile_;
};

#endif