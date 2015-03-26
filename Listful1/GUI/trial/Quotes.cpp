#include "Quotes.h"


Quotes::Quotes(void)
{
}


Quotes::~Quotes(void)
{
}

void Quotes::addQuote() {
	_quotes.push_back("\"Mistakes are proof that you are trying\"");
	_quotes.push_back("\"Be kind, for everyone you meet\nis fighting a harder battle.\"");
	_quotes.push_back("\"Never stop doing your best just because\nsomeone doesn't give you credit.\"");
	_quotes.push_back("\"It's not who you are that holds you back,\nit's who you think you're not.\"");
	
	return;
}


std::string Quotes::quoteOfTheDay() {
	srand(time(NULL));
	
	int randNum;
	addQuote();
	int size = _quotes.size();
	//get a pseudo random number in [0, size of quote bank]
	for (int i=0; i<30;i++){
		randNum = (rand()%size);
	}
	std::string chosenQuote = _quotes[randNum];

	return chosenQuote;
}