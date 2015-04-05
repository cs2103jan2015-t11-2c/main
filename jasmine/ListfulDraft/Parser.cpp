#include "Parser.h"

//Separates the user input to be the command string and information string
void Parser::init(std::string command) {
	TIME_DATE = 1;
	CAT_IMPT = 2;
	FRONT = 1;
	BACK = 2;

	extra.push_back("from");
	extra.push_back("now");
	extra.push_back("until");
	extra.push_back("due");
	extra.push_back("by"); 
	extra.push_back("on");
	extra.push_back("do");
	extra.push_back("at");
	extra.push_back("to");
	extra.push_back("up");
	extra.push_back("after");
	extra.push_back("before");
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
	extra.push_back("date");
	extra.push_back("time");

	extraBack.push_back("onwards");
	
	extraCAT_IMPT.push_back("of");
	extraCAT_IMPT.push_back("category");
	extraCAT_IMPT.push_back("priority");
	extraCAT_IMPT.push_back("importance");
	extraCAT_IMPT.push_back("impt");
	extraCAT_IMPT.push_back("cat");

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
		return true;
	}
	return false;
}

int Parser::determineCommand() {
	if (_userInput == "add" || _userInput == "1") {
		return commandType::ADD;
	}
	else if (_userInput == "display" || _userInput == "2") {
		return commandType::DISPLAY;
	}
	else if (_userInput == "delete" || _userInput == "3") {
		return commandType::REMOVE;
	}
	else if (_userInput == "clear" || _userInput == "4") {
		return commandType::CLEAR;
	}
	else if (_userInput == "edit" || _userInput == "5") {
		return commandType::EDIT;
	}
	else if (_userInput == "sort" || _userInput == "6") {
		return commandType::SORT;
	}
	else if (_userInput == "search" || _userInput == "7") {
		return commandType::SEARCH;
	}
	else if (_userInput == "exit" || _userInput == "8") {
		return commandType::EXIT;
	}
	else if (_userInput == "undo") {
		return commandType::UNDO;
	}
	else if (_userInput == "redo") {
		return commandType::REDO;
	}
	else {
		return commandType::INVALID;
	}
}

//determine what category user chooses to sort by
int Parser::determineCategory(std::string info) {
	if (info == "date") {
		return subCategory::DATE;
	}
	else if (info == "time") {
		return subCategory::TIME;
	}
	else if (info == "priority" || info == "impt" || info == "importance") {
		return subCategory::PRIORITY;
	}
	else if (info == "category" || info == "cat") {
		return subCategory::CATEGORY;
	}
	else if (info == "sub" || info == "subject" || info == "alphabetically") {
		return subCategory::SUBJECT;
	}
	else {
		return subCategory::INVALIDCAT;
	}
}

int Parser::carryOutCommand(Classes &listClass, DataStore &data, std::ostringstream &errMsg) {
	int command = determineCommand();
	errMsg.clear();

	switch(command) {
		case ADD:
			separateWord(listClass, data);
			if (listClass.add.addContent(data, errMsg)) {
				return commandType::ADD;
			}
			return (commandType::ADD + 11);
		case DISPLAY: {
			int i = 0;
			if (data.getData().empty()) {
				return (commandType::DISPLAY + 11);
			}

			while (data.getData()[i].isFloat) {
				if (i == 0) {
					std::cout << "floating task(s):" << std::endl;
				}
				std::cout << (i + 1) << ". " << data.getDataString(i) << std::endl;
				i++;
			}
			int count = 0;
			while (i < data.getData().size() && !(data.getData()[i].isFloat)) {
				if (count == 0) {
					std::cout << "non-floating task(s):" << std::endl;
				}
				std::cout << (i + 1) << ". " << data.getDataString(i) << std::endl;
				i++;
				count++;
			}
			break;
			}																																																																		
		case CLEAR:
			if (listClass.clearFile.clearFile(data)) {
				return commandType::CLEAR;
			}
			return (commandType::CLEAR + 11);
		case EDIT: {
			std::string command, editInput;
			int index;
			editInput = _information.substr(2);
			index = atoi(_information.substr(0).c_str());
			command = editInput.substr(0, editInput.find_first_of(" ")+1);
			command = command.substr(0, editInput.find_first_of(" "));
			_information = command;
			listClass.edit.getCat() = determineCategory(_information);
			editInput = editInput.substr(editInput.find_first_of(" ")+1);

			if (listClass.edit.editContent(data, editInput, index-1)) {
				return commandType::EDIT;
			}
			return (commandType::EDIT + 11);
			}
		case REMOVE:
			if (listClass.remove.deleteContent(data, _information, errMsg)) {
				return commandType::REMOVE;
			}
			return (commandType::REMOVE + 11);
		case REDO:
			if (data.redoData()) {
				return commandType::REDO;
			}
			return (commandType::REDO + 11);
		case UNDO:
			if (data.undoData()) {
				return commandType::UNDO;
			}
			return (commandType::UNDO + 11);
		case SEARCH: {
			std::string command, keyword;
			command = _information.substr(0, _information.find_first_of(" "));
			keyword = _information.substr(_information.find_first_of(" ")+1);
			keyword = keyword.substr(0, keyword.find_first_of(" "));
			_information = command;
			listClass.searchFile.getCat() = determineCategory(_information);
			keyword = keyword.substr(keyword.find_first_of(" ")+1);
			if (listClass.searchFile.searchFile(data, keyword, errMsg)) {
				return commandType::SEARCH;
			}
			return (commandType::SEARCH + 11);
			}
		case SORT:
			changeToLower(_information);
			listClass.sortFile.getSortCat() = determineCategory(_information);
			if (listClass.sortFile.sortContent(data)) {
				return commandType::SORT;
			}
			return (commandType::SORT + 11);
		case EXIT:
			_isEnd = true;
			break;
		default:
			return commandType::INVALID;
	}
	return commandType::DO_NOTHING;
}

