#include "Account.h"



Account::Account(std::string inLogin, std::string inPass, std::string inIP, bool inAdmin)
{
	login = inLogin;
	pass = inPass;
	lastIP = inIP;
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

bool Account::isAdmin() {
	return admin;
}