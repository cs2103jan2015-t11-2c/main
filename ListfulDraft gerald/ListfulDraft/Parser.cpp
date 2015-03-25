#include "Parser.h"

void Parser::init(std::string command) {
	size_t start = 0;
	size_t end;

	getNextWord(command, start, end);
	_userInput = command.substr(start, end - 1);
	_information = command.substr(end);
}

bool Parser::isRunProgram() {
	return _isEnd;
}

bool Parser::isClearScreen(std::string input) {
	if (input == "clear screen") {
		return true;;
	}
	return false;
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
	else if (_userInput == "search" || _userInput == "6") {
		return commandType::SEARCH;
	}
	else if (_userInput == "undo") {
		return commandType::UNDO;
	}
	else if (_userInput == "redo") {
		return commandType::REDO;
	}
	else if (_userInput == "exit" || _userInput == "7") {
		return commandType::EXIT;
	}
	else {
		return commandType::INVALID;
	}
}

void Parser::separateWord(Classes listClass, DataStore data) {
	date = false;
	time = false;
	size_t dateIndex = 0;
	size_t timeIndex = 0;

	retrieveDate(listClass, data, dateIndex);
	if (date) std::cout << "extracted date: " << _day << '/' << _month << '/' << _year << std::endl;
	retrieveTime(listClass, data, timeIndex);
	if (time) std::cout << "extracted time: " << _sTime << '-' << _eTime << std::endl;
	std::cout << "final " << timeIndex << std::endl;
	std::cout << "remaining str: " << _information << std::endl;
	retrievePriority(listClass, data);
	std::cout << "Priority: " << _priority << std::endl;
	std::cout << "remaining str: " << _information << std::endl;
	std::cout << "Category: " << _category << std::endl;
	std::cout << "remaining str: " << _information << std::endl;

}

void Parser::carryOutCommand(Classes listClass, DataStore data) {
	int command = determineCommand();

	switch(command) {
		case ADD:
			separateWord(listClass, data);

		case INVALID:
			break;
	}
}

void Parser::retrieveDate(Classes listClass, DataStore data, size_t &index) {
	std::string dStr = _information;
	size_t start = 0;
	size_t end = start;

	do {
		if (!listClass.date.extractDate(dStr)) {
			updateStr(dStr, start, end);
		}
		else {
			index = start;
			joinStr(dStr, start);
			_day = listClass.date.getDay();
			_month = listClass.date.getMonth();
			_year = listClass.date.getYear();
			date = true;
			return;
		}
	} while (end != std::string::npos);
}

void Parser::retrieveTime(Classes listClass, DataStore data, size_t &index) {
	std::string tStr = _information;
	int noOfWord = 0;
	int count = 0;
	size_t start = 0;
	size_t end = 0;
	size_t space;

	do {
		if (count != 0) {
			noOfWord++;
		}

		if (listClass.time.extractTime(tStr, count)) {
			joinStr(tStr, start);
			count++;
		}

		if (count == 1) {
			space = start;
		}

		if (count == 2 && noOfWord <= 2) {
			index = space;
			joinStr(tStr, space);
			listClass.time.checkStartEnd();
			_sTime = listClass.time.getStart();
			_eTime = listClass.time.getEnd();
			time = true;
			return;
		}
		updateStr(tStr, start, end);
	} while (end != std::string::npos);

	if (count == 1) {
		index = start;
		listClass.time.updateTime();
		listClass.time.checkStartEnd();
		_sTime = listClass.time.getStart();
		_eTime = listClass.time.getEnd();
	}
}

void Parser::retrievePriority(Classes listClass, DataStore data) {
	std::string pStr = _information;
	size_t start = 0;
	size_t end = 0;

	do { 
		if (!listClass.priority.checkPriority(pStr)) {
			updateStr(pStr, start, end);
		}
		else {
			_priority = listClass.priority.getPriority();
			std::cout << pStr << std::endl;
			joinStr(pStr, start);
			priority = true;
			return;
			}	
	} while (end != std::string::npos);

	return;
}

void Parser::updateStr(std::string &tStr, size_t &start, size_t &end) {
	getNextWord(_information, start, end);
	// do you need to check here when its alr checked below?
	if (end != std::string::npos) {
		tStr = _information.substr(end);
		start = end;
	}
}

void Parser::getNextWord (std::string &tStr, size_t &start, size_t &end) {
	end = tStr.find_first_of(" ,:;?/()[]{}''""!@#$%^&*-_+=|<>`~", start);
	if (end == std::string::npos) {
		return;
	}
	end = tStr.find_first_not_of(" ,:;?/()[]{}''""!@#$%^&*-_+=|<>`~", end);
}

void Parser::joinStr(std::string &tStr, size_t &start) {
	_information = _information.substr(0, start);
	_information = _information + tStr;
}