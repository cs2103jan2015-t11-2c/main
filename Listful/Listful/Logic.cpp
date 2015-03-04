#include "Logic.h"
#include "DataStore.h"

	DataStore data;

Logic::Logic(void) {
	DataStore data;
}

void Logic::addContent(std::string &fileName, std::string readInLine) {
	char choice;

	if (!data.getDataBase().empty() && isDuplicate(readInLine)) {
			
		//Gives user a choice to add the text in the file despite the duplicate
		std::cin >> choice;
		if (choice == 'n') {
			std::cout << "\n";
			return;
		}
	}

	data.getDataBase().push_back(readInLine);
	updateText(fileName);
	sprintf_s(messageToUser, MESSAGE_ADD.c_str(), fileName.c_str(), readInLine.c_str());
	output(messageToUser);
}

bool Logic::isDuplicate(std::string &readInLine) {
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

void Logic::deleteContent(std::string &fileName) {
	//To check if the index number the user wants to delete is valid
	if (contentIndex > data.getDataBase().size()) {
		output(ERROR_DELETE);
		return;
	}

	if (isFileEmpty(fileName)) {
		return;
	}
	
	std::string text = data.getDataBase()[contentIndex - 1];
	data.getDataBase().erase(data.getDataBase().begin() + contentIndex - 1);
	updateText(fileName);
	sprintf_s(messageToUser, MESSAGE_DELETE.c_str(), fileName.c_str(), text.c_str());
	output(messageToUser);

	if (data.getDataBase().empty()) {
		sprintf_s(messageToUser, MESSAGE_CLEAR.c_str(), fileName.c_str());
		output(messageToUser);
	}
}

void Logic::clearFile(std::string &fileName) {
	if (isFileEmpty(fileName)) {
		return;
	}

	data.getDataBase().clear();
	updateText(fileName);
	sprintf_s(messageToUser, MESSAGE_CLEAR.c_str(), fileName.c_str());
	output(messageToUser);
}

void Logic::compareLineSize(std::string &line1, std::string &line2, std::string &lineSize) {
	if (line1.size() <= line2.size()) {
			lineSize = line1;
	}
	else {
		lineSize = line2;
	}
}

bool Logic::compareWord(std::string &line1, std::string &line2, std::string &lineSize) {

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
void Logic::sortFile(std::string fileName) {
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

void Logic::switchPlaces(int &iter, int &start) {
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
	data.getDataBase() = tempItems;
}

//Displays all contents that contains the keywords
void Logic::searchFile(std::string &fileName, std::string readInLine) {
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

bool Logic::foundContent(std::string &readInLine) {
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

/*
//Informs user that the file is empty
bool TextBuddy::isFileEmpty(std::string &fileName) {
	if (file.empty()) {
		sprintf_s(messageToUser, MESSAGE_EMPTY.c_str(), fileName.c_str());
		output(messageToUser);
		return true;
	}

	return false;
}
*/

Logic::~Logic(void) {}
