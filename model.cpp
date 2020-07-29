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
}

Model::~Model()
{
    std::cout << "Model died" << std::endl;
    delete this->board_;
    delete this->score_;
    delete this->level_;
}

bool Model::checkGameOver()
{
    return this->gameOver_;
};

void Model::startGame()
{
    std::cout << "Starting game" << std::endl;
    if (nullptr == this->nextBlock_)
    {
        Block *newBlock = this->level_->nextBlock();
        this->board_->addBlock(newBlock);
    }
    else
    {
        this->board_->addBlock(this->nextBlock_);
    }
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
    int linesDropped = this->board_->dropCurrentBlock();
    // Could not drop block
    if (linesDropped == -1)
    {
        // Do nothing
        cout << "Do nothing" << endl;
    }
    // Dropped block
    else
    {
        // Update score
        int addScore = (this->level_->getLevelNum() + linesDropped);
        addScore *= addScore;
        // cout << "Add score: " << addScore << endl;

        int bonusPoints = 0;
        std::vector<Block *> cBlocks = this->board_->getClearedBlocks();
        for (int i = 0; i < cBlocks.size(); i++)
        {
            Block *cBlk = cBlocks[i];
            if (!cBlk->getScoreCounted())
            {
                bonusPoints += (cBlk->getLevelGen() + 1) * (cBlk->getLevelGen() + 1);
                cBlk->setScoreCounted(true);
            }
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
            // Game over
            this->gameOver_ = true;
        }
    }
    notify();
};

void Model::resetGame(){

};

void Model::setLevel(Level *){

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