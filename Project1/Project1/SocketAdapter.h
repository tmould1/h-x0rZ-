#pragma once
#include "HaxorSocket.h"
#include "PracticalSocket.h"
class SocketAdapter :
	private HaxorSocket
{
public:
	SocketAdapter();
	~SocketAdapter();
	void Send(std::string msg);
	std::string Receive();
	void Socket();
	void Initialize(TCPSocket * tcpSockPtr);
	bool isSet();
	int GetID() {
		return adaptee->getSockDesc();
	}
private:
	TCPSocket* adaptee;
	int msgLength = 1024;
	bool set = false;
};

