#pragma once

#include <string>

class HaxorSocket
{
private:
	int socketID;
public:
	virtual void Socket() = 0;
	virtual void Connect() = 0;
	virtual std::string Receive() = 0;
	virtual void Send(std::string Msg) = 0;
};

