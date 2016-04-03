#pragma once

#include <mutex>
#include <thread>
#ifdef __linux__
#include <sys/time.h>
#endif
#include "Client.h"
#include "PracticalSocket.h"


class ServerManager {
private : 
	TCPServerSocket servSock;
	int defaultPort = 9999;

	const int maxClients = 100;
	Client * clientList;
	Client * dummyClient;

	bool serverStatus = true;

#ifdef __linux__
	fd_set descSet;
#endif

public:
	ServerManager() : servSock(defaultPort), serverStatus(false), clientList(NULL) {};
	ServerManager(int port) : servSock(port) {};
	~ServerManager();
	void acquireClient(Client & inClient);
	Client* getLastClient();
	bool isRunning();
	void abort();
	void checkSockets();
	//void checkNewConnection();

};