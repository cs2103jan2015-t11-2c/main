#include "Parser.h"

Parser::Parser(std::string &commandLine) {
	_userInput = commandLine;
}

bool Parser::isRunProgram() {
	return _isEnd;
}

bool Parser::isClearScreen() {
	if (_userInput == "clear screen") {
		return false;
	}
	return true;
}

void Parser::convertLowerCase() {
	std::transform(_userInput.begin(), _userInput.end(), _userInput.begin(), ::tolower);
}

int Parser::determineCommand() {
	if (_userInput == "add" || _userInput == "1") {
		return commandType::ADD;
	}
	else if (_userInput == "delete" || _userInput == "4") {
		return commandType::DELETE;
	}
	else if (_userInput == "display" || _userInput == "2") {
		return commandType::DISPLAY;
	}
	else if (_userInput == "clear" || _userInput == "5") {
		return commandType::CLEAR;
	}
	else if (_userInput == "edit" || _userInput == "3") {
		return commandType::EDIT;
	}
	else if (_userInput == "sort") {
		return commandType::SORT;
	}
	else if (_userInput == "search") {
		return commandType::SEARCH;
	}
	else if (_userInput == "undo") {
		return commandType::UNDO;
	}
	else if (_userInput == "redo") {
		return commandType::REDO;
	}
	else if (_userInput == "search") {
		return commandType::SEARCH;
	}
	else if (_userInput == "exit" || _userInput == "6") {
		return commandType::EXIT;
	}
	else {
		return commandType::INVALID;
	}
}

void Parser::carryOutCommand(int command) {
	switch (command){
			case 1:{ //add
				getline(std::cin, userInput);
				std::string sub = userContent();
				int ST = startTime();
				int ET = endTime();
				int DD = dateDay();
				int MM = dateMonth();
				int YYYY = dateYear();
				std::string p = userPriority();
				std::string cat =  userCat();

				add.addContent(fileName, fileSize, sub, ST, ET, DD, MM, YYYY, p, cat, data);
				fileSize++;
				break;
				   }
			case 2:{ //display
				std::string displayStr = getDisplay();
				display.displayContent(fileName, data, displayStr, 0);
				break;
				   }
			case 3:{ //edit
				int deleteIndex = getDelete();
				remove.deleteContent(fileName, data, deleteIndex);
				fileSize--;
				break;
				   }
			case 4:{ //delete
				std::cin >> index;
				std::cin >> command;
				getline(std::cin, userInput);
				int ST = editSTime();
				int ET = editETime();
				int DD = editDay();
				int MM = editMonth();
				int YYYY = editYear();
				std::string p = userPriority();
				std::string cat = userCat();
				if (isDate()) {
					edit.editContent(fileName, data, userInput, index, userInput, editDay(), editMonth(), editYear());
				}
				else if (isTime()) {
					edit.editContent(fileName, data, cat, index, userInput, editSTime(), editETime());
				}
				else {
					edit.editContent(fileName, data, cat, index, userInput);
				}
				break;
				}
			case 5: //clear
				break;
			case 6: { //exit
					deleteFile.clearFile(fileName, data);
				break;
				}
			case 7: { //sort
					deleteFile.clearFile(fileName, data);
				break;
				}
			case 8: { //search
					deleteFile.clearFile(fileName, data);
				break;
				}
			case 9: { //undo
					deleteFile.clearFile(fileName, data);
				break;
				}
			case 10: { //redo
					deleteFile.clearFile(fileName, data);
				break;
				}
			default:
				std::cout << "Invalid command.\n";
				std::cin >> command;
				break;
		}
}

bool isTime (std::string line) {
	int i;
	int count = 0;

	for (i = 0; i <= line.size(); i++) {
		if ((count <= 2) && (line[i] == '.' || line[i] == ':')) {
			if (count > 2) {
				return false;
			}
		}
		while (line[i] <= '9' || line[i] >= '0') {
			i++;
			count++;
			if (count > 4) {
				return false;
			}
		}
		i--;
	}

}

bool Parser::getTime() {
	int index;
	int start;
	int end;
	std::string frontStr;
	std::string backStr;

	index = _userInput.find(" to ");
	if (index != std::string::npos) {
		start = _userInput.find_last_of(" ", index-1);
		frontStr = _userInput.substr(start+1, (index-1)-(start+1));

	}
	else {
		index = _userInput.find("-");
		if (index != std::string::npos) {

		}
		else {
			index = _userInput.find("pm");
			if (index != std::string::npos) {

			}
			else {
				index = _userInput.find("am");
				if (index != std::string::npos) {
				}
			}
		}
	}
	return false;
}



