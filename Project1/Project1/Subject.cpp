#include "Subject.h"



Subject::Subject()
{
	observers = new std::list<Observer*>();
}


Subject::~Subject()
{
	delete observers;
}

void Subject::notify() {
	std::list<Observer*>::iterator o = observers->begin();
	while (o != observers->end()) {
		(*o)->update();
	}

	//for ( auto o : Obser)

}

void Subject::attach(Observer & observer) {
	observers->push_back(&observer);
}

void Subject::detach(Observer & observer) {
	observers->remove(&observer);
}
