#include "model.h"
#include "controller.h"
#include "view.h"
#include "guiview.h"
#include "level.h"

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cstring>
#include <thread>

#include <gtkmm.h>

int main(int argc, char *argv[])
{

    std::cout << "Starting program..." << std::endl;
    std::cout << std::endl;

    int levelNum = 0;
    std::string scriptFile = "sequence.txt";
    // int seed = 1;
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

    std::shared_ptr<View> view = std::make_shared<View>(controller, model);
    if (graphicsOn)
    {
        // Initialize gtkmm with the command line arguments, as appropriate.
        Gtk::Main kit(argc, argv);

        std::thread workerThread_([view] {
            view->run();
        });

        //Wait for thread to detach
        workerThread_.detach();

        GUIView gui(model);  // Create the view -- is passed handle to controller and model
        Gtk::Main::run(gui); // Show the window and return when it is closed.
    }
    else
    {
        view->run();
    }

    std::cout << std::endl;
    std::cout << "Exiting program..." << std::endl;
    return 0;
}