/*
void Parser::determineCommand(DataStore &data, std::string fileName, int command, int &fileSize, Add &add, Delete &remove, Display &display, Edit &edit, Clear &deleteFile){
}

std::string Parser::userContent(){
	std::string userContent = userInput.substr(0, userInput.find_first_of(".,?!"));
	return userContent;
}

bool Parser::isDate() {
	size_t found;

	found = userInput.find("/");
	if (found != std::string::npos) {
		return true;
	}

	return false;
}

bool Parser::isTime() {
	size_t found;

	found = userInput.find("-");
	if (found != std::string::npos) {
		return true;
	}

	return false;
}

int Parser::getDelete() {
	int deleteStr;
	std::cin >> deleteStr;
	return deleteStr;
}

std::string Parser::getDisplay() {
	std::string displayStr;
	std::cin >> displayStr;
	return displayStr;
}

std::string Parser::getEditCat() {
	std::string cat;
	std::cin >> cat;
	return cat;
}

int Parser::editDay(){
	std::string userDateDay = userInput.substr(0, 2);
	int dateDay = atoi(userDateDay.c_str());
	return dateDay;
}

int Parser::editMonth(){
	std::string userDateMonth = userInput.substr(3, 2);
	int dateMonth = atoi(userDateMonth.c_str());
	return dateMonth;
}

int Parser::editYear(){
	std::string userDateYear = userInput.substr(6, 4);
	int dateYear = atoi(userDateYear.c_str());
	
	return dateYear;
}

int Parser::editSTime(){
	std::string userStartTime;
	int startTime;

	userStartTime = userInput.substr(0, 4);
	startTime = atoi(userStartTime.c_str());
	
	return startTime;
}

int Parser::editETime(){
	std::string userEndTime;
	int endTime;

	userEndTime = userInput.substr(userTime().find_first_of("-")+1, 4);
	endTime = endTime = atoi(userEndTime.c_str());

	return endTime;
}

std::string Parser::userDate(){
	std::string userDate = userInput.substr(userInput.find_first_of(".,?!")+2,10);

	return userDate;
}

int Parser::dateDay(){
	std::string userDateDay = userDate().substr(0, 2);
	int dateDay = atoi(userDateDay.c_str());
	return dateDay;
}

int Parser::dateMonth(){
	std::string userDateMonth = userDate().substr(3, 2);
	int dateMonth = atoi(userDateMonth.c_str());
	return dateMonth;
}

int Parser::dateYear(){
	std::string userDateYear = userDate().substr(6, 4);
	int dateYear = atoi(userDateYear.c_str());
	return dateYear;
}

std::string Parser::userTime(){
	std::string userTime = userInput.substr(userInput.find_first_of(".,?!")+14, 9);

	return userTime;
}

int Parser::startTime(){
	std::string userStartTime;
	int startTime;

	userStartTime = userTime().substr(0, 4);
	startTime = atoi(userStartTime.c_str());
	return startTime;
}

int Parser::endTime(){
	std::string userEndTime;
	int endTime;

	userEndTime = userTime().substr(userTime().find_first_of("-")+1, 4);
	endTime = endTime = atoi(userEndTime.c_str());
	return endTime;
}

std::string Parser::userCat(){
	std::string userCat = userInput.substr(userInput.find_last_of(" ")+1, userInput.size());

	return userCat;
}

std::string Parser::userPriority(){
//	int lengthPriority = (userInput.size() - userInput.find_first_of(".,?!")-25) - (userInput.size()- userInput.find_last_of(","));
	int a = userInput.size() - userInput.find_first_of(".,?!")-25;
	int b = userInput.size()- userInput.find_last_of(",");
	std::string userPriority = userInput.substr(userInput.find_first_of(".,?!")+25, a-b);

	return userPriority;
}*/

/*void Parser::testParser(){
	std::string text = getUserInput();
	std::cout << "Day = " << dateDay(userDate(text)) << std::endl;
	std::cout << "month = " << dateMonth(userDate(text)) << std::endl;
	std::cout << "year = " << dateYear(userDate(text)) << std::endl;
	std::cout << "user content = " << userContent(text) << std::endl;
	std::cout << "user date = " << userDate(text) << std::endl;
	std::cout << "user time = " << userTime(text) << std::endl;
	std::cout << "user priority = " << userPriority(text) << std::endl;
	std::cout << "start time = " << startTime(userTime(text)) << std::endl;
	std::cout << "end time = " << endTime(userTime(text)) << std::endl;
}*/