
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

    cmdPrototypes = new vector<Command*>();
    cmdMap = new std::map<string,Command*>();

	// Load Available Commands
	cmdPrototypes->push_back( new LoginCommand() );
	(*cmdMap)["Login"] = cmdPrototypes->at( cmdPrototypes->size()-1 );
	cmdPrototypes->push_back(new NewAccountCommand());
	(*cmdMap)["NewAccount"] = cmdPrototypes->at(cmdPrototypes->size()-1);
	cmdPrototypes->push_back(new LoginCheckCommand());
	(*cmdMap)["LoginCheck"] = cmdPrototypes->at(cmdPrototypes->size()-1);
}

ServerManager::ServerManager(int port) {
	servSock = new TCPServerSocket(port);
	serverStatus = true;
	cm = cm->get();
}

ServerManager::~ServerManager() {
	delete servSock;
}

void ServerManager::acquireClient(Client & inClient) {
	cm->addClient(&inClient);
}

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
	int maxDesc, sd, serverSocket = servSock->getSockDesc();
	Client * dummyClient;

#ifdef __linux__
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 500000;
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
		int sockID;
		if (dummyClient->assignSocket(servSock)) {
			cm->addClient(dummyClient);
			// Successful Assignment
		}
		sockID = dummyClient->getSocketID();
                cout << "SocketID assigned: " << sockID;
		thread newConnThread(&ServerManager::newConnectionThreadWrapper, sockID);
                newConnThread.detach();
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
void ServerManager::threadNewConnection(int clientID) {
	string initMsgBuff;
	string cmdName;
	Command* tempCmd;
	Client * newClient = cm->findClientById(clientID);
	bool success = false;

        cout << " and new connection thread found " << newClient->getSocketID() << endl;

        while ( !mtx.try_lock() ){
          // Keep Trying!
        }
        // Mutex is Locked

	// Receive Login or NewAccount
//	initMsgBuff = newClient->getSocket().Receive();
	initMsgBuff = "Login Todd Password 127.0.0.1";


	// Build Command for either
	if (initMsgBuff.find("Login") != std::string::npos) {
		tempCmd = (*cmdMap)["Login"]->Clone();
	}
	else if (initMsgBuff.find("NewAccount") != std::string::npos) {
		tempCmd = (*cmdMap)["NewAccount"]->Clone();
	}
	tempCmd->Initialize(initMsgBuff);
	success = tempCmd->Execute();

	// Send Result?  Or have the Command return the result
	delete tempCmd;

	// LoginCheck::Execute() will find initMsgType from initMsgBuff
	tempCmd = (*cmdMap)["LoginCheck"]->Clone();
	tempCmd->GetClient(newClient);

	if (success) {
		tempCmd->Initialize(initMsgBuff + " 1");
		// Acquire the Client
		acquireClient(*newClient);
	}
        else {
		tempCmd->Initialize(initMsgBuff + " 0");
        }

	tempCmd->Execute();
	// Unlock ServerManager Data

        cout << "Finished handling new Connection!" << endl;
	mtx.unlock();
}
// checkAccount(),
// In:  name, pass, IP
// Out:  <int> status : 0 - Account DNE
//                     -1 - Incorrect Password
//						1 - Success!

bool ServerManager::checkAccount(std::string name , std::string pass , std::string IP){
	Account * tAccount = new Account(name,pass,IP, "", 0);
	bool status = 0;
	if (exists(accountDir + tAccount->getLogin())) {
		status = 1;
		if (false) { // password doesn't match

		}
	}
	return status;
}

void ServerManager::newConnectionThreadWrapper( int clientID ){
        ServerManager * sm = sm->get();
	sm->threadNewConnection(clientID);
}
