#include "DataStore.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>

DataStore::DataStore () {
}

void main(int argc, char *argv[]) {

	if (argc > 1) {

		DataStore newStore;
		newStore.inputCommand();
		newStore.executeCommand();
	}

	return;
}

void DataStore::inputCommand() {

	std::cin >> command; 
	usercommand = checkCommand();

	return;
}

int DataStore::checkCommand() {
	
	if (command == "add") {
		return commandType::ADD;
	}
	else if (command == "delete") {
		return commandType::DELETE;
	}
	else if (command == "display") {
		return commandType::DISPLAY;
	}
	else if (command == "clear") {
		return commandType::CLEAR;
	}
	else if (command == "search") {
		return commandType::SEARCH;
	}
	else if (command == "exit") {
		return commandType::EXIT;
	}
	else {
		return commandType::INVALID;
	}
}

void DataStore::executeCommand() {

	switch (usercommand) {
		case ADD:
			//remove whitespace before user input
			cin >> ws;
			getline(cin, input);
			addContent(input);
			break;

		case DELETE:
			cin >> index;
			deleteContent();
			break;

		case CLEAR:
			clearContent();
			break;

		case DISPLAY:
			displayContent();
			break;
			
		case SORT:
			sortFile();
			break;

		case SEARCH:
			cin >> ws;
			getline(cin, input);
			result = searchFile(input);
			break;

		case INVALID:
			sprintf_s(buffer, ERROR_COMMAND.c_str(), command.c_str());
			print(buffer);
			break;

		case EXIT:
			return;
	}
	commandType();
	executeCommand();	
}



DataStore::DataStore(void) {
}


DataStore::~DataStore(void) {
}

/*
//Updates text file after every command so that if user does not close the program 
//properly, the information is not lost
void TextBuddy::updateText(std::string &fileName) {
	std::vector <std::string>::iterator iter = file.begin();

	writeFile.open(fileName);
	for (int count = 1; iter != file.end(); count++) {
		writeFile << count << ". " << *iter << "\n";
		iter++;
	}
	writeFile.close();
}
*/