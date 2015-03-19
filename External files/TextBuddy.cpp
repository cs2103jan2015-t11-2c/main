// Jasmine Quah Xue Li 
// Matriculation no. : A0116177E
// CE2 - TextBuddy

#include "TextBuddy.h"

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

void TextBuddy::getCommand() {
	std::cout << "\ncommand: ";
	std::cin >> inputCommand;
	command = determineCommand();
}

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

void TextBuddy::printContent(std::string &fileName) {
	if (isFileEmpty(fileName)) {
		return;
	}

	if (tempItems.empty()) {
		tempItems = file;
	}

	std::vector <std::string>::iterator index = tempItems.begin();
	std::cout << "\n\n";

	for (int i = 1; index != tempItems.end(); i++) {
		if (index == tempItems.end() - 1) {
			std::cout << i << ". " << *index << "\n";
		}
		else {
			std::cout << i << ". " << *index << "\n\n";
		}
		index++;
	}/*
	std::string fileName = argv[FILE_INDEX];
	std::string content;

	readFile.open(fileName);
	while (std::getline(readFile, content)) {
		output(content);
	}
	readFile.close();*/
}

void TextBuddy::addContent(std::string &fileName, std::string readInLine) {
	char choice;

	if (!file.empty() && isDuplicate(readInLine)) {
			
		//Gives user a choice to add the text in the file despite the duplicate
		std::cin >> choice;
		if (choice == 'n') {
			std::cout << "\n";
			return;
		}
	}

	file.push_back(readInLine);
	updateText(fileName);
	sprintf_s(messageToUser, MESSAGE_ADD.c_str(), fileName.c_str(), readInLine.c_str());
	output(messageToUser);
}

bool TextBuddy::isDuplicate(std::string &readInLine) {
	std::vector <std::string>::iterator iter;

	for (iter = file.begin(); iter != file.end(); iter++) {
		if (*iter == readInLine) {
			sprintf_s(messageToUser, ERROR_ADD.c_str(), readInLine.c_str());
			output(messageToUser);
			return true;
		}
	}

	return false;
}

void TextBuddy::deleteContent(std::string &fileName) {
	//To check if the index number the user wants to delete is valid
	if (contentIndex > file.size()) {
		output(ERROR_DELETE);
		return;
	}

	if (isFileEmpty(fileName)) {
		return;
	}
	
	std::string text = file[contentIndex - 1];
	file.erase(file.begin() + contentIndex - 1);
	updateText(fileName);
	sprintf_s(messageToUser, MESSAGE_DELETE.c_str(), fileName.c_str(), text.c_str());
	output(messageToUser);

	if (file.empty()) {
		sprintf_s(messageToUser, MESSAGE_CLEAR.c_str(), fileName.c_str());
		output(messageToUser);
	}
}

void TextBuddy::clearFile(std::string &fileName) {
	if (isFileEmpty(fileName)) {
		return;
	}

	file.clear();
	updateText(fileName);
	sprintf_s(messageToUser, MESSAGE_CLEAR.c_str(), fileName.c_str());
	output(messageToUser);
}

void TextBuddy::compareLineSize(std::string &line1, std::string &line2, std::string &lineSize) {
	if (line1.size() <= line2.size()) {
			lineSize = line1;
	}
	else {
		lineSize = line2;
	}
}

