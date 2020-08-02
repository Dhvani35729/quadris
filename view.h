#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include "observer.h"

#include <gtkmm.h>
#include <memory>
#include <thread>
#include "boardcanvas.h"
#include "block.h"
#include "board.h"

class Controller;
class Model;
class GUIView;

// View
class View : public Observer
{
public:
    View(std::shared_ptr<Controller>, std::shared_ptr<Model>);
    virtual ~View();

    virtual void update(); // Observer Pattern: concrete update() method

    void run();

    void setCaller(GUIView *caller);

private:
    GUIView *caller_;
    void draw();

    // Observer Pattern: to access Model accessors without having to downcast subject
    std::shared_ptr<Model> model_;

    // Strategy Pattern member (plus signal handlers)
    std::shared_ptr<Controller> controller_;
};

class GUIView : public Gtk::Window
{
public:
    GUIView(std::shared_ptr<View>, std::shared_ptr<Model>);

    // Called from the worker thread.
    void notify();
    void drawNextBlock(Block);

    // Dispatcher handler.
    void on_notification_from_worker_thread();

private:
    void update_widgets();

    std::shared_ptr<Model> model_;

    std::shared_ptr<View> m_Worker;
    std::thread *m_WorkerThread;

    Gtk::Box m_box1;
    Glib::Dispatcher m_Dispatcher;
    Gtk::Grid m_container;
    BoardCanvas m_Area;
    Gtk::Label m_label;
};

#endif