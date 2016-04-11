#pragma once
#include <vector>
#include <list>
#include "Observer.h"

class Subject
{
private:
	std::list<Observer*>* observers;
public:
	Subject();
	~Subject();
	virtual void attach(Observer & observer);
	virtual void detach(Observer & observer);
	virtual void notify();
};

// To Set up a SocketSubject,
//  In the class containing a TCPSocket instance.
//  SocketSubject thisSocketSubject = new SocketSubject();
//  thisSocketSubject.setState( &actualTCPSocket );

//class SocketSubject : public Subject {
//private :
//	TCPSocket* socketState;
//public :
//	TCPSocket* getState() {
//		return (socketState);
//	}
//	void setState(TCPSocket* toState) {
//		socketState = toState;
//	}
//};

