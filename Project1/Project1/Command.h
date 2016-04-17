#pragma once
#include <string>
#include <vector>
#include "ServerManager.h"

class Command
{
protected:
	vector<std::string> * argList;
public:
	Command(string CmdList)
	{
		argList = new vector<std::string>();
		// Populate arglist from CmdList
	}

	~Command();
	virtual bool Execute() = 0;
	virtual Command* Clone() = 0;
};

class NewAccountCommand : public Command {
public:
	NewAccountCommand() {

	}
	NewAccountCommand(string n, string p, string i, string e, string a) {
		argList->push_back(n);
		argList->push_back(p);
		argList->push_back(i);
		argList->push_back(e);
		argList->push_back(a);
	}
	bool Execute() {
		ServerManager * sm = sm->get();
		Account * tempAccount;
		string name, pass, ip, email, admin;
		bool bAdmin = false;
		bool success = false;
		name = argList->at(0);
		pass = argList->at(1);
		ip = argList->at(2);
		email = argList->at(3);
		admin = argList->at(4);
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
	LoginCommand() {

	}
	LoginCommand(string n, string p, string i) {
		argList->push_back(n);
		argList->push_back(p);
		argList->push_back(i);
	}
	bool Execute() {
		bool status = false;
		ServerManager * sm = sm->get();

		sm->checkAccount(argList->at(0), argList->at(1), argList->at(2));
	}
	Command * Clone() {
		return new LoginCommand();

	}
};

class LoginCheckCommand : public Command {
	HaxorSocket* toConnect;
	ServerManager * sm = sm->get();
public:
	bool Execute() {
		sm->SendMessageToSocket()
	}
	Command * Clone() {
		return new LoginCheckCommand();
	}
};
