#include <iostream>
#include <memory>
#include <string>

#include "../views/view.h"

#include "../support/observer.h"
#include "../support/subject.h"
#include "../support/fileexception.h"
#include "../controller/controller.h"
#include "../game/model.h"

using namespace std;

// constructor
View::View(shared_ptr<Controller> cont, shared_ptr<Model> model)
{
    this->model_ = model;
    this->controller_ = cont;

    // Register View as an observer of model
    model_->subscribe(this);
}

// destructor
View::~View()
{
    // Unregister View as an observer of model
    model_->unsubscribe(this);
}

// Observer Pattern: concrete update() method
void View::update()
{
    // Draw each time model updates
    this->draw();

    // If the game is over,
    // tell the user, game is over!
    if (this->model_->isGameOver())
    {
        cout << "xxxxxxxxxxx" << endl;
        cout << "Game over!" << endl;
        cout << "xxxxxxxxxxx" << endl;
    }
}

// Run the View (game loop)
// (i.e. start taking in commands from command line)
void View::run()
{
    // Start the game
    this->model_->startGame();

    // As long as the game isn't over,
    // keep taking in commands
    while (!this->model_->isGameOver())
    {
        try
        {
            controller_->getCommand();
        }
        catch (FileNotFoundException e)
        {
            cout << "Could not open file: " << e.getFileName() << endl;
        }
    }
}

// Helper method to draw
void View::draw()
{
    // Draw score
    // Note: An output operator was not added to score or level
    // as users may wish to format their output differently (per view)
    cout << "Level:     " << model_->getLevelNum() << endl;
    cout << "Score:     " << model_->getScore() << endl;
    cout << "Hi Score:  " << model_->getHiScore() << endl;
    cout << "-----------" << endl;

    cout << model_->getBoard();

    cout << "-----------" << endl;
    cout << "Next:      " << endl;
    cout << model_->getNextBlock();

    cout << endl;
}
