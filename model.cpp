#include "model.h"
#include "board.h"
#include "block.h"

#include <iostream>

Model::Model(int h, int w)
{
    std::cout << "Model born" << std::endl;
    this->board_ = new Board(h, w);
    this->score_ = new Score();
    this->level_ = new LevelZero();
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
    return false;
};

void Model::startGame()
{
    std::cout << "Starting game" << std::endl;
    Block *newBlock = this->level_->nextBlock();
    this->board_->addBlock(newBlock);
    notify();
};

void Model::playRound(Command)
{
    notify();
};

void Model::resetGame(Command){

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