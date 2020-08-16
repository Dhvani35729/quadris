#ifndef BOARD_CANVAS_H
#define BOARD_CANVAS_H

#include <vector>
#include <map>

#include <gtkmm/drawingarea.h>

// Colour struct
struct colour
{
    float r;
    float g;
    float b;
};

// BoardCanvas
class BoardCanvas : public Gtk::DrawingArea
{
public:
    // constructor
    BoardCanvas();

    // destructor
    virtual ~BoardCanvas();

    // Set the size of the canvas
    void setSize(int height, int width);

    // Update the grid of cells (i.e. the board)
    void updateBoard(std::vector<std::vector<char>> board);

    // Update the matrix of the next block
    void updateNextBlock(std::vector<std::vector<char>> cells);

protected:
    // Override default signal handler
    bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

    // Helper method to draw a border around the board
    void drawBorders(const Cairo::RefPtr<Cairo::Context> &cr);

private:
    // Board height and width
    int bHeight_;
    int bWidth_;

    // Grid of cells (i.e. the board)
    std::vector<std::vector<char>> board_;

    // The matrix of cells of the next block
    std::vector<std::vector<char>> nextBlock_;

    // Map of char's to colours
    std::map<char, colour> blockColours;
};

#endif