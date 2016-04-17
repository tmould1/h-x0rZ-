#include "SocketAdapter.h"



SocketAdapter::SocketAdapter()
{
}


SocketAdapter::~SocketAdapter()
{ 
}


void SocketAdapter::Send(std::string msg)
{
	adaptee->send((void *)msg.c_str(), msg.length());
}


std::string SocketAdapter::Receive()
{
	string message;
	char* cmessage;
	adaptee->recv((void *)cmessage, msgLength);
	message = cmessage;
	return message;
}


void SocketAdapter::Socket()
{
	socketID = adaptee->getSockDesc();
}
