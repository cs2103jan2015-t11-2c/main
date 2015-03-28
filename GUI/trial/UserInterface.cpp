#pragma once
#include "UserInterface.h"

std::string UserInterface::getFileName(std::string filename){
	std::string file = filename; //getting filename from gui
	_hi = filename;
	return file;				//return filename in std format to use in code
}

std::string UserInterface::runProgram(std::string inputLine){
	std::string outputMessage;
	Messages message;
	Parser parse;
	DataStore data(getFileName(_hi));
	Classes listClass;
	int index = 0;

	do {
		parse.init(inputLine);

		if (parse.isClearScreen(inputLine)) {
			return std::string(100, '\n');
		}
		else {
			index = parse.carryOutCommand(listClass, data);
			outputMessage = message.chosenMessage(index);
			return outputMessage;
		}
	} while (!parse.isRunProgram());
}

void UserInterface::addQuote() {
	_quotes.push_back("\"Mistakes are proof that you are trying\"");
	_quotes.push_back("\"Be kind, for everyone you meet\nis fighting a harder battle.\"");
	_quotes.push_back("\"Never stop doing your best just because\nsomeone doesn't give you credit.\"");
	_quotes.push_back("\"It's not who you are that holds you back,\nit's who you think you're not.\"");
	
	return;
}


std::string UserInterface::quoteOfTheDay() {
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