#include "UserInterface.h"

const std::string UserInterface::MESSAGE_WELCOME = "*** Welcome to Listful ***";
const std::string UserInterface::MESSAGE_ACTION = "Please choose an action: ";

const std::string UserInterface::MESSAGE_ADD = "added to %s: \"%s\"";
const std::string UserInterface::MESSAGE_DELETE = "deleted from %s: \"%s\"";
const std::string UserInterface::MESSAGE_CLEAR = "all content deleted from %s";
const std::string UserInterface::MESSAGE_EMPTY = "%s is empty";
const std::string UserInterface::MESSAGE_SORT = "%s has been sorted alphabetically";
const std::string UserInterface::MESSAGE_EDIT;
const std::string UserInterface::MESSAGE_SEARCH;
const std::string UserInterface::MESSAGE_UNDO;
const std::string UserInterface::MESSAGE_REDO;

const std::string UserInterface::ERROR_COMMAND = "invalid command";
const std::string UserInterface::ERROR_DELETE = "text not found";
const std::string UserInterface::ERROR_ADD = "\"%s\" is already inside. y to include; n to exclude";
const std::string UserInterface::ERROR_SEARCH = "\"%s\" cannot be found in %s";
const std::string UserInterface::ERROR_EDIT;
const std::string UserInterface::ERROR_SORT;
const std::string UserInterface::ERROR_UNDO;
const std::string UserInterface::ERROR_REDO;

const std::string UserInterface::MESSAGE_EMPTY;

void UserInterface::printStarRow(){
	for (int i=0; i<80; i++){
		std::cout << "*" ;
	}
}

void UserInterface::centralizePrintToUser(std::string text) {
	int position = (80-text.size())/2;

	for (int i=0; i<position; i++){
		std::cout << " ";
	}

	std::cout << text <<std::endl;
}

void UserInterface::printToUser(std::string text) {
	std::cout << 
}

void UserInterface::addQuote() {
	_quotes.push_back("Mistakes are proof that you are trying");
	_quotes.push_back("Be kind, for everyone you meet is fighting a harder battle.");
	_quotes.push_back("Never stop doing your best just because someone doesn't give you credit.");
	_quotes.push_back("It's not who you are that holds you back, it's who you think you're not.");
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

void UserInterface::userAction() {
	std::cout << std::endl << std::setw(13) << "(1) Add" << std::setw(13) << "(2) Display" 
			  << std::setw(13) << "(3) Edit" << std::setw(13) << "(4) Delete" 
			  << std::setw(13) << "(5) Clear" << std::setw(13) << "(6) Exit" << std::endl;

	centralizePrintToUser(MESSAGE_ACTION);
}

void UserInterface::runProgram(char *argv[]) {
	std::string fileName = argv[1];

	homeScreen();

	do {
		userAction();
		getline(std::cin, _userInput);
		if (parse.isClearScreen(_userInput)) {
			std::cout << std::string(100, '\n');
			homeScreen();
		}
		else {
			parse.carryOutCommand(parse.determineCommand(_userInput));
		}
	} while (parse.isRunProgram());
	
	/*
	
	while (command != 7) {				
		while (command < 1 || command > 7) {
			std::cout << "Invalid command.\n";
			std::cin >> command;
		}

		parse.determineCommand(data, fileName, command, fileSize, add, remove, display, edit, clearFile);

		userAction();
		std::cin >> command;
	}*/
}

void UserInterface::homeScreen() {
	printStarRow();
	centralizePrintToUser(MESSAGE_WELCOME);
	printStarRow();

	addQuote();
	centralizePrintToUser(quoteOfTheDay());
	std::cout << std::endl;
}