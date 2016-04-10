#pragma once
#include <vector>
#include "PracticalSocket.h"

class SocketSubject;
class Observer
{
public:
	virtual void update()=0;
};


// To set up a SocketObserver,
//   In the class needing the information,
//   SocketObserver mySocketObserver = new SocketObserver();
//   mySocketObserver.socketSubject = &thisSocketSubject;
//   thisSocketSubject.attach( mySocketObserver );

class SocketObserver : public Observer {
private:
	int socketState;
public:
	SocketSubject * socketSubject;
	void update() {
		socketState = (int)socketSubject->getState();
	}
};
