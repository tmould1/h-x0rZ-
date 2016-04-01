#include "Client.h"

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
	nextClient = obj.nextClient;
}

Client* Client::getNextClient() {
	return nextClient;
}

void Client::setNextClient( Client * next) {
	nextClient = next;
}

int Client::getSocket() {
	return (mySock? mySock->getSockDesc() : 0);
}
Client::Client() {
	mySock = NULL;
	nextClient = NULL;
}
