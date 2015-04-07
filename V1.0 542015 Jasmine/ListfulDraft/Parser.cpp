#include "Parser.h"

//Separates the user input to be the command string and information string and initialises private vector in parser
void Parser::init(std::string command) {
	extraFront.push_back("from");
	extraFront.push_back("due");
	extraFront.push_back("by"); 
	extraFront.push_back("on");
	extraFront.push_back("at");
	extraFront.push_back("to");
	extraFront.push_back("before");
	extraFront.push_back("till");
	extraFront.push_back("after");
	extraFront.push_back("the");
	extraFront.push_back("date");
	extraFront.push_back("time");

	extraFront2.push_back("from");
	extraFront2.push_back("due");
	extraFront2.push_back("by"); 
	extraFront2.push_back("on");
	extraFront2.push_back("at");
	extraFront2.push_back("to");
	extraFront2.push_back("before");
	extraFront2.push_back("till");
	extraFront2.push_back("after");
	extraFront2.push_back("the");
	extraFront2.push_back("date");
	extraFront2.push_back("time");
	extraFront2.push_back("read");
	extraFront2.push_back("remind");
	extraFront.push_back("me");
	extraFront2.push_back("check");
	extraFront2.push_back("send");
	extraFront.push_back("this");
	extraFront2.push_back("update");
	extraFront2.push_back("until");
	extraFront2.push_back("in");
	extraFront2.push_back("do");
	extraFront2.push_back("submit");
	extraFront2.push_back("complete");
	extraFront2.push_back("hand");
	extraFront2.push_back("up");

	extraBack.push_back("onwards");
	extraBack.push_back("hours");
	extraBack.push_back("on");
	
	extraCatImpt.push_back("of");
	extraCatImpt.push_back("category");
	extraCatImpt.push_back("priority");
	extraCatImpt.push_back("importance");
	extraCatImpt.push_back("impt");
	extraCatImpt.push_back("cat");

	deadlineWord.push_back(" due ");
	deadlineWord.push_back(" by ");
	deadlineWord.push_back(" on ");
	deadlineWord.push_back(" before ");

	size_t start = 0;
	size_t end;
	_isEnd = false;

	getNextWord(command, start, end);
	if (end == std::string::npos) {
		_userInput = command;
		_information = "";
		return;
	}

	_userInput = command.substr(start, end - 1);
	_information = command.substr(end);
	return;
}

bool Parser::isRunProgram() {
	return _isEnd;
}

bool Parser::isHelp(std::string input) {
	if (input == "?") {
		return true;
	}
	return false;
}

void Parser::errorAddMsg(std::ostringstream &errMsg, bool pastDate, bool checkTime, Classes listClass) {
	if (pastDate) {
		errMsg << std::endl << "date entered has already past (undo/edit adviced)";
	}
	if (checkTime && listClass.time.getEnd() != listClass.time.getStart()) {
		errMsg << std::endl << "end time entered earlier then start time (undo/edit adviced)";
	}
	return;
}

