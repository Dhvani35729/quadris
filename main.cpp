#include "model.h"
#include "controller.h"
#include "view.h"

#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{

    std::cout << "Starting program..." << std::endl;
    std::cout << std::endl;

    // Create model
    std::shared_ptr<Model> model = std::make_shared<Model>(18, 11);
    // Create controller
    std::shared_ptr<Controller> controller = std::make_shared<Controller>(model);
    View view(controller, model); // Create the view -- is passed handle to controller and model
    view.run();                   // Show the window and return when it is closed.

    std::cout << std::endl;
    std::cout << "Exiting program..." << std::endl;
    return 0;
}