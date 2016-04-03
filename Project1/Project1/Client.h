#pragma once

#include <vector>
#include "PracticalSocket.h"
#include "ServerManager.h"

class Client {
private :
	TCPSocket * mySock;
	//Client * nextClient;
	vector<string> inMsg;
	vector<string>::iterator msgIter;
	ServerManager * sm;

public:
	Client operator=(const Client obj);
	Client();
	//~Client();
	bool assignSocket(TCPServerSocket & server);
	int getSocket();
	void putMsg(string msg);
	string getMsg();
	void recMsg(TCPSocket & inSock);
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
