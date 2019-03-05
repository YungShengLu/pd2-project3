#include "subject.h"
#include "observer.h"

Subject::Subject() {

}

void Subject::notifyObs() {
    for (Observer* obs : observers)
        obs->notify();
}

void Subject::registerObs(Observer* obs) {
    observers.push_back(obs);
}
