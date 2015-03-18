#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <iomanip>
#include "UserInterface.h"


UserInterface::~UserInterface(void){
}
void UserInterface::printStarRow(){
	for (int i=0; i<80; i++){
		std::cout << "*" ;
	}
}
void UserInterface::centralizeOutput(std::string text){
	int position = (80-text.size())/2;
	for (int i=0; i<position; i++){
		std::cout << " ";
	}
	std::cout << text << std::endl;
	return;
}

void UserInterface::addQuote(){
	_quotes.push_back("Mistakes are proof that you are trying");
	_quotes.push_back("Be kind, for everyone you meet is fighting a harder battle.");
	_quotes.push_back("Never stop doing your best just because someone doesn't give you credit.");
	_quotes.push_back("It's not who you are that holds you back, it's who you think you're not.");
	return;
}


std::string UserInterface::quoteOfTheDay(){
	srand(time(NULL));
	
	int randNum;
	int size = _quotes.size();
	//get a pseudo random number in [0, size of quote bank]
	for (int i=0; i<30; i++){
		randNum = (rand()%size);
	}
	std::string chosenQuote = _quotes[randNum];

	return chosenQuote;
}

int UserInterface::userAction(){
	std::cout << "(1) Add" << std::setw(42) << "(4) Edit" << std::endl;
	std::cout << "(2) Display" << std::setw(40) << "(5) Search" << std::endl;
	std::cout << "(3) Delete" << std::setw(39) << "(6) Save" << std::endl;
	std::cout << "(7) Exit" << std::endl;
	int choiceNum;
	std::cin >> choiceNum;
	return choiceNum;
}

/*int UserInterface::determineCommand(int choiceNum){
	while (choiceNum != 7){
	if (choiceNum < 1 || choiceNum > 7) {
		return commandType::INVALID;
	}
	else {
		switch (choiceNum){
			case 1:
				return commandType::ADD;
			case 2:
				return commandType::DISPLAY;
			case 3:
				return commandType::DELETE;
			case 4:
				return commandType::EDIT;
			case 5:
				return commandType::SEARCH;
			case 6:
				return commandType::SAVE;
			case 7:
				return commandTYPE::EXIT;
		}
	}
}*/

/*void UserInterface::checkFileCreated(std::string &fileName) {
	sprintf_s(messageToUser, MESSAGE_WELCOME.c_str(), fileName.c_str());
	std::cout << messageToUser << "\n";

	std::string content;
	std::string emptystring;
	size_t index;

	readFile.open(fileName);
	while (std::getline(readFile, content)) {
		if (file.empty() && content == emptystring) {
			return;
		}

		index = content.find_first_of(" ");
		content = content.substr((index + 1), content.size() - (index + 1));
		file.push_back(content);
	}
	readFile.close();
}*/