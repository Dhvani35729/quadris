#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"

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

    m_WorkerThread = new std::thread(
        [this] {
            m_Worker->run();
        });
}

View::View(std::shared_ptr<Controller> c, std::shared_ptr<Model> m)
{
    std::cout << "View born" << std::endl;
    this->model_ = m;
    this->controller_ = c;

    // Register view as observer of model
    model_->subscribe(this);
}

GUIView::~GUIView()
{
    std::cout << "GUIView died" << std::endl;
    model_->unsubscribe(this);
}

View::~View()
{
    std::cout << "View died" << std::endl;
    model_->unsubscribe(this);
}

void GUIView::update()
{
    std::cout << "Updating GUIView" << std::endl;

    if (m_WorkerThread && this->model_->checkGameOver())
    {
        this->hide();
        m_WorkerThread = nullptr;
    }

    Board board = this->model_->getBoard();
    Block nextBlock = this->model_->getNextBlock();
    m_Area.updateBoard(board.getBoard());
    m_Area.updateNextBlock(nextBlock.getCells());
    m_Area.queue_draw();
}

void View::update()
{
    std::cout << "Updating view" << std::endl;
    // Drawing

    // std::cout << "Drawing board \n"
    //   << std::endl;
    this->draw();
    std::cout << std::endl;
}

void View::run()
{
    std::cout << "Running application" << std::endl;
    this->model_->startGame();

    bool exitGame = false;
    while (!exitGame && !this->model_->checkGameOver())
    {
        exitGame = controller_->getCommand();
    }
}

void View::draw()
{
    // Draw score
    // TODO: Maybe use overloaded << operator
    // TODO: Justify to right
    std::cout << "Level:     " << model_->getLevelNum() << std::endl;
    std::cout << "Score:     " << model_->getScore() << std::endl;
    std::cout << "Hi Score:  " << model_->getHiScore() << std::endl;
    std::cout << "-----------" << std::endl;

    std::cout << model_->getBoard();

    std::cout << "-----------" << std::endl;
    std::cout << "Next:      " << std::endl;
    std::cout << model_->getNextBlock();
}
