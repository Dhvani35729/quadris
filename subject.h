#ifndef MVC_SUBJECT_H
#define MVC_SUBJECT_H

#include <set>

class Observer;

// Subject
class Subject
{
public:
    // subscribe to the observer
    void subscribe(Observer *);

    // unsubscribe to the observer
    void unsubscribe(Observer *);

protected:
    // notify all observers
    void notify();

private:
    typedef std::set<Observer *> Observers;
    Observers observers_;
};

#endif