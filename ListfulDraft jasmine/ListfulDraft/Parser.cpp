#include "Parser.h"

void Parser::init(std::string command) {
	size_t start = 0;
	size_t end;
	_isEnd = false;

	getNextWord(command, start, end);
	if (end == std::string::npos) {
		_userInput = command;
		return;
	}

	_userInput = command.substr(start, end - 1);
	_information = command.substr(end);
	return;
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

void Parser::carryOutCommand(Classes listClass, DataStore data) {
	int command = determineCommand();

	switch(command) {
		case ADD:
			separateWord(listClass, data);
			listClass.add.
			break;
		case DISPLAY:
			break;
		case CLEAR:
			break;
		case EDIT:
			break;
		case DELETE:
			break;
		case REDO:
			break;
		case UNDO:
			break;
		case SEARCH:
			break;
		case SORT:
			break;
		case EXIT:
			_isEnd = true;
			break;
		case INVALID:
			break;
	}
	return;
}

void Parser::separateWord(Classes listClass, DataStore &data) {
	date = false;
	time = false;
	cat = false;
	priority = false;

	retrieveDate(listClass);
	if (date) {
		data.get_tempEntry().day = _day; 
		data.get_tempEntry().month = _month; 
		data.get_tempEntry().year = _year; 
		std::cout << "extracted date: " << data.get_tempEntry().day << '/' << data.get_tempEntry().month << '/' << data.get_tempEntry().year << std::endl;
	}

	retrieveTime(listClass);
	if (time) {
		data.get_tempEntry().startTime = _sTime; 
		data.get_tempEntry().endTime = _eTime; 
		std::cout << "extracted time: " << data.get_tempEntry().startTime << '-' << data.get_tempEntry().endTime << std::endl;
	}

	retrievePriority(listClass);
	if (priority) {
		data.get_tempEntry().priority = _priority;
		std::cout << "Priority: " << data.get_tempEntry().priority << std::endl;
	}

	retrieveCategory(listClass);
	if (cat) {
		data.get_tempEntry().category = _cat;
		std::cout << "category: " << data.get_tempEntry().category << std::endl;
	}

	data.get_tempEntry.subject = _information;
	return;
}

void Parser::retrieveDate(Classes listClass) {
	std::string dStr = _information;
	size_t start = 0;
	size_t end = 0;
	int count = 0;

	do {
		if (!listClass.date.extractDate(dStr)) {
			updateStr(dStr, start, end);
		}
		else {
			joinStr(dStr, start);
			cutExtraWord(start - 1, count);
			_day = listClass.date.getDay(); 
			_month = listClass.date.getMonth(); 
			_year = listClass.date.getYear();
			date = true;
			return;
		}
	} while (end != std::string::npos);
	return;
}

void Parser::retrieveTime(Classes listClass) {
	std::string tStr = _information;
	int count = 0;
	size_t start = 0;
	size_t end = 0;
	int word = 0;

	do {
		if (listClass.time.extractTime(tStr, count)) {
			if (count == 1) {
				listClass.time.updateTime();
			}
			joinStr(tStr, start);
			cutExtraWord(start - 1, word);
			_sTime = listClass.time.getStart(); 
			_eTime = listClass.time.getEnd();
		//	listClass.time.checkStartEnd();
			time = true;
			return;
		}
		updateStr(tStr, start, end);
	} while (end != std::string::npos);
	return;
}

void Parser::retrievePriority(Classes listClass) {
	std::string pStr = _information;
	size_t start = 0;
	size_t end = 0;
	int word = 0;

	do { 
		if (!listClass.priority.extractPriority(pStr)) {
			updateStr(pStr, start, end);
			std::cout << pStr << std::endl;
		}
		else {
			joinStr(pStr, start);
			_priority = listClass.priority.getPriority();
			cutExtraWord(start - 1, word);
			priority = true;
			return;
			}	
	} while (end != std::string::npos);
	return;
}

void Parser::retrieveCategory(Classes listClass) {
	std::string pStr = _information;
	size_t start = 0;
	size_t end = 0;
	int word = 0;

	do { 
		if (!listClass.category.extractCat(pStr)) {
			updateStr(pStr, start, end);
		}
		else {
			joinStr(pStr, start);
			_cat = listClass.category.getCat();
			cutExtraWord(start - 1, word);
			cat = true;
			return;
			}	
	} while (end != std::string::npos);
	return;
}

void Parser::getNextWord (std::string &tStr, size_t &start, size_t &end) {
	end = tStr.find_first_of(" ,:;?/()[]{}''""!@#$%^&*-_+=|<>`~", start);
	if (end == std::string::npos) {
		return;
	}
	end = tStr.find_first_not_of(" ,:;?/()[]{}''""!@#$%^&*-_+=|<>`~", end);
	return;
}

void Parser::updateStr(std::string &tStr, size_t &start, size_t &end) {
	getNextWord(_information, start, end);
	if (end != std::string::npos) {
		tStr = _information.substr(end);
		start = end;
	}
	return;
}

void Parser::joinStr(std::string &tStr, size_t &start) {
	_information = _information.substr(0, start);
	_information = _information + tStr;
	return;
}

void Parser::cutExtraWord(size_t found, int count) {
	std::string word = "";
	size_t find = _information.find_first_not_of(" ", found);
	size_t find2 = _information.find_first_of(" ", find);
	
	if (count == 0) {
		if (find != std::string::npos) {
			word = _information.substr(find, find2 - find);
			if (!extraWord(word, find)) {
			}
		}
	}

	if (count > 3) {
		return;
	}

	find = _information.find_last_not_of(" ", found);
	if (find == std::string::npos) {
		return;
	}
	find = _information.find_last_of(" ", find);
	if (find == std::string::npos) {
		find = 0;
	}
	word = _information.substr(find, found - find);
	removeChar(word);
	if (extraWord(word, find)) {
		count++;
		return cutExtraWord(find, count);
	}
	return;
}

bool Parser::extraWord(std::string word, size_t found) {
	std::vector <std::string> extra;
	extra.push_back("from");
	extra.push_back("now");
	extra.push_back("until");
	extra.push_back("due");
	extra.push_back("by"); 
	extra.push_back("on");
	extra.push_back("do");
	extra.push_back("of");
	extra.push_back("importance");
	extra.push_back("onwards");
	extra.push_back("at");
	extra.push_back("to");
	extra.push_back("up");
	extra.push_back("!");
	extra.push_back("?");
	extra.push_back(",");
	extra.push_back(".");
	extra.push_back("till");
	extra.push_back("this");
	extra.push_back("complete");
	extra.push_back("then");
	extra.push_back("read");
	extra.push_back("in");
	extra.push_back("hand");
	extra.push_back("submit");
	extra.push_back("send");
	extra.push_back("update");
	extra.push_back("remind");
	extra.push_back("me");
	extra.push_back("the");
	extra.push_back("check");
	extra.push_back("up");
	extra.push_back("category");
	extra.push_back("priority");
	extra.push_back("impt");
	extra.push_back("cat");
	//extra.push_back("and");
	changeToLower(word);

	size_t find = 0;
	std::vector <std::string>::iterator iter = extra.begin();

	while (iter != extra.end()) {
		if (word == (*iter)) {
			find = _information.find_first_of(" ", found + 1);
			if (find == std::string::npos) {
				_information = _information.substr(0, found);
				return true;
			}
			word = _information.substr(find);
			_information = _information.substr(0, found) + word;
			return true;
		}
		iter++;
	}
	return false;
}

void Parser::changeToLower(std::string &str) {
	int i;
	for (i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = 'a' + (str[i] - 'A');	
		}
	}
	return;
}

void Parser::removeChar(std::string &str) {
	size_t found;
	found = str.find_first_of(" /.-");

	while (found != std::string::npos && found == 0) {
		str = str.substr(1);
		found = str.find_first_of(" /.-");
	}
	return;
}