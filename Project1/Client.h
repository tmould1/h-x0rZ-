#pragma once

#include <vector>
#include "PracticalSocket.h"

class Client {
private :
	TCPSocket * mySock;
	//Client * nextClient;

protected:
	Client operator=(const Client obj);
public:
	Client();
	//~Client();
	bool assignSocket(TCPServerSocket & server);
	int getSocket();
//	Client* getNextClient();
	//void setNextClient( Client * next );
};

class ClientManager {
private:
	vector<Client> clientVec;
};