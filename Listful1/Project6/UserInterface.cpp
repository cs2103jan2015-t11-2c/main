#include "UserInterface.h"
#include <locale>
#include <assert.h>
#include <ctype.h>

const std::string UserInterface::MESSAGE_WELCOME = "*** Welcome to Listful ***";
const std::string UserInterface::MESSAGE_ACTION = "Please choose an action: ";

const std::string UserInterface::MESSAGE_ADD = "added to %s: \"%s\"";
const std::string UserInterface::MESSAGE_DELETE = "deleted from %s: \"%s\"";
const std::string UserInterface::MESSAGE_CLEAR = "all content deleted from %s";
const std::string UserInterface::MESSAGE_EMPTY = "%s is empty";
const std::string UserInterface::MESSAGE_SORT = "%s has been sorted alphabetically";

const std::string UserInterface::ERROR_COMMAND = "invalid command";
const std::string UserInterface::ERROR_DELETE = "text not found";
const std::string UserInterface::ERROR_ADD = "\"%s\" is already inside. y to include; n to exclude";
const std::string UserInterface::ERROR_SEARCH = "\"%s\" cannot be found in %s";

void UserInterface::printStarRow(){
	for (int i=0; i<80; i++){
		std::cout << "*" ;
	}
}

void UserInterface::centralizeOutput(std::string text) {
	int position = (80-text.size())/2;
	for (int i=0; i<position; i++){
		std::cout << " ";
	}
	std::cout << text <<std::endl;
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
	int size = _quotes.size();
	//get a pseudo random number in [0, size of quote bank]
	for (int i=0; i<30;i++){
		randNum = (rand()%size);
	}
	std::string chosenQuote = _quotes[randNum];

	return chosenQuote;
}

void UserInterface::userAction() {
	std::cout << std::endl;
	std::cout << "(1) Add" << std::setw(42) << "(4) Edit" << std::endl;
	std::cout << "(2) Display" << std::setw(40) << "(5) Search" << std::endl;
	std::cout << "(3) Delete" << std::setw(39) << "(6) Clear" << std::endl;
	std::cout << "(7) Exit \n" << std::endl;
}

void UserInterface::homeScreen() {
	printStarRow();
	centralizeOutput(MESSAGE_WELCOME);
	printStarRow();

	addQuote();
	centralizeOutput(quoteOfTheDay());
	std::cout << std::endl;
	
	centralizeOutput(MESSAGE_ACTION);
	std::cout << std::endl;
}

void UserInterface::runProgram(char *argv[]) {
	userAction();
	std::string command;
	Parser parse;
	Log log;
	log.clear();

	std::string fileName = argv[1];
	fileSize = 1;
	
	std::cin >> command;

	bool isAlphaCommand;

	if(isAlphaCommand){
		while (command != "EXIT") {
			std::string input;
			getline(std::cin,input);
			parse.determineCommandAlpha(input,parse.userCommandAlpha(command));
			log.log("moving to parser");

			userAction();
			std::cin >> command;
		}
	}
	else {
		while (command != "7") {				
		std::string input;
		getline(std::cin,input);
		parse.determineCommandNum(input, parse.userCommandNum(command));
		log.log("moving to parser");

		userAction();
		std::cin >> command;
		}
	}

}

bool isAlphaCommand(std::string command){
	locale locale;
	bool isAllAlpha = false;
	for (std::string::iterator i=command.begin(); i != command.size(); i++){
		if(isalpha(*i, locale)){
			isAllAlpha = true;
		}
		else {
			isAllAlpha = false;
		}
	}
	return isAllAlpha;
}

/*void UserInterface::runProgram(char *argv[]) {
	DataStore data;
	Parser parse;
	Add add;
	Display display;
	Delete remove;
	Edit edit;
	Clear clearFile;
	Sort sort;
	Log log;
	log.clear();

	userAction();
	std::cin >> command;
	
	assert( command>0 && command <=7);

	std::string fileName = argv[1];
	fileSize = 1;

	while (command != 7) {				
		while (command < 1 || command > 7) {
			std::cout << "Invalid command.\n";
			std::cin >> command;
		}

		parse.determineCommand(data, fileName, command, fileSize, add, remove, display, edit, clearFile, sort);
		log.log("moving to parser");

		userAction();
		std::cin >> command;
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

