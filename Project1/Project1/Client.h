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
	vector<Client>::iterator it;
	Client zeroClient;
protected:
	bool findClient(Client & tClient);
public:
	ClientManager();
	bool addClient(Client & inClient);
	bool removeClient( Client & outClient );
	Client & getClient( string name );

};