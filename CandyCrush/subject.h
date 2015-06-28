#ifndef SUBJECT
#define SUBJECT

#include "QHeaderfile.h"

using namespace std;

class Observer;

class Subject {
public:
    Subject();

    void notifyObs();
    void registerObs(Observer *observers);

private:
    vector<Observer*> observers;
};

#endif // SUBJECT

