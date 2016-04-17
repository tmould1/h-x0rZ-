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
private:
	TCPSocket* adaptee;
	int msgLength = 1024;
};