int Parser::carryOutCommand(Classes &listClass, DataStore &data, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	int command = listClass.determineCommand(_userInput);
	int returnValue = 0;
	int index = 0;
	std::string str = "";
	bool pastDate = false;
	bool checkTime = false;
	bool isTemp = false;
	bool isDelete = false;
	
	switch(command) {
		case listClass.ADD:
			separateWord(listClass, data, pastDate, checkTime);
			errorAddMsg(errMsg, pastDate, checkTime, listClass);
			if (listClass.add.addContent(data, errMsg, isTemp)) {
				returnValue = listClass.commandType::ADD;
			}
			else {
				returnValue = (listClass.commandType::ADD + 12);
			}
			break;

		case listClass.DISPLAY:
			if (_information == "") {
				if (listClass.display.getDisplay(data, floating, scheduled, deadline)) {
					return listClass.commandType::DISPLAY;
				}
				return (listClass.commandType::DISPLAY + 12);
			}
			else {

			}

		case listClass.CLEAR:
			if (listClass.clearFile.clearFile(data)) {
				returnValue = listClass.commandType::CLEAR;
			}
			else {
				returnValue = (listClass.commandType::CLEAR + 12);
			}
			break;

		case listClass.EDIT: 
			str = _information;
			separateWord(listClass, data, pastDate, checkTime);
			if (!getEditDelete(data, listClass, index, listClass.edit.getCat(), str)) {
				returnValue = listClass.commandType::INVALID;
			}
			else {
				if (listClass.edit.editContent(data, index - 1, errMsg)) {
					returnValue = listClass.commandType::EDIT;
				}
				else {
					returnValue = (listClass.commandType::EDIT + 12);
				}
			}
			break;

		case listClass.REMOVE:
			if (listClass.remove.deleteContent(data, _information, errMsg, isDelete)) {
				return listClass.commandType::REMOVE;
			}
			else if (!isDelete) {
				listClass.display.getDeleteDisplay(data, floating, scheduled, deadline);
				return (listClass.commandType::REMOVE + 15);
			}
			return (listClass.commandType::REMOVE + 12);

		case listClass.REDO:
			if (data.redoData(data, errMsg)) {
				return listClass.commandType::REDO;
			}
			return (listClass.commandType::REDO + 12);

		case listClass.UNDO:
			if (data.undoData(data, errMsg)) {
				return listClass.commandType::UNDO;
			}
			return (listClass.commandType::UNDO + 12);

		case listClass.SEARCH: /*{
			std::string command, keyword;
			command = _information.substr(0, _information.find_first_of(" "));
			keyword = _information.substr(_information.find_first_of(" ")+1);
			keyword = keyword.substr(0, keyword.find_first_of(" "));
			_information = command;
			listClass.searchFile.getCat() = listClass.determineSubCat(_information);
			keyword = keyword.substr(keyword.find_first_of(" ")+1);
			if (listClass.searchFile.searchFile(data, keyword, errMsg)) {
				return listClass.commandType::SEARCH;
			}
			return (listClass.commandType::SEARCH + 12);
			}
			std::cout << "index: " << listClass.edit.getCat() << std::endl;
			std::cout << "sub: " << data.get_tempEntry().subject << std::endl;
			std::cout << "time: " << data.get_tempEntry().startTime << "-" << data.get_tempEntry().endTime << std::endl;
			std::cout << "date: " << data.get_tempEntry().day << "/" << data.get_tempEntry().month << std::endl;
			std::cout << "priority: " << data.get_tempEntry().priority << std::endl;
			std::cout << "category: " << data.get_tempEntry().category << std::endl;
			*/
			break;

		case listClass.SORT:
			changeToLower(_information);
			listClass.sortFile.getSortCat() = listClass.determineSubCat(_information);
			if (listClass.sortFile.sortContent(data)) {
				returnValue = listClass.commandType::SORT;
			}
			else {
				returnValue = (listClass.commandType::SORT + 12);
			}
			break;

		case listClass.EXIT:
			_isEnd = true;
			return listClass.commandType::EXIT;

		default:
			if (_userInput == "") {
				return listClass.commandType::DO_NOTHING;
			}
			return listClass.commandType::INVALID;
	}
	data.updateFile(data);
	data.savePrevFile();
	return returnValue;
}

bool Parser::getIndex(DataStore &data, int &index) {
	size_t found = _information.find_first_of("0123456789");
	size_t found2 = _information.find_first_not_of("0123456789", found);
	
	if (found == std::string::npos) {
		return false;
	}
	if (found2 == std::string::npos) {
		found2 = _information.size();
	}
	std::string str = data.get_tempEntry().subject.substr(found, found2 - found);
	data.get_tempEntry().subject = data.get_tempEntry().subject.substr(0, found) + data.get_tempEntry().subject.substr(found2);
	removeFrontChar(data.get_tempEntry().subject);
	index = atoi(str.c_str());
	return true;
}

bool Parser::getEditDelete(DataStore &data, Classes listClass, int &index, int &cat, std::string str) {
	if (!getIndex(data, index)) {
		return false;
	}
	std::string word = "";
	size_t found = 0;
	size_t found2 = 0;

	while (listClass.determineSubCat(word) == listClass.subCategory::INVALIDCAT) {
		found = str.find_first_not_of(" ", found2);
		if (found == std::string::npos) {
			return false;
		}
		found2 = str.find_first_of(" ", found);
		if (found2 == std::string::npos) {
			found2 = str.size();
		}
		word = str.substr(found, found2 - found);
	}

	if (listClass.determineSubCat(word) == listClass.subCategory::INVALIDCAT) {
		return false;
	}
	found = data.get_tempEntry().subject.find(word);
	if (found != std::string::npos) {
		data.get_tempEntry().subject = data.get_tempEntry().subject.substr(0, found) + data.get_tempEntry().subject.substr(found + word.size());
		removeFrontChar(data.get_tempEntry().subject);
	}
	cat = listClass.determineSubCat(word);
	return true;
}

