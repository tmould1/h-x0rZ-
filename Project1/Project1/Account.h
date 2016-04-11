#pragma once

#include <string>
class Account
{
public:
	Account(std::string, std::string, std::string, bool);
	~Account();
	std::string getLogin();
	std::string getPass();
	std::string getIP();
	bool isAdmin();
private:
	std::string login;
	std::string pass;
	std::string lastIP;
	bool admin;
};

