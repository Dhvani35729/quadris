#include "model.h"

#include <iostream>

Model::Model()
{
    std::cout << "Model born" << std::endl;
}

Model::~Model()
{
    std::cout << "Model died" << std::endl;
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