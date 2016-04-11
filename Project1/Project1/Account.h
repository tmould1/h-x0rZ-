#pragma once

#include <string>
#include <ostream>
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
	void Report(std::ostream &);
private:
	std::string login;
	std::string pass;
	std::string lastIP;
	std::string email;
	bool admin;
};

