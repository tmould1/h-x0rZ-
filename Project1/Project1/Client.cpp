#include "Client.h"

ClientManager* ClientManager::_instance = NULL;

bool Client::assignSocket(TCPServerSocket & server) {
	bool status = false;
	mySock->Initialize(server.accept());
	if (mySock->IsSet()) {
		status = true;
	}
	return status;
}

Client Client::operator=(const Client obj) {
	mySock = obj.mySock;
}

int Client::getSocketID() {
	return (mySock->IsSet() ? mySock->GetID(): -1);
}

HaxorSocket& Client::getSocket() {
	return *mySock;
}

Client::Client(){
	mySock = NULL;
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
	msgVector.erase(msgVector.begin());
	//Mutex Unlock
	return temp;
}

void Client::recMsg(vector<string> & msgBuffer) {
	sm = sm->get();
	putMsg(msgBuffer, sm->GetMsgFromSocket(*mySock));
}

Account& Client::getAccount() {
	return *account;
}

void Client::setAccount(Account& inAcct) {
	account = &inAcct;
}




ClientManager* ClientManager::get() {
	if (!_instance) {
		_instance = new ClientManager();
	}
	return _instance;
}


// Client Manager Section BEGIN

bool ClientManager::findClient(Client & tClient) {
	bool status = false;
	vector<Client>::iterator iClient;
	for (iClient = clientVec.begin(); iClient != clientVec.end(); iClient++) {
		if ( (*iClient).getSocketID() == tClient.getSocketID() ) {
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

