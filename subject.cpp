#include <set>

#include "subject.h"
#include "observer.h"

// subscribe to the observer
void Subject::subscribe(Observer *newView)
{
    observers_.insert(newView);
}

// unsubscribe to the observer
void Subject::unsubscribe(Observer *formerView)
{
    observers_.erase(formerView);
}

// notify all observers
void Subject::notify()
{
    Observers::iterator i;
    for (i = observers_.begin(); i != observers_.end(); i++)
    {
        (*i)->update();
    }
}