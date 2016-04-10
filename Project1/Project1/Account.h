#pragma once

#include <string>
class Account
{
public:
	Account(std::string, std::string, std::string);
	~Account();
	std::string getLogin();
	std::string getPass();
	std::string getIP();
private:
	std::string login;
	std::string pass;
	std::string lastIP;
};

