#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H

class Model;

// Controller
class Controller
{
public:
    Controller(Model *);

private:
    Model *model_;
};

#endif