//To separate out the information into its time, date, category, priority and subject
void Parser::separateWord(Classes &listClass, DataStore &data) {
	date = false;
	time = false;
	cat = false;
	priority = false;
	
	retrieveTime(listClass);
	retrieveDate(listClass);
	retrievePriority(listClass);
	retrieveCategory(listClass);

	removeFrontChar(_information);
	removeBackChar(_information);
	data.get_tempEntry().subject = _information;
	data.get_tempEntry().isComplete = false;

	if (time) {
		data.get_tempEntry().startTime = listClass.time.getStart(); 
		data.get_tempEntry().endTime = listClass.time.getEnd();
	}
	else {
		data.get_tempEntry().startTime = 0;
		data.get_tempEntry().endTime = 0;
	}

	if (date) {
		data.get_tempEntry().day = listClass.date.getDay(); 
		data.get_tempEntry().month = listClass.date.getMonth(); 
		data.get_tempEntry().year = listClass.date.getYear(); ;
		data.get_tempEntry().isFloat = false;
	}
	else {
		data.get_tempEntry().day = 0;
		data.get_tempEntry().month = 0; 
		data.get_tempEntry().year = 0;
		data.get_tempEntry().isFloat = true;
	}

	if (priority) {
		data.get_tempEntry().priority = listClass.priority.getPriority();
	}
	else {
		data.get_tempEntry().priority = "LOW  ";
	}
	if (cat) {
		data.get_tempEntry().category = listClass.category.getCat();
	}
	else {
		data.get_tempEntry().category = "INBOX    ";
	}
	return;
}

void Parser::retrieveDate(Classes &listClass) {
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

void Parser::retrieveTime(Classes &listClass) {
	std::string tStr = _information;
	int count = 0;
	size_t start = 0;
	size_t end = 0;
	int word = 0;

	do {
		if (listClass.time.extractTime(tStr, count, start, _information)) {
			if (count == 1) {
				listClass.time.updateTime();
			}
			joinStr(tStr, start);
			if (start == 0) {
				cutExtraWord(start, word, TIME_DATE);
			}
			else {
				cutExtraWord(start - 1, word, TIME_DATE);
			}
		//	listClass.time.checkStartEnd();
			time = true;
			return;
		}
		updateStr(tStr, start, end);
	} while (end != std::string::npos);
	return;
}

void Parser::retrievePriority(Classes &listClass) {
	std::string pStr = _information;
	size_t start = 0;
	size_t end = 0;
	int word = 0;

	do { 
		if (!listClass.priority.extractPriority(pStr)) {
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
			priority = true;
			return;
			}	
	} while (end != std::string::npos);
	return;
}

void Parser::retrieveCategory(Classes &listClass) {
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
	
	//Checks the next word only
	if (count == 0) {
		find = _information.find_first_not_of(" ,.?!", found);
		if (find != std::string::npos) {
			find = _information.find_first_of(" ", find);
			if (find == std::string::npos) {
				find = word.size() - 1;
			}
			word = _information.substr(found, find - found);
			removeFrontChar(word);
			removeBackChar(word);
			extraWord(word, found, cat, BACK);
		}
	}
	
	//To ensure that removal is up to 3 words only
	if (count > 3) {
		return;
	}

	find = _information.find_last_not_of(" .,?!", found);
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
	if (extraWord(word, find, cat, FRONT)) {
		count++;
		return cutExtraWord(find, count, cat);
	}
	return;
}

//Identifies if the words is an extra
//3 different vector for three different cases since there are different extra words before and after 
//for different types (time & date, category & importance) 
bool Parser::extraWord(std::string word, size_t found, int cat, int frontOrBack) {
	changeToLower(word);
	removeBackChar(word);

	size_t find = 0;
	std::vector <std::string>::iterator iter;
	int size = 0;

	if (cat == TIME_DATE && frontOrBack == FRONT) {
		iter = extra.begin();
		size = extra.size();
	}
	else if (TIME_DATE && frontOrBack == BACK) {
		iter = extraBack.begin();
		size = extraBack.size();
	}
	else {
		iter = extraCAT_IMPT.begin();
		size = extraCAT_IMPT.size();
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