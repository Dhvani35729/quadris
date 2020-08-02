#ifndef BOARD_CANVAS_
#define BOARD_CANVAS_

#include <gtkmm/drawingarea.h>

#include "board.h"
#include "block.h"

struct colour
{
    float r;
    float g;
    float b;
};

class BoardCanvas : public Gtk::DrawingArea
{
public:
    BoardCanvas();
    virtual ~BoardCanvas();
    void updateBoard(std::vector<std::vector<char>>);
    void updateNextBlock(std::vector<std::vector<char>>);

protected:
    //Override default signal handler:
    bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

private:
    std::vector<std::vector<char>> board_;
    std::vector<std::vector<char>> nextBlock_;
    std::map<char, colour> blockColours;
};

#endif