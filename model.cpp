#include <vector>
#include <memory>
#include <string>
#include <utility>

#include "model.h"
#include "level.h"
#include "score.h"
#include "block.h"
#include "board.h"

using namespace std;

// constructor
Model::Model(int height, int width, int levelNum, string fileName)
{
    this->board_ = make_unique<Board>(height, width);
    this->score_ = make_unique<Score>();
    this->scriptFile_ = fileName;

    this->level_ = this->makeLevel(levelNum);

    if (nullptr == this->level_)
    {
        throw Model::LevelNotFoundException(levelNum);
    }

    this->nextBlock_ = nullptr;
    this->gameOver_ = false;
}

// Helper method
// Maps level numbers to Level classes
unique_ptr<Level> Model::makeLevel(int levelNum)
{
    unique_ptr<Level> newLevel = nullptr;

    if (levelNum == 0)
    {
        newLevel = make_unique<LevelZero>(this->scriptFile_);
    }
    else if (levelNum == 1)
    {
        newLevel = make_unique<LevelOne>();
    }
    else if (levelNum == 2)
    {
        newLevel = make_unique<LevelTwo>();
    }
    else if (levelNum == 3)
    {
        newLevel = make_unique<LevelThree>();
    }
    else if (levelNum == 4)
    {
        newLevel = make_unique<LevelFour>();
    }

    return newLevel;
}

// destructor
Model::~Model() {}

void Model::startGame()
{
    // Get a new block from the level and add it to the board
    shared_ptr<Block> newBlock = this->level_->nextBlock();
    this->board_->addBlock(newBlock);

    // Increment block added
    this->blocksSinceClear_ += 1;

    // Get the next block again, to display the next block
    this->nextBlock_ = this->level_->nextBlock();

    notify();
};

void Model::exitGame()
{
    this->gameOver_ = true;
    notify();
}

void Model::resetGame()
{
    // Reset the board and score
    this->board_->resetBoard();
    this->score_->resetScore();

    this->nextBlock_ = nullptr;
    this->gameOver_ = false;

    // Start thr game again
    this->startGame();
};

// Returns true if the game is over
bool Model::isGameOver() const
{
    return this->gameOver_;
};

// Move the current block in the
// specified direction x multiplier times
void Model::moveBlock(Direction c, int multiplier)
{
    for (int i = 0; i < multiplier; i++)
    {
        this->board_->moveCurrentBlock(c);
    }
    notify();
};

// Rotate the current block in the
// specified direction x multiplier times
void Model::rotateBlock(Direction c, int multiplier)
{
    for (int i = 0; i < multiplier; i++)
    {
        this->board_->rotateCurrentBlock(c);
    }
    notify();
};

// Drop the current block
// Do this x multiplier times
void Model::dropBlock(int multiplier)
{
    for (int i = 0; i < multiplier; i++)
    {
        this->dropBlockHelper();
    }
    notify();
};

