#pragma once

#include <string>

class TCPSocket;

class HaxorSocket
{
public:
	int socketID;
	virtual void Socket() = 0;
//	virtual void Connect() = 0;
	virtual std::string Receive() = 0;
	virtual void Send(std::string Msg) = 0;
	virtual void Initialize(TCPSocket * tcpSockPtr) = 0;
	virtual bool IsSet() = 0;
	virtual int GetID() = 0;
	virtual void Close() = 0;
};

