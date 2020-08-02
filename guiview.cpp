#include "observer.h"
#include "guiview.h"
#include "model.h"
#include "boardcanvas.h"

#include <iostream>
#include <memory>
#include <string>

using namespace std;

GUIView::GUIView(std::shared_ptr<View> view, std::shared_ptr<Model> model) : workerThread_(nullptr), container_(Gtk::ORIENTATION_VERTICAL)
{
    std::cout << "GUIView born" << std::endl;

    set_title("Quadris");
    // set_border_width(10);
    set_default_size(260, 460);

    this->worker_ = view;
    this->model_ = model;

    levelLabel_.set_label("Level: ");
    // Align the label to the left side.
    levelLabel_.set_halign(Gtk::ALIGN_START);
    levelLabel_.set_valign(Gtk::ALIGN_START);

    scoreLabel_.set_label("Score: ");
    // Align the label to the left side.
    scoreLabel_.set_halign(Gtk::ALIGN_START);
    scoreLabel_.set_valign(Gtk::ALIGN_START);

    hiScoreLabel_.set_label("Hi Score: ");
    // Align the label to the left side.
    hiScoreLabel_.set_halign(Gtk::ALIGN_START);
    hiScoreLabel_.set_valign(Gtk::ALIGN_START);

    signal_delete_event().connect(sigc::mem_fun(this, &GUIView::onExitClicked));

    // Pack the label into the vertical box (vbox box1).  Remember that
    // widgets added to a vbox will be packed one on top of the other in
    // order.
    container_.pack_start(levelLabel_, Gtk::PACK_SHRINK);
    container_.pack_start(scoreLabel_, Gtk::PACK_SHRINK);
    container_.pack_start(hiScoreLabel_, Gtk::PACK_SHRINK);
    container_.pack_start(canvas_, Gtk::PACK_EXPAND_WIDGET);

    add(container_);

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

    workerThread_ = make_unique<std::thread>(
        [this] {
            worker_->run();
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

    if (workerThread_ && this->model_->checkGameOver())
    {
        cout << "Stopping thread" << endl;

        //Wait for thread to detach
        if (workerThread_->joinable())
        {
            workerThread_->detach();
        }
        this->hide();
    }
    else
    {
        cout << "Drawing GUI" << endl;
        int levelNum = this->model_->getLevelNum();
        levelLabel_.set_label("Level: " + std::to_string(levelNum));

        int score = this->model_->getScore();
        int hiScore = this->model_->getHiScore();
        scoreLabel_.set_label("Score: " + std::to_string(score));
        hiScoreLabel_.set_label("HI Score: " + std::to_string(hiScore));

        Board board = this->model_->getBoard();
        Block nextBlock = this->model_->getNextBlock();
        canvas_.updateBoard(board.getBoard());
        canvas_.updateNextBlock(nextBlock.getCells());
        canvas_.queue_draw();
    }
}

bool GUIView::onExitClicked(GdkEventAny *event)
{
    this->model_->exitGame();
    return true;
}