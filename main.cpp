#include "model.h"
#include "controller.h"
#include "view.h"

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cstring>

#include <gtkmm.h>
#include <cairomm/cairomm.h>

/** Main window class. */
class MainWindow : public Gtk::Window
{
private:
    /** Subclass for drawing area. */
    class CDrawingArea : public Gtk::DrawingArea
    {
    public:
        typedef enum
        {
            SHAPE_RECTANGLE,
            SHAPE_ELLIPSE,
            SHAPE_TRIANGLE
        } shape_t;

    private:
        shape_t _curShape = SHAPE_RECTANGLE;

        /** Drawing event handler. */
        virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
        {
            switch (_curShape)
            {
            case SHAPE_RECTANGLE:
                cr->rectangle(20, 20, 200, 100);
                cr->set_source_rgb(0, 0.8, 0);
                cr->fill_preserve();
                break;
            case SHAPE_ELLIPSE:
                cr->arc(150, 100, 90, 0, 2 * 3.14);
                cr->set_source_rgb(0.8, 0, 0);
                cr->fill_preserve();
                break;
            case SHAPE_TRIANGLE:
                cr->move_to(40, 40);
                cr->line_to(200, 40);
                cr->line_to(120, 160);
                cr->line_to(40, 40);
                cr->set_source_rgb(0.8, 0, 0.8);
                cr->fill_preserve();
                cr->set_line_cap(Cairo::LINE_CAP_ROUND);
                cr->set_line_join(Cairo::LINE_JOIN_ROUND);
                break;
            }
            cr->set_line_width(3);
            cr->set_source_rgb(0, 0, 0);
            cr->stroke();
            return true;
        }

    public:
        CDrawingArea(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder)
            : Gtk::DrawingArea(cobject) {}

        void SetShape(shape_t shape)
        {
            if (_curShape != shape)
            {
                _curShape = shape;
                queue_draw(); // Request re-drawing.
            }
        }
    };

    Glib::RefPtr<Gtk::Builder> _builder;
    Gtk::RadioButton *_rbRect, *_rbEllipse, *_rbTriangle;
    Gtk::ScrolledWindow *_swin;
    CDrawingArea *_drawingArea;

public:
    /** Signal handler which is called when any radio button is clicked. */
    void OnRadiobuttonClick()
    {
        if (_rbRect->get_active())
        {
            _drawingArea->SetShape(CDrawingArea::SHAPE_RECTANGLE);
        }
        else if (_rbEllipse->get_active())
        {
            _drawingArea->SetShape(CDrawingArea::SHAPE_ELLIPSE);
        }
        else if (_rbTriangle->get_active())
        {
            _drawingArea->SetShape(CDrawingArea::SHAPE_TRIANGLE);
        }
    }

    /** "quit" action handler. */
    void OnQuit() { hide(); }

    MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder) : Gtk::Window(cobject), _builder(builder)
    {
        /* Retrieve all widgets. */
        _builder->get_widget("rbutRectangle", _rbRect);
        _builder->get_widget("rbutEllipse", _rbEllipse);
        _builder->get_widget("rbutTriangle", _rbTriangle);
        _builder->get_widget("scrolledwindow1", _swin);
        _builder->get_widget_derived("drawingarea", _drawingArea);
        _drawingArea->set_size_request(300, 200);
        _swin->set_min_content_height(200);
        _swin->set_min_content_width(300);

        /* Connect signals. */
        _rbRect->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnRadiobuttonClick));
        _rbEllipse->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnRadiobuttonClick));
        _rbTriangle->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnRadiobuttonClick));

        /* Actions. */
        Glib::RefPtr<Gtk::Action>::cast_dynamic(_builder->get_object("action_quit"))->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::OnQuit));
    }
};

int main(int argc, char *argv[])
{

    std::cout << "Starting program..." << std::endl;
    std::cout << std::endl;
    Gtk::Main app(argc, argv);
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("sample.glade");
    MainWindow *mainWindow = nullptr;
    builder->get_widget_derived("topWindow", mainWindow);
    app.run(*mainWindow);
    delete mainWindow;
    return 0;

    int levelNum = 0;
    std::string scriptFile = "sequence.txt";
    int seed = 1;
    bool graphicsOn = true;

    for (int i = 1; i < argc; i++)
    {
        if (std::strcmp(argv[i], "-startlevel") == 0 || std::strcmp(argv[i], "--startlevel") == 0)
        {
            if (i + 1 < argc)
            {
                levelNum = std::stoi(argv[i + 1]);
                i++;
            }
        }
        else if (std::strcmp(argv[i], "-scriptfile") == 0 || std::strcmp(argv[i], "--scriptfile") == 0)
        {
            if (i + 1 < argc)
            {
                scriptFile = argv[i + 1];
                i++;
            }
        }
        else if (std::strcmp(argv[i], "-seed") == 0 || std::strcmp(argv[i], "--seed") == 0)
        {
            if (i + 1 < argc)
            {
                seed = std::stoi(argv[i + 1]);
                i++;
            }
        }
        else if (std::strcmp(argv[i], "-text") == 0 || std::strcmp(argv[i], "--text") == 0)
        {
            graphicsOn = false;
        }
        else
        {
            std::cout << "Invalid command line arguments." << std::endl;
            return 0;
        }
    }

    // Create model
    std::shared_ptr<Model> model;
    try
    {
        model = std::make_shared<Model>(18, 11, levelNum, scriptFile);
    }
    catch (Model::LevelNotFoundException &e)
    {
        std::cout << e.getLevelNum() << ": Level number doesn't exist!" << std::endl;
        std::cout << "Exiting program..." << std::endl;
        return -1;
    }

    // Create controller
    std::shared_ptr<Controller> controller = std::make_shared<Controller>(model);
    View view(controller, model); // Create the view -- is passed handle to controller and model
    view.run();                   // Show the window and return when it is closed.

    std::cout << std::endl;
    std::cout << "Exiting program..." << std::endl;
    return 0;
}