#include "UI.h"

// from ui.h

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>

//Command messages
static const std::string MESSAGE_ADD;
static const std::string MESSAGE_DELETE;
static const std::string MESSAGE_CLEAR;
static const std::string MESSAGE_EMPTY;
static const std::string MESSAGE_SORT;

//Welcome message
static const std::string MESSAGE_WELCOME;

//Error messages
static const std::string ERROR_COMMAND;
static const std::string ERROR_DELETE;
static const std::string ERROR_ADD;
static const std::string ERROR_SEARCH;

//Index of created text file name
static const int FILE_INDEX;

class UI {
public:
	UI(void);
	~UI(void);
};

#endif

// ui.cpp
#include "UI.h"


UI::UI(void) {
}


UI::~UI(void) {
}

/*
//Command messages
const std::string TextBuddy::MESSAGE_ADD = "added to %s: \"%s\"";
const std::string TextBuddy::MESSAGE_DELETE = "deleted from %s: \"%s\"";
const std::string TextBuddy::MESSAGE_CLEAR = "all content deleted from %s";
const std::string TextBuddy::MESSAGE_EMPTY = "%s is empty";
const std::string TextBuddy::MESSAGE_SORT = "%s has been sorted alphabetically";

//Greeting message
const std::string TextBuddy::MESSAGE_WELCOME = "Welcome to TextBuddy. %s is ready for use";

//Error messages
const std::string TextBuddy::ERROR_COMMAND = "invalid command";
const std::string TextBuddy::ERROR_DELETE = "text not found";
const std::string TextBuddy::ERROR_ADD = "\"%s\" is already inside. y to include; n to exclude";
const std::string TextBuddy::ERROR_SEARCH = "\"%s\" cannot be found in %s";

//ui
void TextBuddy::getCommand() {
	std::cout << "\ncommand: ";
	std::cin >> inputCommand;
	command = determineCommand();
}

//ui
int TextBuddy::determineCommand() {
	if (inputCommand == "add") {
		return commandType::ADD;
	}
	else if (inputCommand == "delete") {
		return commandType::DELETE;
	}
	else if (inputCommand == "display") {
		return commandType::DISPLAY;
	}
	else if (inputCommand == "clear") {
		return commandType::CLEAR;
	}
	else if (inputCommand == "sort") {
		return commandType::SORT;
	}
	else if (inputCommand == "search") {
		return commandType::SEARCH;
	}
	else if (inputCommand == "exit") {
		return commandType::EXIT;
	}
	else {
		return commandType::INVALID;
	}
	//Check if command is valid else it will continue to take in strings until the user inputs 
	//a valid command
	/*std::string CommandList;
	CommandList = "add delete display clear exit sort search";

	std::size_t found; 
	found = CommandList.find(inputCommand);

	while (found == std::string::npos) {
		getline(std::cin, inputCommand);
		std::cout << "\n";
		output(ERROR_COMMAND);
		getCommand();
		found = CommandList.find(inputCommand);
	}*/
}

//ui
void TextBuddy::checkFileCreated(std::string &fileName) {
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
}

//ui
void TextBuddy::carryOutCommand(std::string &fileName) {
	std::string readInLine;

	switch (command) {
		case ADD:
			readInLine = removeWhitespace();
			addContent(fileName, readInLine);
			break;

		case DELETE:
			std::cin >> contentIndex;
			std::cout << "\n";
			deleteContent(fileName);
			break;
		
		case CLEAR:
			std::cout << "\n";
			clearFile(fileName);
			break;
	
		case DISPLAY:
			tempItems.clear();
			printContent(fileName);
			break;

		case SORT:
			std::cout << "\n";
			sortFile(fileName);
			break;

		case SEARCH:
			readInLine = removeWhitespace();
			searchFile(fileName, readInLine);
			break;

		case EXIT:
			return;

		default:
			getline(std::cin, inputCommand);
			std::cout << "\n";
			output(ERROR_COMMAND);
			break;
	}
	getCommand();
	carryOutCommand(fileName);
}

//ui
std::string TextBuddy::removeWhitespace() {
	std::string readInLine;

	//Removes whitespace before the wanted text
	std::cin >> std::ws;
	getline(std::cin, readInLine);
	std::cout << "\n";

	//Removes all end of line whitespaces
	while (readInLine.at(readInLine.size() - 1) == ' ') {
		readInLine = readInLine.substr(0, readInLine.size() - 1);
	}

	return readInLine;
}

void TextBuddy::output(std::string messageToUser) {
	std::cout << "\n" << messageToUser << "\n";
}
*/