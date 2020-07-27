#include "cell.h"
#include <iostream>

Cell::Cell(int row, int col, char symbol)
{
    // std::cout << "Cell born" << std::endl;
    this->row_ = row;
    this->col_ = col;
    this->symbol_ = symbol;
    if (symbol != ' ')
    {
        this->occupied_ = true;
    }
    else
    {
        this->occupied_ = false;
    }
};

Cell::~Cell(){
    // std::cout << "Cell died" << std::endl;
};

void Cell::setSymbol(char c)
{
    symbol_ = c;
    if (c != ' ')
    {
        this->occupied_ = true;
    }
    else
    {
        this->occupied_ = false;
    }
};
bool Cell::isOccupied()
{
    return occupied_;
};

char Cell::getSymbol() const
{
    return this->symbol_;
};