#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H

#include <memory>

#include "model.h"
#include "interpreter.h"

class Model;

// Controller
class Controller
{
public:
    // constructor
    Controller(std::shared_ptr<Model> model);

    // destructor
    ~Controller();

    // Get the next command
    void getCommand();

private:
    std::shared_ptr<Model> model_;
    std::unique_ptr<Interpreter> inter_;
};

#endif