//To separate out the information into its time, date, category, priority and subject
void Parser::separateWord(Classes &listClass, DataStore &data, bool &pastDate, bool & checkTime) {
	date = false;
	time = false;
	cat = false;
	priority = false;
	
	retrieveDate(listClass, pastDate);
	std::cout << "1 " << _information << std::endl;
	retrieveTime(listClass, checkTime);
	std::cout << "2 " << _information << std::endl;
	retrievePriority(listClass);
	retrieveCategory(listClass);
	retrieveComplete(listClass, data);
	
	if (time) {
		data.get_tempEntry().startTime = listClass.time.getStart(); 
		data.get_tempEntry().endTime = listClass.time.getEnd();
		if (data.get_tempEntry().startTime == data.get_tempEntry().endTime) {
			data.get_tempEntry().isTimedTask = false;
		}
		else {
			data.get_tempEntry().isTimedTask = true;
		}
	}
	else {
		data.get_tempEntry().startTime = 0;
		data.get_tempEntry().endTime = 0;
		data.get_tempEntry().isTimedTask = false;
	}
	std::cout << "2 " << data.get_tempEntry().startTime << '-' << data.get_tempEntry().endTime << std::endl;
	
	if (date) {
		data.get_tempEntry().day = listClass.date.getDay(); 
		data.get_tempEntry().month = listClass.date.getMonth(); 
		data.get_tempEntry().year = listClass.date.getYear();
		data.get_tempEntry().isFloat = false;
		if (!data.get_tempEntry().isTimedTask && data.get_tempEntry().startTime == 0 && data.get_tempEntry().endTime == 0) {
			data.get_tempEntry().startTime == 2359;
		}
	}
	else {
		data.get_tempEntry().day = 0;
		data.get_tempEntry().month = 0; 
		data.get_tempEntry().year = 0;
		data.get_tempEntry().isFloat = true;
	}
	std::cout << "1 " << data.get_tempEntry().day << '/' << data.get_tempEntry().month << std::endl;

	if (priority) {
		data.get_tempEntry().priority = listClass.priority.getPriority();
	}
	else {
		data.get_tempEntry().priority = "LOW";
	}

	if (cat) {
		data.get_tempEntry().category = listClass.category.getCat();
	}
	else {
		data.get_tempEntry().category = "INBOX   ";
	}
	
	removeFrontChar(_information);
	removeBackChar(_information);
	data.get_tempEntry().subject = _information;
	return;
}

void Parser::retrieveComplete(Classes &listClass, DataStore &data) {
	size_t found = _information.find(" | yes ");
	
	if (found != std::string::npos) {
		data.get_tempEntry().isComplete = true;
	}
	else {
		data.get_tempEntry().isComplete = false;
	}
	return;
}

void Parser::retrieveDate(Classes &listClass, bool &pastDate) {
	std::string dStr = _information;
	size_t start = 0;
	size_t end = 0;
	int count = 0;

	do {
		if (!listClass.date.extractDate(dStr, pastDate, _information, start)) {
			updateStr(dStr, start, end);
		}
		else {
			joinStr(dStr, start);
			if (start == 0) {
				cutExtraWord(start, count, TIME_DATE);
			}
			else {
				cutExtraWord(start - 1, count, TIME_DATE);
			}
			date = true;
			return;
		}
	} while (end != std::string::npos);
	return;
}

void Parser::retrieveTime(Classes &listClass, bool &checkTime) {
	std::string tStr = _information;
	int count = 0;
	size_t start = 0;
	size_t end = 0;
	int i = 0;

	do {
		if (listClass.time.extractTime(tStr, count, checkTime)) {
			if (count == 1) {
				listClass.time.updateTime();
			}
			joinStr(tStr, start);
			i = 0;
			if (start == 0) {
				cutExtraWord(start, i, TIME_DATE);
			}
			else {
				cutExtraWord(start - 1, i, TIME_DATE);
			}
			time = true;
			return;
		}
		updateStr(tStr, start, end);
	} while (end != std::string::npos);
	return;
}

void Parser::retrievePriority(Classes &listClass) {
	std::string pStr = _information;
	std::string str = "";
	size_t start = 0;
	size_t end = 0;
	int i = 0;
	int impt = 0;
	size_t found = 0;

	do {
		getFirstWord(listClass, str, pStr, start, found);
		impt = listClass.determineP(str);
		if (!listClass.priority.extractPriority(impt, pStr, found)) {
			updateStr(pStr, start, end);
		}
		else {
			joinStr(pStr, start);
			if (start == 0) {
				cutExtraWord(start, i, CAT_IMPT);
			}
			else {
				cutExtraWord(start - 1, i, CAT_IMPT);
			}
			priority = true;
			return;
			}	
	} while (end != std::string::npos);
	return;
}

