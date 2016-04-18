
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

	cmdPrototypes.push_back( new LoginCommand() );
	cmdMap["Login"] = cmdPrototypes.at( cmdPrototypes.size() );
	cmdPrototypes.push_back(new NewAccountCommand());
	cmdMap["NewAccount"] = cmdPrototypes.at(cmdPrototypes.size());
	cmdPrototypes.push_back(new LoginCheckCommand());
	cmdMap["LoginCheck"] = cmdPrototypes.at(cmdPrototypes.size());
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

string ServerManager::GetMsgFromSocket(HaxorSocket & inSock) {
	return inSock.Receive();
}
void ServerManager::SendMessageToSocket(HaxorSocket & inSock, string message) {
	inSock.Send(message);
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
	string cmdName;
	Command* tempCmd;
	bool success = false;

	// Lock ServerManager Data

	// Associate Socket with Client, then work on Client
	if (newClient.assignSocket(*servSock)) {
		cout << " Socket Assignment Success for " << newClient.getAccount().getIP << endl;
	}
	// Receive Login or NewAccount
	initMsgBuff = newClient.getSocket().Receive();
	newClient.getSocket();
	
	// Build Command for either
	if (initMsgBuff.find("Login") != std::string::npos) {
		tempCmd = cmdMap["Login"]->Clone();
	}
	else if (initMsgBuff.find("NewAccount") != std::string::npos) {
		tempCmd = cmdMap["NewAccount"]->Clone();
	}
	tempCmd->Initialize(initMsgBuff);
	success = tempCmd->Execute();
	// Send Result?  Or have the Command return the result
	if (success) {
		delete tempCmd;
		tempCmd = cmdMap["LoginCheck"]->Clone();
		tempCmd->GetClient(newClient);
		tempCmd->Initialize(initMsgBuff);
		tempCmd->Execute();

		// Acquire the Client
		acquireClient(newClient);
	}



	// Unlock ServerManager Data
}
// checkAccount(),
// In:  name, pass, IP
// Out:  <int> status : 0 - Account DNE
//                     -1 - Incorrect Password
//						1 - Success!
int ServerManager::checkAccount(std::string, std::string, std::string){
	int status = 0;
	if( )
}