#include "UserInterface.h"

void UserInterface::printStarRow(){
	for (int i=0; i<80; i++){
		std::cout << "*" ;
	}
	return;
}

void UserInterface::centralizePrintToUser(std::string text) {
	int position = (80-text.size())/2;

	for (int i=0; i<position; i++){
		std::cout << " ";
	}
	std::cout << text <<std::endl;
	return;
}

void UserInterface::printToUser(std::string text) {
	std::cout << text << std::endl;
	return;
}

void UserInterface::addQuote() {
	_quotes.push_back("Mistakes are proof that you are trying");
	_quotes.push_back("Be kind, for everyone you meet is fighting a harder battle.");
	_quotes.push_back("Never stop doing your best just because someone doesn't give you credit.");
	_quotes.push_back("It's not who you are that holds you back, it's who you think you're not.");
	return;
}

std::string UserInterface::quoteOfTheDay() {
	srand(time(NULL));
	int randNum;

	//get a pseudo random number in [0, size of quote bank]
	for (int i=0; i<30;i++){
		randNum = (rand()%_quotes.size());
	}
	std::string chosenQuote = _quotes[randNum];

	return chosenQuote;
}

void UserInterface::printSpace(int num) {
	while (num != 0) {
		std::cout << " ";
	}
	return;
}

void UserInterface::userAction() {
	Message message;
	centralizePrintToUser(message.chooseMessage(1));

	std::cout << std::endl << std::setw(10) << "(1) Add" << std::setw(10) << "(2) Display" 
			  << std::setw(10) << "(3) Edit" << std::setw(10) << "(4) Delete" 
			  << std::setw(10) << "(5) Clear" << std::setw(10) << "(6) Search" << std::setw(10) << "(7) Exit" << std::endl;
	return;
}

std::string UserInterface::runProgram(char *argv[]) {
	std::string fileName = argv[1];
	Parser parse;
	DataStore data;
	Classes listClass;
	int messageIndex = 0;
	std::string outputMessage;
	Message message;

	homeScreen();

	do {
		userAction();
		getline(std::cin, _userInput);
		parse.init(_userInput);
		if (parse.isClearScreen(_userInput)) {
			std::cout << std::string(100, '\n');
			homeScreen();
		}
		else {
			messageIndex = parse.carryOutCommand(listClass, data, fileName);
			outputMessage = message.chooseMessage(messageIndex);
			return outputMessage;
		}
	} while (!parse.isRunProgram());
	return;
}

void UserInterface::homeScreen() {
	Message message;
	printStarRow();
	centralizePrintToUser(message.chooseMessage(0));
	printStarRow();

	addQuote();
	centralizePrintToUser(quoteOfTheDay());
	std::cout << std::endl;
	return;
}