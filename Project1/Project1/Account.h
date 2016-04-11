#pragma once

#include <string>
class Account
{
public:
	Account(std::string, std::string, std::string, std::string, bool);
	~Account();
	std::string getLogin();
	std::string getPass();
	std::string getIP();
	std::string getEmail();
	bool isAdmin();
private:
	std::string login;
	std::string pass;
	std::string lastIP;
	std::string email;
	bool admin;
};