// Helper recursive method
// Drops the current block, and then calculates the score
// Base case: no special blocks
// Recursive call:
// If there are special blocks (eg. Star Block)
// then we call dropBlockHelper() helper again
void Model::dropBlockHelper()
{
    // Drop the current block
    pair<int, vector<Block>> metaData = this->board_->dropCurrentBlock();
    int linesCleared = metaData.first;
    vector<Block> clearedBlocks = metaData.second;

    if (linesCleared > 0)
    {
        // Update score
        // addScore = (current level + number of lines cleared)^2
        int addScore = (this->level_->getLevelNum() + linesCleared);
        addScore *= addScore;

        // For each block that was cleared
        // bounsPoints = (the level at which the block was generated + 1)^2
        int bonusPoints = 0;
        for (int i = 0; i < clearedBlocks.size(); i++)
        {
            int blkLevel = clearedBlocks[i].getLevelGen();
            bonusPoints += (blkLevel + 1) * (blkLevel + 1);
        }

        addScore += bonusPoints;

        this->score_->addScore(addScore);

        // Reset the blocks since last clear counter
        this->blocksSinceClear_ = 0;
    }

    // We check if for any special blocks
    shared_ptr<Block> specialBlock = this->level_->addSpecialBlock(this->blocksSinceClear_);

    // If there are special blocks, we add the special block to the board
    if (nullptr != specialBlock)
    {
        bool addedSpecialBlock = this->board_->addBlock(specialBlock);
        if (addedSpecialBlock)
        {
            // If we could add the special block, we increase our counter
            this->blocksSinceClear_ += 1;

            // If the block is not playable, we drop it
            if (!specialBlock->isPlayable())
            {
                // Recursive call
                this->dropBlockHelper();
            }
        }
        else
        {
            // If we cannot add the special block, the game is over
            this->gameOver_ = true;
        }
    }
    else
    {
        // If there are no special blocks, then we add the new block
        shared_ptr<Block> nextBlock = this->nextBlock_;
        bool addedBlock = this->board_->addBlock(nextBlock);
        if (addedBlock)
        {
            // If we could add the new block, we increase our counter
            this->blocksSinceClear_ += 1;

            // If the block is not playable, we drop it
            if (!nextBlock->isPlayable())
            {
                // Recursive call
                this->dropBlockHelper();
            }
            // Otherwise, we get the next block to be displayed
            this->nextBlock_ = this->level_->nextBlock();
        }
        else
        {
            // If we cannot add a new block, the game is over
            this->gameOver_ = true;
        }
    }
}

// Change the current block to the new type
void Model::changeCurrentBlock(BlockType newType)
{
    this->board_->changeCurrentBlock(newType);
    notify();
};

// Show the hint block
void Model::showHint()
{
    this->board_->showHint();
    notify();
};

// Hide the hint block
void Model::hideHint()
{
    this->board_->hideHint();
};

// Level up by 1
// Do this x multiplier times
void Model::levelUp(int multiplier)
{
    for (int i = 0; i < multiplier; i++)
    {
        int newLevelNum = this->level_->getLevelNum() + 1;
        unique_ptr<Level> newLevel = this->makeLevel(newLevelNum);

        if (nullptr != newLevel)
        {
            // Move constructor
            this->level_ = move(newLevel);
        }
    }

    notify();
};

// Level down by 1
// Do this x multiplier times
void Model::levelDown(int multiplier)
{
    for (int i = 0; i < multiplier; i++)
    {

        int newLevelNum = this->level_->getLevelNum() - 1;
        unique_ptr<Level> newLevel = this->makeLevel(newLevelNum);
        if (nullptr != newLevel)
        {
            // Move constructor
            this->level_ = move(newLevel);
        }
    }
    notify();
};

// Turn on randomness in the level
void Model::randomOn()
{
    this->level_->setIsRandom(true);
    notify();
};

// Turn off randomness in the level
// and take input from the file
void Model::randomOff(string seqFileName)
{
    this->level_->setSequenceFile(seqFileName);
    this->level_->setIsRandom(false);
    notify();
};

// Special method (not part of spec)
// Plays the hint block
void Model::playAI()
{
    // Show the hint
    this->showHint();
    // Play the hint
    // Note: a delay can be added here for testing
    this->board_->playHint();
    // Drop the hint block
    this->dropBlock(1);
}

// Getters
Board Model::getBoard() const
{
    return *this->board_;
}

int Model::getBoardHeight() const
{
    return this->board_->getHeight();
};
int Model::getBoardWidth() const
{
    return this->board_->getWidth();
};

Block Model::getNextBlock() const
{
    return *this->nextBlock_;
};

int Model::getLevelNum() const
{
    return this->level_->getLevelNum();
};

int Model::getScore() const
{
    return this->score_->getScore();
};
int Model::getHiScore() const
{
    return this->score_->getHiScore();
};
