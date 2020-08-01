#include "model.h"
#include "board.h"
#include "block.h"

#include <iostream>
#include <memory>
#include <string>

using namespace std;

Model::Model(int h, int w, int levelNum, string fileName)
{
    std::cout << "Model born" << std::endl;
    this->board_ = std::make_unique<Board>(h, w);
    this->score_ = std::make_unique<Score>();
    this->scriptFile_ = fileName;

    this->level_ = this->makeLevel(levelNum);

    if (nullptr == this->level_)
    {
        throw Model::LevelNotFoundException(levelNum);
    }

    this->nextBlock_ = nullptr;
    this->gameOver_ = false;
}

Model::~Model()
{
    std::cout << "Model died" << std::endl;
}

bool Model::checkGameOver()
{
    return this->gameOver_;
};

void Model::startGame()
{
    std::cout << "Starting game" << std::endl;

    std::shared_ptr<Block> newBlock = this->level_->nextBlock();
    this->board_->addBlock(newBlock);
    this->blocksSinceClear_ += 1;

    this->nextBlock_ = this->level_->nextBlock();

    notify();
};

void Model::moveBlock(Command c, int multiplier)
{
    for (int i = 0; i < multiplier; i++)
    {
        this->board_->moveCurrentBlock(c);
    }
    notify();
};

void Model::rotateBlock(Command c, int multiplier)
{
    for (int i = 0; i < multiplier; i++)
    {
        this->board_->rotateCurrentBlock(c);
    }
    notify();
};

void Model::showHint()
{
    this->board_->showHint();
    notify();
};

void Model::hideHint()
{
    this->board_->hideHint();
};

void Model::playAI()
{
    this->showHint();
    // TODO: Remove - for testing AI mode
    // char c;
    // cin >> c;
    this->board_->playHint();
    this->dropBlock(1);
}

void Model::dropBlockHelper()
{
    std::pair<int, std::vector<Block>> metaData = this->board_->dropCurrentBlock();
    int linesCleared = metaData.first;
    vector<Block> clearedBlocks = metaData.second;

    if (linesCleared > 0)
    {
        // Update score
        int addScore = (this->level_->getLevelNum() + linesCleared);
        addScore *= addScore;
        // cout << "Add score: " << addScore << endl;

        int bonusPoints = 0;
        for (int i = 0; i < clearedBlocks.size(); i++)
        {
            int blkLevel = clearedBlocks[i].getLevelGen();
            bonusPoints += (blkLevel + 1) * (blkLevel + 1);
        }
        // cout << "Add bonus: " << bonusPoints << endl;

        addScore += bonusPoints;

        this->score_->addScore(addScore);

        this->blocksSinceClear_ = 0;
    }

    // cout << "Check special block: " << this->blocksSinceClear_ << endl;
    std::shared_ptr<Block> specialBlock = this->level_->addSpecialBlock(this->blocksSinceClear_);
    if (nullptr != specialBlock)
    {
        bool addedSpecialBlock = this->board_->addBlock(specialBlock);
        if (addedSpecialBlock)
        {
            this->blocksSinceClear_ += 1;
            if (!specialBlock->isPlayable())
            {
                this->dropBlockHelper();
            }
        }
        else
        {
            // Game over - could not add block
            this->gameOver_ = true;
        }
    }
    else
    {

        // Add new block
        std::shared_ptr<Block> nextBlock = this->nextBlock_;
        bool addedBlock = this->board_->addBlock(nextBlock);
        if (addedBlock)
        {
            this->blocksSinceClear_ += 1;
            if (!nextBlock->isPlayable())
            {
                this->dropBlockHelper();
            }
            this->nextBlock_ = this->level_->nextBlock();
        }
        else
        {
            // Game over - could not add block
            this->gameOver_ = true;
        }

        // TODO: Check if this should be inside if
    }
}

void Model::dropBlock(int multiplier)
{
    for (int i = 0; i < multiplier; i++)
    {
        this->dropBlockHelper();
    }
    notify();
};

void Model::toggleRandom(Command c)
{
    if (this->getLevelNum() == 3 || this->getLevelNum() == 4)
    {
        //TODO: toggle randomness attribute (create this) exclusive to levels 3 and 4?
    }
};

void Model::resetGame()
{
    this->board_->resetBoard();
    this->score_->resetScore();

    this->nextBlock_ = nullptr;
    this->gameOver_ = false;

    this->startGame();
};

std::unique_ptr<Level> Model::makeLevel(int levelNum)
{
    std::unique_ptr<Level> newLevel = nullptr;

    if (levelNum == 0)
    {
        newLevel = std::make_unique<LevelZero>(this->scriptFile_);
    }
    else if (levelNum == 1)
    {
        newLevel = std::make_unique<LevelOne>();
    }
    else if (levelNum == 2)
    {
        newLevel = std::make_unique<LevelTwo>();
    }
    else if (levelNum == 3)
    {
        newLevel = std::make_unique<LevelThree>();
    }
    else if (levelNum == 4)
    {
        newLevel = std::make_unique<LevelFour>();
    }

    return newLevel;
}

void Model::levelUp(int multiplier)
{
    for (int i = 0; i < multiplier; i++)
    {
        int newLevelNum = this->level_->getLevelNum() + 1;
        std::unique_ptr<Level> newLevel = this->makeLevel(newLevelNum);

        if (nullptr != newLevel)
        {
            this->level_ = move(newLevel);
        }
    }

    notify();
};

void Model::levelDown(int multiplier)
{
    for (int i = 0; i < multiplier; i++)
    {

        int newLevelNum = this->level_->getLevelNum() - 1;
        std::unique_ptr<Level> newLevel = this->makeLevel(newLevelNum);
        if (nullptr != newLevel)
        {
            this->level_ = move(newLevel);
        }
    }
    notify();
};

void Model::changeCurrentBlock(BlockType newType)
{
    this->board_->changeCurrentBlock(newType);
    notify();
};

int Model::getScore() const
{
    return this->score_->getScore();
};
int Model::getHiScore() const
{
    return this->score_->getHiScore();
};

int Model::getLevelNum() const
{
    return this->level_->getLevelNum();
};

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