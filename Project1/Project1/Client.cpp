#include "Client.h"

ClientManager* ClientManager::_instance = NULL;

Player* Client::GetPlayer() {
	return player;
}

std::string Client::GetName(){
	account->getLogin();
}

bool Client::assignSocket(TCPServerSocket * server) {
	bool status = false;
	mySock->Initialize(server->accept());
	if (mySock->IsSet()) {
		status = true;
	}
	return status;
}

Client Client::operator=(const Client obj) {
	mySock = obj.mySock;
	return *this;
}

int Client::getSocketID() {
        int result = -1;
	if ( mySock != NULL && mySock->IsSet() ) {
	  result = mySock->GetID();
        }
	return result;
}

HaxorSocket& Client::getSocket() {
	return *mySock;
}

Client::Client(){
	mySock = new SocketAdapter();
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



// Client Manager Section BEGIN

ClientManager* ClientManager::get() {
	if ( _instance == NULL ) {
		_instance = new ClientManager();
	}
	return _instance;
}

bool ClientManager::findClient(Client & tClient) {
	bool status = false;
	vector<Client*>::iterator iClient;
	for (iClient = clientVec.begin(); iClient != clientVec.end(); iClient++) {
		if ( (*iClient)->getSocketID() == tClient.getSocketID() ) {
			it = iClient;
			status = true;
			break;
		}
	}
	return status;
}

Client* ClientManager::findClientByID(int tID) {
	vector<Client*>::iterator iClient;
	for (iClient = clientVec.begin(); iClient != clientVec.end(); iClient++) {
		if ((*iClient)->getSocketID() == tID) {
			it = iClient;
			break;
		}
	}
	return (*it);
}

ClientManager::ClientManager() {
    Client * firstClient = new Client();
	it = clientVec.begin();
	it = clientVec.insert(it, firstClient);
}

void ClientManager::Initialize(){
	sm = sm->get();
}



ClientManager::~ClientManager() {
	delete _instance;
}

bool ClientManager::addClient(Client * inClient) {
	it = clientVec.insert(it, inClient);
	return true;
}

bool ClientManager::removeClient(Client & outClient) {
	bool status = false;
	// Add Mutex, Semaphore, or Monitor
	// Critical Section BEGIN
	// Clean up and Remove the Client
	if (findClient(outClient)) {
		outClient.getSocket().Close();
		clientVec.erase(it);
		status = true;
	}
	// Critical Section END
	return status;
}

Client& ClientManager::getClient(string name) {
	return *(new Client());
}

void ClientManager::populateFDSets() {
	for (it = clientVec.begin(); it != clientVec.end(); it++) {
		sm->setDescriptor(&(*it)->getSocket());
	}

}

void ClientManager::handleExceptions() {
	for (it = clientVec.begin(); it != clientVec.end(); it++) {
		sm->HandleExceptionSockets(&(*it)->getSocket());
		// Save Client
		// Safely Remove Client
		removeClient(**it);
	}
}

void ClientManager::getInputFromClients() {
	for (it = clientVec.begin(); it != clientVec.end(); it++) {
		sm->checkInSet(&(*it)->getSocket());
	}
}
