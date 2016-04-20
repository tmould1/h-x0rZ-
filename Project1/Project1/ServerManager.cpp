
#include "ServerManager.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/stat.h>


ServerManager* ServerManager::_instance = NULL;

const char * accountDir = "../accounts/";

bool exists(const std::string& );

ServerManager::ServerManager() {
	servSock = new TCPServerSocket(9999);
	serverStatus = true;

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
}

ServerManager::~ServerManager() {
	delete servSock;
}

void ServerManager::acquireClient(Client & inClient) {
	cm->addClient(&inClient);
}

void ServerManager::releaseClient(Client * outClient) {
	cm->removeClient(*outClient);
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

void ServerManager::initializeFDSets() {
#ifdef __linux__
	FD_ZERO(&inSet);
	FD_ZERO(&outSet);
	FD_ZERO(&excSet);
#endif
}

void ServerManager::getNewSockets() {
#ifdef __linux__
	FD_SET(maxDesc = servSock->getSockDesc(), &inSet); 
#endif
}

void ServerManager::handleNewConnection() {
#ifdef __linux__
        Client * dummyClient;
	// If Server Socket has something, it's a new connection
	if (FD_ISSET(servSock->getSockDesc(), &inSet)) {
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

void ServerManager::Select() {
#ifdef __linux__
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 500000;

	select(maxDesc + 1, &inSet, NULL, NULL, &tv);
#endif

}
void ServerManager::checkSockets() {
	int sd;

	// Zero the Set out
	initializeFDSets();

	cm->populateFDSets();
	// Select Interface Populates File Descriptor Lists with Info
	// Concerning: New Connections, Sockets with Inbound Messages, and Sockets with Outbound Messages
	Select();

	// Populate new Connections
	getNewSockets();
}

void ServerManager::getInput() {
	handleNewConnection();
//	cm->handleExceptions();
	//Check 
        // cm->getInputFromClients();

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
        cm->Initialize();
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
	//else if (initMsgBuff.find("NewAccount") != std::string::npos) {
	//	tempCmd = (*cmdMap)["NewAccount"]->Clone();
	//}
	else {
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

void ServerManager::setDescriptor(HaxorSocket * thisSocket) {
#ifdef __linux__
        if ( thisSocket->IsSet() ) {
	if (maxDesc < thisSocket->GetID()) {
		maxDesc = thisSocket->GetID();
	}
	FD_SET(thisSocket->GetID(), &inSet);
	FD_SET(thisSocket->GetID(), &outSet);
	FD_SET(thisSocket->GetID(), &excSet);
        }

#endif
}

void ServerManager::HandleExceptionSockets(HaxorSocket * thisSocket) {

#ifdef __linux__
        if( thisSocket->IsSet() ) {
		if (FD_ISSET(thisSocket->GetID(), &excSet)) {
			FD_CLR(thisSocket->GetID(), &inSet);
			FD_CLR(thisSocket->GetID(), &outSet);
		}
        }
#endif

}
