#include "Account.h"



Account::Account(std::string inLogin, std::string inPass, std::string inIP)
{
	login = inLogin;
	pass = inPass;
	lastIP = inIP;
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