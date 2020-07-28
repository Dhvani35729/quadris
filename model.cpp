#include "model.h"
#include "board.h"
#include "block.h"

#include <iostream>

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
    return this->board_->isOccupied(0, 0);
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

void Model::moveBlock(Command){

};
void Model::rotateBlock(Command c)
{
    this->board_->rotateCurrentBlock(c);
    notify();
};

void Model::dropBlock()
{
    this->board_->dropCurrentBlock();
    this->board_->addBlock(this->nextBlock_);
    this->nextBlock_ = this->level_->nextBlock();
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