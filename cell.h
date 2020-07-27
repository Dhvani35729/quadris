#ifndef CELL_H
#define CELL_H

// Cell
class Cell
{
public:
    Cell(int, int, char);
    ~Cell();
    void setSymbol(char c);
    bool isOccupied();

private:
    int row_;
    int col_;
    bool occupied_;
    char symbol_;
};

#endif