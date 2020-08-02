#include "observer.h"
#include "guiview.h"
#include "model.h"
#include "boardcanvas.h"

#include <iostream>
#include <memory>
#include <string>

using namespace std;

GUIView::GUIView(std::shared_ptr<View> view, std::shared_ptr<Model> model) : m_WorkerThread(nullptr), m_box1(Gtk::ORIENTATION_VERTICAL)
{
    std::cout << "GUIView born" << std::endl;

    set_title("Quadris");
    // set_border_width(10);
    set_default_size(260, 460);

    this->m_Worker = view;
    this->model_ = model;

    m_label.set_label("Level: ");

    // Align the label to the left side.
    m_label.set_halign(Gtk::ALIGN_START);
    m_label.set_valign(Gtk::ALIGN_START);

    signal_delete_event().connect(sigc::mem_fun(this, &GUIView::onExitClicked));

    // Pack the label into the vertical box (vbox box1).  Remember that
    // widgets added to a vbox will be packed one on top of the other in
    // order.
    m_box1.pack_start(m_label, Gtk::PACK_SHRINK);
    m_box1.pack_start(m_Area, Gtk::PACK_EXPAND_WIDGET);

    add(m_box1);

    // for (const auto &child : m_container.get_children())
    // {
    //     child->set_hexpand(true);
    //     child->set_halign(Gtk::ALIGN_FILL);
    //     child->set_vexpand(true);
    //     child->set_valign(Gtk::ALIGN_FILL);
    // }

    show_all();
    // show_all_children();

    model_->subscribe(this);

    m_WorkerThread = make_unique<std::thread>(
        [this] {
            m_Worker->run();
        });
}

GUIView::~GUIView()
{
    std::cout << "GUIView died" << std::endl;
    model_->unsubscribe(this);
}

void GUIView::update()
{
    std::cout << "Updating GUIView" << std::endl;

    if (m_WorkerThread && this->model_->checkGameOver())
    {
        cout << "Stopping thread" << endl;

        //Wait for thread to detach
        if (m_WorkerThread->joinable())
        {
            m_WorkerThread->detach();
        }
        this->hide();
    }
    else
    {
        cout << "Drawing GUI" << endl;
        Board board = this->model_->getBoard();
        Block nextBlock = this->model_->getNextBlock();
        m_Area.updateBoard(board.getBoard());
        m_Area.updateNextBlock(nextBlock.getCells());
        m_Area.queue_draw();
    }
}

bool GUIView::onExitClicked(GdkEventAny *event)
{
    this->model_->exitGame();
    return true;
}