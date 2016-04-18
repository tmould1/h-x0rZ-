#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "ServerManager.h"

class Command
{
protected:
	vector<std::string> * argList;
	string cmdArgs;
	Client * clientActor;
public:
	Command()
	{
		argList = new vector<std::string>();
		// Populate arglist from CmdList
	}
	virtual void GetClient(Client & actor) {
		clientActor = &actor;
	}
	virtual void Initialize(string inArgs) {
		cmdArgs = inArgs;
		splitArgs();
	}
	void splitArgs( ) {
		stringstream ss(cmdArgs);
		string arg;
		char * delimiter = " ";

		while (getline(ss, arg, *delimiter)) {
			argList->push_back(arg);
		}
	}

	~Command();
	virtual bool Execute() = 0;
	virtual Command* Clone() = 0;
};

class NewAccountCommand : public Command {
public:
	bool Execute() {
		ServerManager * sm = sm->get();
		Account * tempAccount;
		string name, pass, ip, email, admin;
		bool bAdmin = false;
		bool success = false;
		name = argList->at(1);
		pass = argList->at(2);
		ip = argList->at(3);
		email = argList->at(4);
		admin = argList->at(5);
		if (admin == "true") {
			bAdmin = true;
		}
		tempAccount = new Account(name, pass, ip, email, bAdmin);
		if (sm->AddAccount(*tempAccount)) {
			success = true;
			// Success
		}
		else {
			// Failure
		}
		delete tempAccount;
		return success;

	}
	Command * Clone() {
		return new NewAccountCommand();
	}
};

class LoginCommand : public Command {
public:
	bool Execute() {
		bool status = false;
		ServerManager * sm = sm->get();

		sm->checkAccount(argList->at(1), argList->at(2), argList->at(3));
	}
	Command * Clone() {
		return new LoginCommand();

	}
};

class LoginCheckCommand : public Command {
	ServerManager * sm = sm->get();

public:
	void Initialize(string inArgs) {
		cmdArgs = inArgs;
		splitArgs();

	}
	bool Execute() {

		if (cmdArgs.find("Login") != std::string::npos) {
			sm->SendMessageToSocket(clientActor->getSocket(), "LoginCheck Login 1");
		}
		else if (cmdArgs.find("NewAccount") != std::string::npos) {
			sm->SendMessageToSocket(clientActor->getSocket(), "LoginCheck NewAccount 1");
		}

	}
	Command * Clone() {
		return new LoginCheckCommand();
	}
};
