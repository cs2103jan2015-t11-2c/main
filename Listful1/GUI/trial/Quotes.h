#include "Headers.h"
#include <cstdlib>
#include <ctime>

#pragma once

class Quotes
{
private:
	std::vector <std::string> _quotes;

public:
	Quotes(void);
	~Quotes(void);

	void addQuote();
	std::string quoteOfTheDay();
};

