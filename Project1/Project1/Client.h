#pragma once

#include <vector>
#include "PracticalSocket.h"
#include "ServerManager.h"
#include "Account.h"
#include "HaxorSocket.h"
#include "Command.h"

class Command;
class ServerManager;
class Account;

class Client {
private :
	SocketAdapter * mySock;
	vector<Command*> inMsg; // From Client to Server ( Messages to read and inform Server )
	vector<Command*>::iterator msgIter;
	vector<Command*> outMsg; // From Server to Client ( Messages to send to client from server )
	ServerManager * sm;
	Account * account;


public:
	Client operator=(const Client obj);
	Client();
	~Client();
	bool assignSocket(TCPServerSocket * server);
	int getSocketID();
	void putMsg(vector<string>&, string msg);
	string getMsg(vector<string>&);
	void recMsg(vector<string>&);
	Account & getAccount();
	void setAccount(Account &);
	HaxorSocket & getSocket();
};

class ClientManager {
private:
	static ClientManager* _instance;
	vector<Client*> clientVec;
	vector<Client*>::iterator it;
	Client zeroClient();
protected:
	bool findClient(Client & tClient);
public:
	static ClientManager* get();
	ClientManager();
	~ClientManager();
	bool addClient(Client & inClient);
	bool removeClient( Client & outClient );
	Client & getClient( string name );
	Client * findClientById(int tID);

};


