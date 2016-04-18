#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "ServerManager.h"
#include "Client.h"

class Command
{
protected:
	vector<std::string> * argList;
	string cmdArgs;
	Client * clientActor;
public:
	Command();
	virtual void GetClient(Client & actor);
	virtual void Initialize(string inArgs);
	void splitArgs();

	~Command();
	virtual bool Execute() = 0;
	virtual Command* Clone() = 0;
};

class NewAccountCommand : public Command {
public:
	bool Execute();
	Command * Clone() {
		return new NewAccountCommand();
	}
};

class LoginCommand : public Command {
public:
	bool Execute();
	Command * Clone() {
		return new LoginCommand();
	}
};

class LoginCheckCommand : public Command {
	ServerManager * sm = sm->get();

public:
	void Initialize(string inArgs);
	bool Execute();
	Command * Clone() {
		return new LoginCheckCommand();
	}
};
