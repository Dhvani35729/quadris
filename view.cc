#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"

#include <iostream>

View::View(Controller *c, Model *m) : model_(m), controller_(c)
{
}

View::~View() {}

void View::update()
{
}
