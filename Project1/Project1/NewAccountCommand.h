#pragma once
#include "Command.h"
#include "ServerManager.h"


class NewAccountCommand :
	public Command
{
public:
	NewAccountCommand();
	~NewAccountCommand();
private:
	ServerManager *serverBoss;

public:
	void Execute(std::string, std::string, std::string );
};

