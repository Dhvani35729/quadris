#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H

#include "model.h"
#include "interpreter.h"

#include <memory>

class Model;

// Controller
class Controller
{
public:
    Controller(std::shared_ptr<Model>);
    ~Controller();
    bool getCommand();

private:
    std::shared_ptr<Model> model_;
    std::unique_ptr<Interpreter> inter_;
};

#endif
