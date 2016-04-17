#include "Account.h"



Account::Account(std::string inLogin, std::string inPass, std::string inIP, std::string inEmail, bool inAdmin)
{
	login = inLogin;
	pass = inPass;
	lastIP = inIP;
	email = inEmail;
	admin = inAdmin;
}


Account::~Account()
{
}

std::string Account::getLogin() {
	return login;
}
std::string Account::getPass() {
	return pass;
}
std::string Account::getIP() {
	return lastIP;
}

std::string Account::getEmail() {
	return email;
}

bool Account::isAdmin() {
	return admin;
}

void Account::Report(std::ostream & oStrm) {
	oStrm << getLogin() << std::endl;
	oStrm << getPass() << std::endl;
	oStrm << getIP() << std::endl;
	oStrm << getEmail() << std::endl;
	oStrm << isAdmin() << std::endl;
}
