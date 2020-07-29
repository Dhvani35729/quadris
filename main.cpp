#include "model.h"
#include "controller.h"
#include "view.h"

#include <iostream>
#include <vector>
#include <cstdlib>

int generate()
{
    return std::rand() % 8;
}

int main(int argc, char *argv[])
{
    std::vector<int> freq;
    freq.resize(7, 0);

    for (int i = 0; i < 1000000; i++)
    {
        int r = generate();
        // std::cout << "got Rand: " << r << std::endl;
        freq[r] += 1;
    }

    for (int i = 0; i < freq.size(); i++)
    {
        std::cout << "i ~ " << freq[i] << std::endl;
    }

    std::cout << "Starting program..." << std::endl;
    std::cout << std::endl;

    Model model(18, 11);            // Create model
    Controller controller(&model);  // Create controller
    View view(&controller, &model); // Create the view -- is passed handle to controller and model
    view.run();                     // Show the window and return when it is closed.

    std::cout << std::endl;
    std::cout << "Exiting program..." << std::endl;
    return 0;
}