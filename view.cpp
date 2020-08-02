#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"

#include <iostream>
#include <memory>
#include <string>

using namespace std;

GUIView::GUIView(std::shared_ptr<View> view, std::shared_ptr<Model> model) : m_Dispatcher(),
                                                                             m_WorkerThread(nullptr), m_box1(Gtk::ORIENTATION_VERTICAL)
{
    set_title("Quadris");
    // set_border_width(10);
    set_default_size(260, 480);

    this->m_Worker = view;
    this->model_ = model;

    m_label.set_label("Level: ");

    // m_container.add(m_label);
    // m_container.add(m_Area);

    // m_container.add(m_Area);
    // add(m_container);

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

    // m_container.add(m_label);

    show_all();
    // show_all_children();

    // Connect the handler to the dispatcher.
    m_Dispatcher.connect(sigc::mem_fun(*this, &GUIView::on_notification_from_worker_thread));

    m_WorkerThread = new std::thread(
        [this] {
            m_Worker->setCaller(this);
            m_Worker->run();
        });
}

// notify() is called from ExampleWorker::do_work(). It is executed in the worker
// thread. It triggers a call to on_notification_from_worker_thread(), which is
// executed in the GUI thread.
void GUIView::notify()
{
    m_Dispatcher.emit();
}

void GUIView::update_widgets()
{
    Board board = this->model_->getBoard();
    Block nextBlock = this->model_->getNextBlock();
    m_Area.updateBoard(board.getBoard());
    m_Area.updateNextBlock(nextBlock.getCells());
    m_Area.queue_draw();
}

void GUIView::on_notification_from_worker_thread()
{
    // if (m_WorkerThread && m_Worker.has_stopped())
    // {
    //     // Work is done.
    //     if (m_WorkerThread->joinable())
    //         m_WorkerThread->join();
    //     delete m_WorkerThread;
    //     m_WorkerThread = nullptr;
    // }
    update_widgets();
}

View::View(std::shared_ptr<Controller> c, std::shared_ptr<Model> m)
{
    std::cout << "View born" << std::endl;
    this->model_ = m;
    this->controller_ = c;

    // Register view as observer of model
    model_->subscribe(this);
}

void View::setCaller(GUIView *caller)
{
    this->caller_ = caller;
};

View::~View()
{
    std::cout << "View died" << std::endl;
    model_->unsubscribe(this);
}

void View::update()
{
    // std::cout << "Updating view" << std::endl;
    // Drawing

    if (nullptr != this->caller_)
    {
        this->caller_->notify();
    }
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

void GUIView::drawNextBlock(Block){

};

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
