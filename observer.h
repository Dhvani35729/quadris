#ifndef OBSERVER_H
#define OBSERVER_H

// Observer
class Observer
{
public:
    // update method to be overriden by each derived class
    // called by Subject
    virtual void update() = 0;
};

#endif