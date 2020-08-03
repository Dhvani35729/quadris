#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <memory>

#include "observer.h"

class Controller;
class Model;

// View
class View : public Observer
{
public:
    // constructor
    View(std::shared_ptr<Controller> cont, std::shared_ptr<Model> model);

    // destructor
    virtual ~View();

    // Observer Pattern: concrete update() method
    virtual void update();

    // Run the View (game loop)
    // (i.e. start taking in commands from command line)
    void run();

private:
    // Helper method to draw
    void draw();

    // Observer Pattern: to access Model accessors
    // without having to downcast subject
    std::shared_ptr<Model> model_;

    // Strategy Pattern member (plus signal handlers)
    std::shared_ptr<Controller> controller_;
};

#endif