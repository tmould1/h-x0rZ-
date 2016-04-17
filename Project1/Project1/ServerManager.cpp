
#include "ServerManager.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/stat.h>


ServerManager* ServerManager::_instance = NULL;

const char * accountDir = "../accounts/";

bool exists(const std::string& );

ServerManager::ServerManager() {
	servSock = new TCPServerSocket(defaultPort);
	serverStatus = true;
	cm = cm->get();
}
ServerManager::ServerManager(int port) {
	servSock = new TCPServerSocket(port);
	serverStatus = true;
	cm = cm->get();
}

ServerManager::~ServerManager() {
	//Client * tmp = clientList;
	//while (tmp) {
	//	//dummyClient = tmp->getNextClient();
	//	delete tmp;
	//	tmp = dummyClient;
	//}
	delete servSock;
}

void ServerManager::acquireClient(Client & inClient) {
	cm->addClient(inClient);
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

void ServerManager::setRunning(){
	serverStatus = true;
}

void ServerManager::abort() {
	serverStatus = false;
}

void ServerManager::checkSockets() {
	//Client * temp = clientList;
	int maxDesc, sd, serverSocket = servSock->getSockDesc();
	Client * dummyClient;

#ifdef __linux__
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 100000;
#endif

#ifdef __linux__
	// Zero the Set out
	FD_ZERO(&descSet);
	// But the Server Listening Port in the Set to Check
	FD_SET(maxDesc = serverSocket, &descSet);
#endif

#ifdef __linux__
	select(maxDesc + 1, &descSet, NULL, NULL, &tv);

	// If Server Socket has something, it's a new connection
	if (FD_ISSET(serverSocket, &descSet)) {
		dummyClient = new Client();
		thread newConnThread;
		newConnThread = thread(threadNewConnection, *dummyClient);

		//dummyClient = new Client();
		//if (!dummyClient->assignSocket(*servSock)) {
		//	cout << "Could not assign new Client Socket" << endl;
		//}
		//
		//acquireClient(*dummyClient);
		//dummyClient.mySock->recv()
//		temp = getLastClient();
//		temp->setNextClient(dummyClient);
	}

	// Otherwise it is I/O

#endif

}

ServerManager* ServerManager::get() {
	if (_instance == NULL) {
		_instance = new ServerManager();
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

void ServerManager::registerClientManager() {
	cm = cm->get();
}

bool ServerManager::AddAccount(Account & newAccount) {
	bool status = false;
	ofstream newPlayerFile;
	if (!exists(accountDir + newAccount.getLogin())) {
		newPlayerFile.open(accountDir + newAccount.getLogin());

		if (newPlayerFile.is_open()) {
			cout << "Writing to new File" << endl;
			newAccount.Report(newPlayerFile);
			status = true;
		}
	}
	else {
		cout << newAccount.getLogin() << " account already exists.  Try another Login Name." << endl;
	}
	return status;
}

inline bool exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
// Gets Called in a thread
void ServerManager::threadNewConnection(Client & newClient) {
	string initMsgBuff;
	// Lock ServerManager Data

	// Associate Socket with Client, then work on Client
	if (newClient.assignSocket(*servSock)) {
		cout << " Socket Assignment Success for " << newClient.getSocket().getForeignAddress << endl;
	}

	// Receive Login or NewAccount
	//initMsgBuff = newClient.getSocket().Receive();
	
	// Build Command for either
	// Execute the Command
	// Send Result?  Or have the Command return the result
	// Acquire the Client

	// Unlock ServerManager Data
}