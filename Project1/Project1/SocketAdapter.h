#pragma once
#include "HaxorSocket.h"
#include "PracticalSocket.h"
class SocketAdapter :
	public HaxorSocket
{
public:
	SocketAdapter();
	~SocketAdapter();
	void Send(std::string msg);
	std::string Receive();
	void Socket();
	void Initialize(TCPSocket * tcpSockPtr);
	bool IsSet();
	int GetID() {
		return adaptee->getSockDesc();
	}
	void Close();
private:
	TCPSocket* adaptee;
	int msgLength;
	bool set;
};

