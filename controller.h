#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H

#include "model.h"
#include "interpreter.h"

class Model;

// Controller
class Controller
{
public:
    Controller(Model *);
    ~Controller();
    void getCommand();

private:
    Model *model_;
    Interpreter *inter_;
};

#endif
