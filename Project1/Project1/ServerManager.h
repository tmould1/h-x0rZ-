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
#include "Lobby.h"

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
	vector<Command *> inBox;
	vector<Command *>::iterator inBoxIterator;
	vector<Command *> outBox;
	vector<Command *>::iterator outBoxIterator;

	std::map<std::string, Command *>* cmdMap;

	Lobby * mainLobby;

#ifdef __linux__
	fd_set inSet, outSet, excSet;
#endif
	int maxDesc;

public:
	static ServerManager* get();
	ServerManager();
	ServerManager(int port);
	~ServerManager();
	void acquireClient(Client & inClient);
	void releaseClient(Client * outClient);
	bool isRunning();
    void setRunning();
	void abort();
	void checkSockets();
	string GetMsgFromSocket(HaxorSocket & inSock);
	void SendMessageToSocket(HaxorSocket & inSock, string message);
	void registerClientManager();
	bool AddAccount(Account & newAccount);
	bool checkAccount(std::string, std::string, std::string);
	void threadNewConnection(int clientID);
    static void newConnectionThreadWrapper(int clientID);
	void initializeFDSets();
	void getNewSockets();
	void handleNewConnection();
	void setDescriptor(HaxorSocket *);
	void HandleExceptionSockets(HaxorSocket *);
	void Select();
	void checkInSet(HaxorSocket *);
	void checkOutSet(HaxorSocket *);

	void processInput();  // During Input Processing; Clone Needed Commands, Initializing, getClient, Insert to InBox
	void gameUpdate();    // Iterate through InBox: Executing Commands,
	                      //  Possibly cloning, init, getclient on outCommands and populating outBox
	void handleOutput();  // Iterate through outBox:  Executing Commands

	Command * getCommandClone(string cmdName);
};


