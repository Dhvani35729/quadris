#include "cell.h"

// constructor
Cell::Cell(int x, int y, char symbol)
{
    this->x_ = x;
    this->y_ = y;
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

// destructor
Cell::~Cell(){};

void Cell::setSymbol(char symbol)
{
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

// Getters
bool Cell::isOccupied() const
{
    return this->occupied_;
};

char Cell::getSymbol() const
{
    return this->symbol_;
};