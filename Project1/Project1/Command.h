#pragma once
class Command
{
public:
	Command();
	~Command();
	virtual void Execute() = 0;
};

