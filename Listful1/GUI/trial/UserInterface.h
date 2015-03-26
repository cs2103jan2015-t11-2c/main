#pragma once

#include "Headers.h"
#include "Quotes.h"

class UserInterface
{
private:
	std::vector<std::string> _quotes;
public:
	UserInterface(void);
	~UserInterface(void);

	std::string runProgram(std::string inputLine);
	std::string qotd();
	
};

