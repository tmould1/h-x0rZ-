#include "Command.h"
#include <iostream>


Command::Command()
{
	argList = new vector<std::string>();
	// Populate arglist from CmdList
}

void Command::GetClient(Client * actor) {
	clientActor = actor;
}

void Command::Initialize(string inArgs) {
	cmdArgs = inArgs;
	splitArgs();
        sm = sm->get();
}

void Command::splitArgs() {
	stringstream ss(cmdArgs);
	string arg;
	char delimiter = ' ';

	while (getline(ss, arg, delimiter)) {
		argList->push_back(arg);
	}
}

Command::~Command()
{
}

// Command Execute Section

bool NewAccountCommand::Execute() {
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

bool LoginCommand::Execute() {
	bool status = false;
	sm->checkAccount(argList->at(1), argList->at(2), argList->at(3));
        status = true;
        return status;
}

bool LoginCheckCommand::Execute() {
	bool status = false;
	if (cmdArgs.find("Login") != std::string::npos) {
		std::cout << "Sending Back Login Success Info" << endl;
		sm->SendMessageToSocket(clientActor->getSocket(), "LoginCheck Login " +argList->at(4));
	}
	else if (cmdArgs.find("NewAccount") != std::string::npos) {
		sm->SendMessageToSocket(clientActor->getSocket(), "LoginCheck NewAccount " + argList->at(4));
	}
	status = true;
	return status;
}
