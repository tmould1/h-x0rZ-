#pragma once

#include <mutex>
#include <thread>
#include <map>
#include <vector>
#ifdef __linux__
#include <sys/time.h>
#endif

#include "PracticalSocket.h"
#include "Client.h"
#include "Account.h"

class Command;
class ClientManager;
class Client;
class HaxorSocket;
const int maxClient = 100;
const int defaultPort = 9999;

class ServerManager {
private :
        mutex mtx;
	static ServerManager* _instance;

	TCPServerSocket * servSock;
	int port;

	int maxClients;

	bool serverStatus;

	ClientManager * cm;

	vector<Command *>* cmdPrototypes;

	std::map<std::string, Command *>* cmdMap;

#ifdef __linux__
	fd_set descSet;
#endif

public:
	static ServerManager* get();
	ServerManager();
	ServerManager(int port);
	~ServerManager();
	void acquireClient(Client & inClient);
	//Client* getLastClient();
	bool isRunning();
    void setRunning();
	void abort();
	void checkSockets();
	string GetMsgFromSocket(HaxorSocket & inSock);
	void SendMessageToSocket(HaxorSocket & inSock, string message);
	//void checkNewConnection();
	void registerClientManager();
	bool AddAccount(Account & newAccount);
	bool checkAccount(std::string, std::string, std::string);
	void threadNewConnection(int clientID);
        static void newConnectionThreadWrapper(int clientID);
};


