#include "UserInterface.h"

const std::string UserInterface::MESSAGE_WELCOME = "*** Welcome to Listful ***";
const std::string UserInterface::MESSAGE_ACTION = "Please choose an action: ";

const std::string UserInterface::MESSAGE_ADD = "added to %s: \"%s\"";
const std::string UserInterface::MESSAGE_DELETE = "deleted from %s: \"%s\"";
const std::string UserInterface::MESSAGE_CLEAR = "all content deleted from %s";
const std::string UserInterface::MESSAGE_EMPTY = "%s is empty";
const std::string UserInterface::MESSAGE_SORT = "%s has been sorted alphabetically";
const std::string UserInterface::MESSAGE_EDIT = "%s has been edited";
const std::string UserInterface::MESSAGE_SEARCH = "results of '%s':\n";
const std::string UserInterface::MESSAGE_UNDO = "undid previous change";
const std::string UserInterface::MESSAGE_REDO = "redid previous undo";

const std::string UserInterface::ERROR_COMMAND = "invalid command";
const std::string UserInterface::ERROR_DELETE = "text not found";
const std::string UserInterface::ERROR_ADD = "\"%s\" is already inside. y to include; n to exclude";
const std::string UserInterface::ERROR_SEARCH = "\"%s\" cannot be found in %s";
const std::string UserInterface::ERROR_EDIT;
const std::string UserInterface::ERROR_SORT;
const std::string UserInterface::ERROR_UNDO;
const std::string UserInterface::ERROR_REDO;

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
	centralizePrintToUser(MESSAGE_ACTION);

	std::cout << std::endl << std::setw(10) << "(1) Add" << std::setw(10) << "(2) Display" 
			  << std::setw(10) << "(3) Edit" << std::setw(10) << "(4) Delete" 
			  << std::setw(10) << "(5) Clear" << std::setw(10) << "(6) Search" << std::setw(10) << "(7) Exit" << std::endl;
	return;
}

void UserInterface::runProgram(char *argv[]) {
	std::string fileName = argv[1];
	Parser parse;
	DataStore data;
	Classes listClass;
	int message = 0;

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
			message = parse.carryOutCommand(listClass, data, fileName);

		}
	} while (!parse.isRunProgram());
	return;
}

void UserInterface::homeScreen() {
	printStarRow();
	centralizePrintToUser(MESSAGE_WELCOME);
	printStarRow();

	addQuote();
	centralizePrintToUser(quoteOfTheDay());
	std::cout << std::endl;
	return;
}