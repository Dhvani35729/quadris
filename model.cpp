#include "model.h"
#include "board.h"
#include "block.h"

#include <iostream>

using namespace std;

Model::Model(int h, int w)
{
    std::cout << "Model born" << std::endl;
    this->board_ = new Board(h, w);
    this->score_ = new Score();
    this->level_ = new LevelZero("sequence.txt");
    this->nextBlock_ = nullptr;
    this->gameOver_ = false;
}

Model::~Model()
{
    std::cout << "Model died" << std::endl;
    delete this->board_;
    delete this->score_;
    delete this->level_;
    delete this->nextBlock_;
}

bool Model::checkGameOver()
{
    return this->gameOver_;
};

void Model::startGame()
{
    std::cout << "Starting game" << std::endl;

    Block *newBlock = this->level_->nextBlock();
    this->board_->addBlock(newBlock);

    this->nextBlock_ = this->level_->nextBlock();

    notify();
};

void Model::moveBlock(Command c)
{
    this->board_->moveCurrentBlock(c);
    notify();
};

void Model::rotateBlock(Command c)
{
    this->board_->rotateCurrentBlock(c);
    notify();
};

void Model::dropBlock()
{
    std::pair<int, std::vector<Block>> metaData = this->board_->dropCurrentBlock();
    int linesDropped = metaData.first;
    vector<Block> clearedBlocks = metaData.second;

    // Could not drop block
    if (linesDropped >= 0)
    {
        // Dropped block

        // Update score
        int addScore = (this->level_->getLevelNum() + linesDropped);
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

        // Add new block
        bool addedBlock = this->board_->addBlock(this->nextBlock_);
        if (addedBlock)
        {
            this->nextBlock_ = this->level_->nextBlock();
        }
        else
        {
            // Game over - could not add block
            this->gameOver_ = true;
        }
    }

    // TODO: Check if this should be inside if
    notify();
};

void Model::resetGame()
{
    this->board_->resetBoard();
    this->score_->resetScore();

    delete nextBlock_;
    this->nextBlock_ = nullptr;

    this->startGame();
};

void Model::setLevel(Level *){

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

std::vector<std::vector<char>> Model::getBoard() const
{
    return this->board_->getBoard();
}
int Model::getBoardHeight() const
{
    return this->board_->getHeight();
};
int Model::getBoardWidth() const
{
    return this->board_->getWidth();
};

std::vector<std::vector<char>> Model::getNextBlock() const
{
    return this->nextBlock_->getCells();
};