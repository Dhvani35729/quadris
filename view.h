#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include "observer.h"

#include <gtkmm.h>
#include <memory>

class Controller;
class Model;

// View
class View : public Gtk::Window, public Observer
{
public:
    View(std::shared_ptr<Controller>, std::shared_ptr<Model>);
    virtual ~View();
    virtual void update(); // Observer Pattern: concrete update() method
    void run();

private:
    void draw();

    // Observer Pattern: to access Model accessors without having to downcast subject
    std::shared_ptr<Model> model_;

    // Strategy Pattern member (plus signal handlers)
    std::shared_ptr<Controller> controller_;
};

#endif