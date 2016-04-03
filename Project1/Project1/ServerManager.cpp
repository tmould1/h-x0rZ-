#include "ServerManager.h"

ServerManager* ServerManager::_instance = NULL;

ServerManager::~ServerManager() {
	//Client * tmp = clientList;
	//while (tmp) {
	//	//dummyClient = tmp->getNextClient();
	//	delete tmp;
	//	tmp = dummyClient;
	//}
}

void ServerManager::acquireClient(Client & inClient) {
	//Client * lastClient;
	//if (!clientList) {
	//	clientList = &inClient;
	//}
	//else {
	//	lastClient = getLastClient();
	//	lastClient->setNextClient(&inClient);
	//}
}

//Client* ServerManager::getLastClient() {
//	Client * clientIterator = clientList;
//	while (clientIterator->getNextClient()) {
//		clientIterator = clientIterator->getNextClient();
//	}
//	return clientIterator;
//}

bool ServerManager::isRunning() {
	return serverStatus;
}

void ServerManager::abort() {
	serverStatus = false;
}

void ServerManager::checkSockets() {
	//Client * temp = clientList;
	int maxDesc, sd, serverSocket = servSock.getSockDesc();
#ifdef __linux__
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 50;
#endif

#ifdef __linux__
	// Zero the Set out
	FD_ZERO(&descSet);
	// But the Server Listening Port in the Set to Check
	FD_SET(maxDesc = serverSocket, &descSet);
#endif

	// Get all the Clients
//	while (temp) {
//#ifdef __linux__
//		sd = temp->getSocket();
//		FD_SET(sd, &descSet);
//		if (sd > maxDesc) {
//			maxDesc = sd;
//		}
//#endif
//		//temp = temp->getNextClient();
//	}

	// Wait for activity on sockets
#ifdef __linux__
	select(maxDesc + 1, &descSet, NULL, NULL, &tv);

	// If Server Socket has something, it's a new connection
	if (FD_ISSET(serverSocket, &descSet)) {
//		dummyClient = new Client();
//		dummyClient->assignSocket(this->servSock);
//		temp = getLastClient();
//		temp->setNextClient(dummyClient);
	}

	// Otherwise it is I/O

#endif

}

ServerManager* ServerManager::get() {
	if (_instance == NULL) {
		_instance = new ServerManager;
	}
	return _instance;
}

string ServerManager::getMsgFromSocket(TCPSocket & inSock) {
	int msgLength;
	const int maxBuf = 255;
	char buf[maxBuf];
	string fMsg;
	size_t len;

	while (inSock.recv(buf, maxBuf) > 0) {
		len = strlen(buf);
		msgLength += len;
		fMsg.append(buf);
		std::fill(buf, buf + len, 0);
	}
	return fMsg;
}
