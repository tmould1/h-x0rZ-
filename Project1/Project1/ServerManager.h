#pragma once

#include <mutex>
#include <thread>
#ifdef __linux__
#include <sys/time.h>
#endif

#include "PracticalSocket.h"
#include "Client.h"
#include "Account.h"

class Client;
class ClientManager;
class Account;

class ServerManager {
private :
	static ServerManager* _instance;

	TCPServerSocket servSock;
	int defaultPort = 9999;

	const int maxClients = 100;

	bool serverStatus;

	ClientManager * cm;


#ifdef __linux__
	fd_set descSet;
#endif

public:
	static ServerManager* get();
	ServerManager();
	ServerManager(int port) : servSock(port) {};
	~ServerManager();
	void acquireClient(Client & inClient);
	//Client* getLastClient();
	bool isRunning();
        void setRunning();
	void abort();
	void checkSockets();
	string getMsgFromSocket(TCPSocket & inSock);
	//void checkNewConnection();
	void registerClientManager();
	bool AddAccount(Account & newAccount);


};


