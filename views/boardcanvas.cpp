#include <vector>
#include <map>
#include <cmath>

#include "boardcanvas.h"

#include <cairomm/context.h>

using namespace std;

// constructor
BoardCanvas::BoardCanvas()
{
    // Set block colours
    blockColours['I'] = colour{0.27, 0.49, 0.67};
    blockColours['J'] = colour{0.96, 0.54, 0.03};
    blockColours['L'] = colour{1.0, 0.65, 0.62};
    blockColours['O'] = colour{0.9608, 0.796, 0.3607};
    blockColours['S'] = colour{0.37, 0.678, 0.254};
    blockColours['Z'] = colour{0.75, 0.196, 0.129};
    blockColours['T'] = colour{0.337, 0.01, 0.678};

    blockColours['?'] = colour{0.0, 0.0, 0.0};
    blockColours['*'] = colour{0.345, 0.153, 0.0274};

    // Clear the board and next block matrix
    this->board_.clear();
    this->nextBlock_.clear();
}

// destructor
BoardCanvas::~BoardCanvas() {}

// Set the size of the canvas
void BoardCanvas::setSize(int height, int width)
{
    this->bWidth_ = width;
    this->bHeight_ = height;
};

// Update the grid of cells (i.e. the board)
void BoardCanvas::updateBoard(vector<vector<char>> board)
{
    this->board_ = board;
}

// Update the matrix of the next block
void BoardCanvas::updateNextBlock(vector<vector<char>> cells)
{
    this->nextBlock_ = cells;
};

// Override default signal handler
// Draw the cells and next block
bool BoardCanvas::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    const int lesser = MIN(width, height);

    // outline thickness changes with window size
    cr->set_line_width(lesser * 0.02);

    // Draw borders around the main board
    this->drawBorders(cr);

    // Draw the main board
    for (int i = 0; i < this->board_.size(); i++)
    {
        for (int j = 0; j < this->board_[i].size(); j++)
        {
            cr->save();
            if (this->board_[i][j] == ' ')
            {
                cr->set_source_rgba(1.0, 1.0, 1.0, 0.8);
            }
            else
            {
                colour blkColor = this->blockColours[this->board_[i][j]];
                cr->set_source_rgb(blkColor.r, blkColor.g, blkColor.b);
            }
            int x = 15 + (j * 20);
            int y = 15 + (i * 20);
            cr->rectangle(x, y, 20, 20);
            cr->fill();
            cr->restore();
        }
    }

    // Draw Next Block text
    Pango::FontDescription font("sans 16");
    auto layout = create_pango_layout("Next block");
    layout->set_font_description(font);
    int startH = 20 * (this->bHeight_ + 2);
    cr->move_to(0, startH);
    layout->show_in_cairo_context(cr);

    // Draw the next block
    for (int i = 0; i < this->nextBlock_.size(); i++)
    {
        for (int j = 0; j < this->nextBlock_[i].size(); j++)
        {
            if (this->nextBlock_[i][j] != ' ')
            {
                colour blkColor = this->blockColours[this->nextBlock_[i][j]];
                cr->save();
                cr->set_source_rgb(blkColor.r, blkColor.g, blkColor.b);
                int x = j * 20;
                int y = (startH + 25) + (i * 20);
                cr->rectangle(x, y, 20, 20);
                cr->fill();
                cr->restore();
            }
        }
    }

    return true;
}

// Helper method to draw a border around the board
void BoardCanvas::drawBorders(const Cairo::RefPtr<Cairo::Context> &cr)
{
    // Top border
    int x = 0;
    int y = 0;
    for (int j = 0; j < this->bWidth_ + 2; j++)
    {
        cr->save();
        cr->set_source_rgb(0.176, 0.18, 0.18);
        if (j == 1)
        {
            x += 15;
        }
        else if (j > 1 && j != this->bWidth_ + 1)
        {
            x += 20;
        }
        else if (j == this->bWidth_ + 1)
        {
            x += 15;
        }

        cr->rectangle(x, y, 20, 15);
        cr->fill();
        cr->restore();
        cr->stroke();
    }

    // Bottom border
    x = 0;
    y = 15 + (20 * (this->bHeight_));
    for (int j = 0; j < this->bWidth_ + 2; j++)
    {
        cr->save();
        cr->set_source_rgb(0.176, 0.18, 0.18);
        if (j == 1)
        {
            x += 15;
        }
        else if (j > 1 && j != this->bWidth_ + 1)
        {
            x += 20;
        }
        else if (j == this->bWidth_ + 1)
        {
            x += 15;
        }

        cr->rectangle(x, y, 20, 15);
        cr->fill();
        cr->restore();
        cr->stroke();
    }

    // Left border
    x = 0;
    y = 0;
    for (int i = 0; i < this->bHeight_ + 2; i++)
    {
        cr->save();
        cr->set_source_rgb(0.176, 0.18, 0.18);
        if (i == 1)
        {
            y += 15;
        }
        else if (i > 1 && i != this->bHeight_ + 1)
        {
            y += 20;
        }
        else if (i == this->bHeight_ + 1)
        {
            y += 15;
        }

        cr->rectangle(x, y, 15, 20);
        cr->fill();
        cr->restore();
        cr->stroke();
    }

    // Right border
    x = 15 + (20 * (this->bWidth_));
    y = 0;
    for (int i = 0; i < this->bHeight_ + 2; i++)
    {
        cr->save();
        cr->set_source_rgb(0.176, 0.18, 0.18);
        if (i == 1)
        {
            y += 15;
        }
        else if (i > 1 && i != this->bHeight_ + 1)
        {
            y += 20;
        }
        else if (i == this->bHeight_ + 1)
        {
            y += 15;
        }

        cr->rectangle(x, y, 15, 20);
        cr->fill();
        cr->restore();
        cr->stroke();
    }
}