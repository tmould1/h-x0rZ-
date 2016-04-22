#pragma once

#include <vector>
#include "PracticalSocket.h"
#include "ServerManager.h"
#include "Account.h"
#include "SocketAdapter.h"
#include "Command.h"
#include "Player.h"

class Command;
class ServerManager;
class Account;
class SocketAdapter;

class Client {
private :
	HaxorSocket * mySock;
	vector<Command*> inMsg; // From Client to Server ( Messages to read and inform Server )
	vector<Command*>::iterator msgIter;
	vector<Command*> outMsg; // From Server to Client ( Messages to send to client from server )
	ServerManager * sm;
	Account * account;
	Player * player;
	std::string name;

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
	Player * GetPlayer();
	std::string GetName();
};

class ClientManager {
private:
	static ClientManager* _instance;
	vector<Client*> clientVec;
	vector<Client*>::iterator it;
	//Client zeroClient();
	ServerManager * sm;
protected:
	bool findClient(Client & tClient);
public:
	static ClientManager* get();
	ClientManager();
	~ClientManager();
	bool addClient(Client * inClient);
	bool removeClient( Client & outClient );
	Client & getClient( string name );
	Client * findClientByID(int tID);
	void populateFDSets();
	void handleExceptions();
	void Initialize();
	void getInputFromClients();
	void CheckInSet();

};


