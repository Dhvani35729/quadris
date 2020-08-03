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
    blockColours['X'] = colour{0.0, 0.0, 0.0};

    this->board_.clear();
}

void BoardCanvas::setSize(int height, int width)
{
    this->bWidth_ = width;
    this->bHeight_ = height;
};

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

    cr->set_line_width(lesser * 0.02); // outline thickness changes
                                       // with window size

    // std::cout << "Drawing canvas" << std::endl;
    // std::cout << "width" << width << std::endl;
    // std::cout << "height" << height << std::endl;

    // int bWidth = this->board_.getWidth();
    // int eight = this->board_.getHeight();

    // Draw borders
    // Top border

    // Top
    // std::cout << "Width: " << this->bWidth_ << std::endl;
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

    // Down
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

    // Left
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

    // Right
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

    // std::cout << "---" << std::endl;
    for (int i = 0; i < this->board_.size(); i++)
    {
        for (int j = 0; j < this->board_[i].size(); j++)
        {
            // std::cout << "Drawing cell: " << i << ":"
            //           << j << std::endl;
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
            // std::cout << "BX: " << x << std::endl;
            cr->rectangle(x, y, 20, 20);
            cr->fill();
            cr->restore();
        }
    }

    Pango::FontDescription font("sans 16");

    // font.set_family("Sans");

    auto layout = create_pango_layout("Next block");

    layout->set_font_description(font);

    // std::cout << "Font: " << font.get_size() << std::endl;

    // Position the text in the middle
    int startH = 20 * (this->bHeight_ + 2);
    cr->move_to(0, startH);

    layout->show_in_cairo_context(cr);

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
                int y = (startH + 20) + (i * 20);
                cr->rectangle(x, y, 20, 20);
                cr->fill();
                cr->restore();
            }
        }
    }

    return true;
}