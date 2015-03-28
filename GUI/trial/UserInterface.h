#pragma once

#include "Parser.h"
#include <ctime>
#include <cstdlib>

class UserInterface
{
private:
		std::vector <std::string> _quotes;

		std::string _userInput;
		std::string _hi;

public:
	UserInterface() {};
	void addQuote();
	std::string quoteOfTheDay();
	std::string getFileName(std::string filename);
	std::string runProgram(std::string inputLine);
	std::string qotd();
	
};


