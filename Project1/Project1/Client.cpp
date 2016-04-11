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

int Client::getSocketID() {
	return (mySock ? mySock->getSockDesc() : -1);
}

TCPSocket& Client::getSocket() {
	return *mySock;
}

Client::Client(){

	mySock = NULL;
//	socketSubject.setState(mySock);
	//nextClient = NULL;
}
Client::~Client() {

}

void Client::putMsg(vector<string> & msgVector, string msg) {
	// Mutex Lock
	msgVector.push_back(msg);
	// Mutex Unlock
}

string Client::getMsg( vector<string> & msgVector) {
	// Mutex Lock
	string temp = msgVector.front();
	msgVector.erase(inMsg.begin());
	//Mutex Unlock
	return temp;
}

void Client::recMsg(vector<string> & msgBuffer) {
	sm = sm->get();
	putMsg(msgBuffer, sm->getMsgFromSocket(*mySock));
}

Account& Client::getAccount() {
	return *account;
}

void Client::setAccount(Account& inAcct) {
	account = &inAcct;
}




ClientManager* ClientManager::get() {
	if (!_instance) {
		_instance = new ClientManager;
	}
	return _instance;
}


// Client Manager Section BEGIN

bool ClientManager::findClient(Client & tClient) {
	bool status = false;
	vector<Client>::iterator iClient;
	for (iClient = clientVec.begin(); iClient != clientVec.end(); iClient++) {
		if ( (*iClient).getSocket() == tClient.getSocket() ) {
			it = iClient;
			status = true;
		}
	}
	//foreach (Client iClient : clientVec) {
	//for ( auto iClient : clientVec ){
	//  if (iClient.getSocket() == tClient.getSocket()) {
	//		it = clientVe);
	//		status = true;
	//	}
	//}
	return status;
}

ClientManager::ClientManager() {
	it = clientVec.begin(); 
	it = clientVec.insert(it, zeroClient);
}

ClientManager::~ClientManager() {
	delete _instance;
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
	return zeroClient;
}

