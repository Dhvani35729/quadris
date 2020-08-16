#ifndef CELL_H
#define CELL_H

// Cell
class Cell
{
public:
    // constructor
    Cell(int x, int y, char symbol);

    // destructor
    ~Cell();

    void setSymbol(char symbol);

    // Getters
    bool isOccupied() const;
    char getSymbol() const;

private:
    // x and y pos
    int x_;
    int y_;

    // true if the cell is not empty
    bool occupied_;

    char symbol_;
};

#endif