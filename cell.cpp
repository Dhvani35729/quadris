#include "cell.h"
#include <iostream>

Cell::Cell(int row, int col, char symbol)
{
    std::cout << "Cell born" << std::endl;
    this->row_ = row;
    this->col_ = col;
    this->symbol_ = symbol;
    this->occupied_ = true;
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