void Parser::retrieveCategory(Classes &listClass) {
	std::string pStr = _information;
	std::string str = "";
	size_t start = 0;
	size_t end = 0;
	size_t found = 0;
	int word = 0;
	int catNum = 0;

	do {
		getFirstWord(listClass, str, pStr, start, found);
		catNum = listClass.determineC(str);
		if (!listClass.category.extractCat(catNum, pStr, found)) {
			updateStr(pStr, start, end);
		}
		else {
			joinStr(pStr, start);
			if (start == 0) {
				cutExtraWord(start, word, CAT_IMPT);
			}
			else {
				cutExtraWord(start - 1, word, CAT_IMPT);
			}
			cat = true;
			return;
		}	
	} while (end != std::string::npos);
	return;
}

//To remove words keyed in by the user that are not the subject
//Checks the next word only and up to three previous words
void Parser::cutExtraWord(size_t found, int count, int cat) {
	std::string word = "";
	size_t find = 0;
	size_t check = _information.find_first_of(",.?!", found);
	if (check == std::string::npos) {
		check = _information.size();
	}
	
	//Checks the next word only
	if (count == 0) {
		find = _information.find_first_not_of(" ", found);
		if (find != std::string::npos && check > find) {
			find = _information.find_first_of(" ", find);
			if (find == std::string::npos) {
				find = word.size() - 1;
			}
			word = _information.substr(found, find - found);
			removeFrontChar(word);
			removeBackChar(word);
			extraWord(word, found, cat, BACK, count);
		}
	}
	
	//To ensure that removal is up to 3 words only
	if (count > 3) {
		return;
	}

	check = _information.find_last_not_of(",.?!", found);
	if (check == std::string::npos) {
		check = 0;
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
	removeFrontChar(word);
	removeBackChar(word);
	
	//Uses recursion to check up to three previous words
	if (check > find && extraWord(word, find, cat, FRONT, count)) {
		count++;
		return cutExtraWord(find, count, cat);
	}
	return;
}

void Parser::getFirstWord(Classes listClass, std::string &str, std::string pStr, size_t start, size_t &found) {
	found = _information.find_first_of(" ", start);
	removeBackChar(pStr);
	if (found == std::string::npos) {
		found = _information.size();
	}
	str = _information.substr(start, found - start);
	found = pStr.find(str) + str.size();
	return;
}

//Identifies if the words is an extra
//3 different vector for three different cases since there are different extra words before and after 
//for different types (time & date, category & importance) 
bool Parser::extraWord(std::string word, size_t found, int cat, int frontOrBack, int count) {
	changeToLower(word);
	removeBackChar(word);

	size_t find = 0;
	std::vector <std::string>::iterator iter;
	int size = 0;

	if (cat == TIME_DATE && frontOrBack == FRONT) {
		if (count == 0) {
			iter = extraFront.begin();
			size = extraFront.size();
		}
		else {
			iter = extraFront2.begin();
			size = extraFront2.size();
		}
	}
	else if (TIME_DATE && frontOrBack == BACK) {
		iter = extraBack.begin();
		size = extraBack.size();
	}
	else {
		iter = extraCatImpt.begin();
		size = extraCatImpt.size();
	}

	while (size > 0) {
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
		size--;
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

void Parser::removeFrontChar(std::string &str) {
	size_t found;
	found = str.find_first_of(" ,.-?!:;");

	while (found != std::string::npos && found == 0) {
		str = str.substr(1);
		found = str.find_first_of(" .,-?!:;");
	}
	return;
}

void Parser::removeBackChar(std::string &str) {
	size_t found;
	found = str.find_last_of(" ,.-?!:;");

	while (found != std::string::npos && found == str.size() - 1) {
		str = str.substr(0, str.size() - 1);
		found = str.find_last_of(" ,.-?!:;");
	}
	return;
}

//Returns the index of the next word in the variable 'end'
void Parser::getNextWord (std::string &tStr, size_t &start, size_t &end) {
	end = tStr.find_first_of(" ", start);
	if (end == std::string::npos) {
		return;
	}
	end = tStr.find_first_not_of(" ", end);
	return;
}

//Cuts out the first word so as to check the next word
void Parser::updateStr(std::string &tStr, size_t &start, size_t &end) {
	getNextWord(_information, start, end);
	if (end != std::string::npos) {
		tStr = _information.substr(end);
		start = end;
	}
	return;
}

//Updates the information string once a time, date, category or priority is found
void Parser::joinStr(std::string &tStr, size_t &start) {
	_information = _information.substr(0, start);
	_information = _information + tStr;
	return;
}

std::string &Parser::getInfo() {
	return _information;
}