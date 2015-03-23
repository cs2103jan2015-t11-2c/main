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

void Parser::getNextWord (std::string &tStr, size_t &start, size_t &end) {
	end = tStr.find_first_of(" ,:;?/()[]{}''""!@#$%^&*-_+=|<>`~", start);
	if (end == std::string::npos) {
		return;
	}
	end = tStr.find_first_not_of(" ,:;?/()[]{}''""!@#$%^&*-_+=|<>`~", end);
}

void Parser::separateWord(Classes listClass, DataStore data) {
	size_t dateIndex;
	size_t timeIndex;

	retrieveDate(listClass, data, dateIndex);
	std::cout << listClass.date.getDate() << std::endl;
		std::cout << "final " << _information[dateIndex] << std::endl;
	retrieveTime(listClass, data, timeIndex);
	std::cout << listClass.time.getTime() << std::endl;
		std::cout << "final " << _information[timeIndex] << std::endl;
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
			index = start;
		std::cout << _information[index] << std::endl;
		}
		else {
			joinStr(dStr, start);
			_day = listClass.date.getDay();
			_month = listClass.date.getMonth();
		std::cout << listClass.date.getDay() << std::endl;
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
			joinStr(tStr, space);
			listClass.time.checkStartEnd();
			_sTime = listClass.time.getStart();
			_eTime = listClass.time.getEnd();
		std::cout << _sTime << std::endl;
			return;
		}
		updateStr(tStr, start, end);
		index = start;
		std::cout << _information[index] << std::endl;
	} while (end != std::string::npos);

	if (count == 1) {
		listClass.time.updateTime();
		listClass.time.checkStartEnd();
			_sTime = listClass.time.getStart();
			_eTime = listClass.time.getEnd();
		std::cout << _sTime << std::endl;
	}
}

void Parser::updateStr(std::string &tStr, size_t &start, size_t &end) {
	getNextWord(_information, start, end);
	if (end != std::string::npos) {
		tStr = _information.substr(end);
		start = end;
	}
}

void Parser::joinStr(std::string &tStr, size_t &start) {
	_information = _information.substr(0, start);
	_information = _information + tStr;
}