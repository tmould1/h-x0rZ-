#include "NewAccountCommand.h"



NewAccountCommand::NewAccountCommand()
{
}


NewAccountCommand::~NewAccountCommand()
{
}


void NewAccountCommand::Execute(std::string login, std::string password, std::string IP)
{
	Account* tempAccount = new Account(login, password, IP);
	serverBoss->AddAccount(*tempAccount);
	delete tempAccount;
}
