#include "boardcanvas.h"
#include <cairomm/context.h>

#include <iostream>
#include <cmath>

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

    this->board_.clear();
}

BoardCanvas::~BoardCanvas()
{
}

void BoardCanvas::updateBoard(std::vector<std::vector<char>> b)
{
    this->board_ = b;
}
void BoardCanvas::updateNextBlock(std::vector<std::vector<char>> b)
{
    this->nextBlock_ = b;
};

bool BoardCanvas::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    const int lesser = MIN(width, height);

    // coordinates for the center of the window
    int xc, yc;
    xc = width / 2;
    yc = height / 2;

    cr->set_line_width(lesser * 0.02); // outline thickness changes
                                       // with window size

    std::cout << "Drawing canvas" << std::endl;
    // std::cout << "width" << width << std::endl;
    // std::cout << "height" << height << std::endl;

    // int bWidth = this->board_.getWidth();
    // int eight = this->board_.getHeight();

    // Draw borders

    for (int i = 0; i < this->board_.size(); i++)
    {
        for (int j = 0; j < this->board_[i].size(); j++)
        {
            // std::cout << "Drawing cell: " << i << ":"
            //           << j << std::endl;
            if (this->board_[i][j] == ' ')
            {
                cr->save();
                cr->set_source_rgba(1.0, 1.0, 1.0, 0.8);
                int x = j * 20;
                int y = i * 20;
                cr->rectangle(x, y, 20, 20);
                cr->fill();
                cr->restore();
                cr->stroke();
            }
            else
            {
                colour blkColor = this->blockColours[this->board_[i][j]];
                cr->save();
                cr->set_source_rgb(blkColor.r, blkColor.g, blkColor.b);
                int x = j * 20;
                int y = i * 20;
                cr->rectangle(x, y, 20, 20);
                cr->fill();
                cr->restore();
            }
        }
    }

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
                int y = 380 + i * 20;
                cr->rectangle(x, y, 20, 20);
                cr->fill();
                cr->restore();
            }
        }
    }

    return true;
}