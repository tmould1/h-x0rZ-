#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include "PracticalSocket.h"

class ServerManager;

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
	static ClientManager* _instance;
	vector<Client> clientVec;
	vector<Client>::iterator it;
	Client zeroClient;
protected:
	bool findClient(Client & tClient);
public:
	static ClientManager* get();
	ClientManager();
	bool addClient(Client & inClient);
	bool removeClient( Client & outClient );
	Client & getClient( string name );

};


#endif