bool TextBuddy::compareWord(std::string &line1, std::string &line2, std::string &lineSize) {

	for (int index = 0; index < lineSize.size(); index++) {
		char word = ' ';
		if (line1[index] >= 'a' && line1[index] <= 'z') {
			if (line2[index] >= 'a' && line2[index] <= 'z') {
				if (line1[index] > line2[index]) {
					return true;
				}
			}
			else if (line2[index] >= 'A' && line2[index] <= 'Z') {
				word = 'a' + (line2[index] - 'A');
				if (line1[index] > word) {
					return true;
				}
			}
			else {
				return false;
			}
		}
		else if (line1[index] >= 'A' && line1[index] <= 'Z') {
			if (line2[index] >= 'A' && line2[index] <= 'Z') {
				return true;
			}
			else if (line2[index] >= 'a' && line2[index] <= 'z') {
				word = 'A' + (line2[index] - 'a');
				if (line1[index] > word) {
					return true;
				}
			}
			else {
				return false;
			}
		}
		else if ((line2[index] >= 'a' && line2[index] <= 'z') || 
				 (line2[index] >= 'A' && line2[index] <= 'Z')) {
			return true;
		}
		else if (line1[index] > line2[index]) {
			return true;
		}
		
		if ((index == lineSize.size() - 1) && (lineSize == line2)) {
			if ((word != ' ') && (line1[index] < word)) {
				return false;
			}
			else if ((word == ' ') && (line1[index] < line2[index])) {
				return false;
			}
			else {
				return true;
			}
		}
	}

	return false;
}

//Sorts vector in ascending order
void TextBuddy::sortFile(std::string fileName) {
	if (isFileEmpty(fileName)) {
		return;
	}
	
	for (int iter = 1; iter < file.size(); ++iter) {
		std::string lineSize;
		std::string line2 = file[iter];
		std::string line1;
		for (int start = 0; start < iter; ++start) {
			line1 = file[start];
			compareLineSize(line1, line2, lineSize);
			if (compareWord(line1, line2, lineSize)) {
				switchPlaces(iter, start);
				line2 = file[iter];
			}
		}
	}
	updateText(fileName);
	sprintf_s(messageToUser, MESSAGE_SORT.c_str(), fileName.c_str());
	output(messageToUser);
}

void TextBuddy::switchPlaces(int &iter, int &start) {
	tempItems.clear();

	for (int count = 0; count < file.size(); ++count) {
		if (count < start) {
			tempItems.push_back(file[count]);
		}
		else if (count == start) {
			tempItems.push_back(file[iter]);
			tempItems.push_back(file[count]);
		} 
		else if (count != iter) {
			tempItems.push_back(file[count]);
		}
	}
	file = tempItems;
}

//Displays all contents that contains the keywords
void TextBuddy::searchFile(std::string &fileName, std::string readInLine) {
	if (isFileEmpty(fileName)) {
		return;
	}
	
	if (foundContent(readInLine)) {
		printContent(fileName);
		return;
	}

	sprintf_s(messageToUser, ERROR_SEARCH.c_str(), readInLine.c_str(), fileName.c_str());
	output(messageToUser);
}

bool TextBuddy::foundContent(std::string &readInLine) {
	std::vector <std::string>::iterator iter;
	size_t found;
	tempItems.clear();

	for (iter = file.begin(); iter != file.end(); iter++) {
		std::string content = *iter;
		found = content.find(readInLine);
		
		if (found != std::string::npos) {
			tempItems.push_back(content);
		}
	}

	if (tempItems.empty()) {
		return false;
	}
	
	return true;
}

void TextBuddy::output(std::string messageToUser) {
	std::cout << "\n" << messageToUser << "\n";
}

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

//Informs user that the file is empty
bool TextBuddy::isFileEmpty(std::string &fileName) {
	if (file.empty()) {
		sprintf_s(messageToUser, MESSAGE_EMPTY.c_str(), fileName.c_str());
		output(messageToUser);
		return true;
	}

	return false;
}

std::vector <std::string> TextBuddy::getFile() {
			return file;
		}

std::vector <std::string> TextBuddy::getTempFile() {
			return tempItems;
}

int main(int argc, char *argv[]) {
	
	//Index of created text file name
	static const int FILE_INDEX = 1;
	std::string fileName = argv[FILE_INDEX];

	if (argc > FILE_INDEX) {

		TextBuddy textFile;

		textFile.checkFileCreated(fileName);

		textFile.getCommand();

		textFile.carryOutCommand(fileName);
	}

	return 0;
}