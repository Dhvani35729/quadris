#include "model.h"
#include "board.h"

#include <iostream>

Model::Model(int h, int w)
{
    std::cout << "Model born" << std::endl;
    this->board_ = new Board(h, w);
    this->score_ = new Score();
}

Model::~Model()
{
    std::cout << "Model died" << std::endl;
    delete this->board_;
    delete this->score_;
}

bool Model::checkGameOver()
{
    return false;
};

void Model::startGame()
{
    std::cout << "Starting game" << std::endl;
};

void Model::playRound(Command){

};

void Model::resetGame(Command){

};

void Model::setLevel(Level *){

};

Score Model::getScore()
{
    return *score_;
};