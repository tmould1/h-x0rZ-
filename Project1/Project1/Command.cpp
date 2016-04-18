#include "Command.h"



Command::Command()
{
	argList = new vector<std::string>();
	// Populate arglist from CmdList
}

void Command::GetClient(Client & actor) {
	clientActor = &actor;
}

void Command::Initialize(string inArgs) {
	cmdArgs = inArgs;
	splitArgs();
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

bool NewAccountCommand::Execute() {
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

bool LoginCommand::Execute() {
	bool status = false;
	ServerManager * sm = sm->get();

	sm->checkAccount(argList->at(1), argList->at(2), argList->at(3));
}

void LoginCheckCommand::Initialize(string inArgs) {
	cmdArgs = inArgs;
	splitArgs();
}
bool LoginCheckCommand::Execute() {

	if (cmdArgs.find("Login") != std::string::npos) {
		sm->SendMessageToSocket(clientActor->getSocket(), "LoginCheck Login 1");
	}
	else if (cmdArgs.find("NewAccount") != std::string::npos) {
		sm->SendMessageToSocket(clientActor->getSocket(), "LoginCheck NewAccount 1");
	}

}