#include "Client.h"

ClientManager* ClientManager::_instance = NULL;

bool Client::assignSocket(TCPServerSocket & server) {
	bool status = false;
	mySock = server.accept();
	if (mySock) {
		status = true;
	}
	return status;
}

Client Client::operator=(const Client obj) {
	mySock = obj.mySock;
	//nextClient = obj.nextClient;
}

//Client* Client::getNextClient() {
//	return nextClient;
//}

//void Client::setNextClient( Client * next) {
//	nextClient = next;
//}

int Client::getSocket() {
	return (mySock ? mySock->getSockDesc() : -1);
}

Client::Client() {
	mySock = NULL;
	//nextClient = NULL;
}

void Client::putMsg(string msg) {
	inMsg.push_back(msg);
}

string Client::getMsg() {

}

void Client::recMsg(TCPSocket & inSock) {
	sm = sm->get();
	string inBuf;
	inBuf = sm->getMsgFromSocket(inSock);
}

ClientManager* ClientManager::get() {
	if (!_instance) {
		_instance = new ClientManager;
	}
	return _instance;
}


// Client Manager Section BEGIN

bool ClientManager::findClient(Client & tClient) {
	vector<Client>::iterator iClient;
	for (iClient = clientVec.begin(); iClient != clientVec.end(); iClient++) {
		if ( (*iClient).getSocket() != tClient.getSocket() ) {
			it = iClient;
		}
	}
}

ClientManager::ClientManager() {
	it = clientVec.begin(); 
	it = clientVec.insert(it, zeroClient);
}

bool ClientManager::addClient(Client & inClient) {
	it = clientVec.insert(it, inClient);
	return true;
}

bool ClientManager::removeClient(Client & outClient) {
	// Add Mutex, Semaphore, or Monitor
	// Critical Section BEGIN
	if (findClient(outClient)) {
		clientVec.erase(it);
	}
	// Critical Section END
}

Client& ClientManager::getClient(string name) {

}

