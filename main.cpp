#include <iostream>
#include <memory>
#include <string>
#include <cstring>
#include <thread>

#include "model.h"
#include "controller.h"
#include "view.h"
#include "guiview.h"
#include "level.h"

#include <gtkmm.h>

using namespace std;

int main(int argc, char *argv[])
{

    // Default level number
    int levelNum = 0;

    // Default LevelZero script file
    string scriptFile = "sequence.txt";

    // Default, GUIView enabled
    bool graphicsOn = true;

    // Parse command line arguments
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
                // Set the global seed
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

    // Create view
    std::shared_ptr<View> view = std::make_shared<View>(controller, model);

    if (graphicsOn)
    {
        // Initialize gtkmm with the command line arguments, as appropriate.
        Gtk::Main kit(argc, argv);

        // Run the command line view on a separate thread
        std::thread workerThread_([view] {
            view->run();
        });

        // Detach thread so we can run the GUIView
        workerThread_.detach();

        // Create the GUIView
        GUIView gui(model);

        // Show the window and return when it is closed.
        Gtk::Main::run(gui);
    }
    else
    {
        // Run
        view->run();
    }

    return 0;
}