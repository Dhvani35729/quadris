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
        if (strcmp(argv[i], "-startlevel") == 0 ||
            strcmp(argv[i], "--startlevel") == 0)
        {
            if (i + 1 < argc)
            {
                levelNum = stoi(argv[i + 1]);
                i++;
            }
        }
        else if (strcmp(argv[i], "-scriptfile") == 0 ||
                 strcmp(argv[i], "--scriptfile") == 0)
        {
            if (i + 1 < argc)
            {
                scriptFile = argv[i + 1];
                i++;
            }
        }
        else if (strcmp(argv[i], "-seed") == 0 ||
                 strcmp(argv[i], "--seed") == 0)
        {
            if (i + 1 < argc)
            {
                // Set the global seed
                seed = stoi(argv[i + 1]);
                i++;
            }
        }
        else if (strcmp(argv[i], "-text") == 0 ||
                 strcmp(argv[i], "--text") == 0)
        {
            graphicsOn = false;
        }
        else if (strcmp(argv[i], "-help") == 0 ||
                 strcmp(argv[i], "--help") == 0)
        {
            cout << "usage: ./quadris [-text] [-startlevel n] [-scriptfile xxx] [-seed xxx] [-help]"
                 << endl;
            cout << endl;
            cout << "-text runs in text-only mode. Shows both GUI and text by default."
                 << endl;
            cout << "-seed sets the RNG's seed to xxx." << endl;
            cout << "-scriptfile uses xxx instead of sequence.txt as source of blocks for level 0."
                 << endl;
            cout << "-startlevel starts the game at level n." << endl;
            cout << "-help shows this help message." << endl;
            return 0;
        }
        else
        {
            cout << "Invalid command line arguments. See './quadris --help'." << endl;
            return 0;
        }
    }

    // Create model
    shared_ptr<Model> model;
    try
    {
        model = make_shared<Model>(18, 11, levelNum, scriptFile);
    }
    catch (Model::LevelNotFoundException &e)
    {
        cout << e.getLevelNum() << ": Level number doesn't exist!" << endl;
        cout << "Exiting program..." << endl;
        return -1;
    }

    // Create controller
    shared_ptr<Controller> controller = make_shared<Controller>(model);

    // Create view
    shared_ptr<View> view = make_shared<View>(controller, model);

    if (graphicsOn)
    {
        // Initialize gtkmm with the command line arguments, as appropriate.
        Gtk::Main kit(argc, argv);

        // Run the command line view on a separate thread
        thread workerThread_([view] {
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