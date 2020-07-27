#include "model.h"
#include "controller.h"
#include "view.h"

#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Starting program..." << std::endl;
    Model model;                    // Create model
    Controller controller(&model);  // Create controller
    View view(&controller, &model); // Create the view -- is passed handle to controller and model
    view.run();                     // Show the window and return when it is closed.

    std::cout << "Exiting program..." << std::endl;
    return 0;
}