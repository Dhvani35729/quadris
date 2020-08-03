#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include <memory>

#include "observer.h"
#include "boardcanvas.h"

#include <gtkmm.h>

class Model;

// GUIView
class GUIView : public Gtk::Window, public Observer
{
public:
    // constructor
    GUIView(std::shared_ptr<Model> model);

    // destructor
    virtual ~GUIView();

    // Observer Pattern: concrete update() method
    virtual void update();

private:
    // Helper method for on window exit (red) button clicked
    bool onExitClicked(GdkEventAny *event);

    // Helper method to draw
    void draw();

    // Observer Pattern: to access Model accessors without having to downcast subject
    std::shared_ptr<Model> model_;

    // GUI Elements
    Gtk::Box container_;
    Gtk::Box labelContainer_;
    Gtk::Label levelLabel_;
    Gtk::Label scoreLabel_;
    Gtk::Label hiScoreLabel_;

    // Custom Drawing Area
    BoardCanvas canvas_;
};

#endif