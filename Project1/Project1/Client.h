#pragma once

#include <vector>
#include "PracticalSocket.h"
#include "ServerManager.h"
#include "Subject.h"
#include "Observer.h"
#include "Account.h"

class Account;
class ServerManager;

class Client {
private :
	TCPSocket * mySock;
	//Client * nextClient;
	vector<string> inMsg; // From Client to Server ( Messages to read and inform Server )
	vector<string>::iterator msgIter;
	vector<string> outMsg; // From Server to Client ( Messages to send to client from server )
	ServerManager * sm;
	Account * account;
//	SocketSubject socketSubject;


public:
	Client operator=(const Client obj);
	Client();
	~Client();
	bool assignSocket(TCPServerSocket & server);
	int getSocket();
	void putMsg(vector<string>&, string msg);
	string getMsg(vector<string>&);
	void recMsg(vector<string>&);
	Account & getAccount();
	void setAccount(Account &);
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
	~ClientManager();
	bool addClient(Client & inClient);
	bool removeClient( Client & outClient );
	Client & getClient( string name );

};


