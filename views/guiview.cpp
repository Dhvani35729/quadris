#include <memory>
#include <string>

#include "../support/observer.h"
#include "../support/subject.h"
#include "../views/guiview.h"
#include "../game/model.h"
#include "boardcanvas.h"

using namespace std;

// constructor
GUIView::GUIView(shared_ptr<Model> model)
    : container_(Gtk::ORIENTATION_HORIZONTAL),
      labelContainer_(Gtk::ORIENTATION_VERTICAL)
{

    this->model_ = model;
    int bHeight = this->model_->getBoardHeight();
    int bWidth = this->model_->getBoardWidth();

    canvas_.setSize(bHeight, bWidth);

    set_title("Quadris - Dhvani, Peggy, Minglei");

    set_default_size(450, 500);

    // Align the labels to the left side.
    levelLabel_.set_halign(Gtk::ALIGN_START);
    levelLabel_.set_justify(Gtk::JUSTIFY_LEFT);

    scoreLabel_.set_halign(Gtk::ALIGN_START);
    scoreLabel_.set_justify(Gtk::JUSTIFY_LEFT);

    hiScoreLabel_.set_halign(Gtk::ALIGN_START);
    hiScoreLabel_.set_justify(Gtk::JUSTIFY_LEFT);

    levelLabel_.set_margin_top(100);
    scoreLabel_.set_margin_top(50);
    hiScoreLabel_.set_margin_top(30);

    labelContainer_.set_margin_right(20);
    canvas_.set_margin_top(15);

    // Setup signal for window exit (red) button clicked
    signal_delete_event().connect(
        sigc::mem_fun(this, &GUIView::onExitClicked));

    // Pack the label into the vertical box
    labelContainer_.pack_start(levelLabel_, Gtk::PACK_SHRINK);
    labelContainer_.pack_start(hiScoreLabel_, Gtk::PACK_SHRINK);
    labelContainer_.pack_start(scoreLabel_, Gtk::PACK_SHRINK);

    // Pack the label container and canvas to the container, with some padding
    container_.pack_start(labelContainer_, Gtk::PACK_SHRINK, 15);
    container_.pack_start(canvas_, Gtk::PACK_EXPAND_WIDGET, 15);

    add(container_);
    show_all();

    // Get initial data
    this->update();

    // Register GUIView as an observer of model
    model_->subscribe(this);
}

// destructor
GUIView::~GUIView()
{
    // Unregister GUIView as an observer of model
    model_->unsubscribe(this);
}

// Helper method for on window exit (red) button clicked
bool GUIView::onExitClicked(GdkEventAny *event)
{
    this->model_->exitGame();
    return true;
}

// Observer Pattern: concrete update() method
void GUIView::update()
{
    // Draw each time model updates
    this->draw();

    // If the game is over,
    // close the window
    if (this->model_->isGameOver())
    {
        this->hide();
    }
}

// Helper method to draw
void GUIView::draw()
{
    int levelNum = this->model_->getLevelNum();
    string levelLabel = "Level: " + to_string(levelNum);
    levelLabel_.set_markup("<span font_desc=\"18.0\">" + levelLabel + "</span>");

    int score = this->model_->getScore();
    int hiScore = this->model_->getHiScore();
    string scoreLabel = "Score: " + to_string(score);
    string hiScoreLabel = "Hi Score: " + to_string(hiScore);
    scoreLabel_.set_markup("<span font_desc=\"16.0\">" + scoreLabel + "</span>");
    hiScoreLabel_.set_markup("<span font_desc=\"16.0\">" + hiScoreLabel + "</span>");

    Board board = this->model_->getBoard();
    Block nextBlock = this->model_->getNextBlock();
    canvas_.updateBoard(board.getBoard());
    canvas_.updateNextBlock(nextBlock.getCells());
    canvas_.queue_draw();
}