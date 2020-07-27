#include "cell.h"
#include <iostream>

Cell::Cell(int row, int col)
{
    this->row_ = row;
    this->col_ = col;
    this->occupied_ = false;
    std::cout << "Cell born" << std::endl;
};

Cell::~Cell()
{
    std::cout << "Cell died" << std::endl;
};

void Cell::setSymbol(char c)
{
    symbol_ = c;
};
bool Cell::isOccupied()
{
    return occupied_;
};