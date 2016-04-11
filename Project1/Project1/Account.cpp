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
	oStrm << "Name : " << getLogin() << std::endl;
	oStrm << "Pass : " << getPass() << std::endl;
	oStrm << "Last IP: " << getIP() << std::endl;
	oStrm << "Email : " << getEmail() << std::endl;
	oStrm << "admin ? " << isAdmin() << std::endl;
}
