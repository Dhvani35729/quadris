#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include "observer.h"
#include "boardcanvas.h"
#include "view.h"

#include <gtkmm.h>
#include <memory>
#include <thread>

class Model;
class BoardCanvas;

class GUIView : public Gtk::Window, public Observer
{
public:
    GUIView(std::shared_ptr<View>, std::shared_ptr<Model>);
    virtual ~GUIView();

    virtual void update(); // Observer Pattern: concrete update() method

private:
    bool onExitClicked(GdkEventAny *event);

    std::shared_ptr<Model> model_;

    std::shared_ptr<View> worker_;
    std::unique_ptr<std::thread> workerThread_;

    Gtk::Box container_;
    BoardCanvas canvas_;
    Gtk::Label levelLabel_;
    Gtk::Label scoreLabel_;
    Gtk::Label hiScoreLabel_;
};

#endif