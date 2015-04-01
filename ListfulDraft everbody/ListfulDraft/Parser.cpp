#include "Parser.h"

//Separates the user input to be the command string and information string
void Parser::init(std::string command) {
	TIME_DATE = 1;
	CAT_IMPT = 2;
	FRONT = 1;
	BACK = 2;

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
	else if (_userInput == "delete" || _userInput == "4") {
		return commandType::REMOVE;
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

//determine what category user chooses to sort by
int Parser::determineCategory() {
	if (_information == "date") {
		return subCategory::DATE;
	}
	else if (_information == "time") {
		return subCategory::TIME;
	}
	else if (_information == "priority" || _information == "impt" || _information == "importance") {
		return subCategory::PRIORITY;
	}
	else if (_information == "category" || _information == "cat") {
		return subCategory::CATEGORY;
	}
	else if (_information == "sub" || _information == "subject" || _information == "alphabetically") {
		return subCategory::SUBJECT;
	}
	else {
		return subCategory::INVALIDCAT;
	}
}

int Parser::carryOutCommand(Classes &listClass, DataStore &data) {
	int command = determineCommand();

	switch(command) {
		case commandType::ADD:
			separateWord(listClass, data);
			if (listClass.add.addContent(data)) {
				return commandType::ADD;
			}
			else {
				return 0; //add error
			}
			break;
		case commandType::DISPLAY:
			break;
		case commandType::CLEAR:
			if (listClass.clearFile.clearFile(data)) {
				return commandType::CLEAR;
			}
			else {
				return 0; //clear error
			}
			break;
		case commandType::EDIT:{
			std::string command, editInput;
			int index;
			editInput = _information.substr(2);
			index = atoi(_information.substr(0).c_str());
			command = editInput.substr(0, editInput.find_first_of(" ")+1);
			command = command.substr(0, editInput.find_first_of(" "));
			_information = command;
			int category = determineCategory();
			editInput = editInput.substr(editInput.find_first_of(" ")+1);

			if (listClass.edit.editContent(data, editInput, index-1, category)) {
				return commandType::EDIT;
			}
			else {
				return 0; //edit error
			}
			break;
							   }

	/*	case commandType::REMOVE:{
			int index;
			index = atoi(_information.substr(0).c_str());
			if (listClass.remove.deleteContent(data, index-1)) {
				return commandType::REMOVE;
			}
			else {
				return 0; //delete error
			}*/

		case commandType::REMOVE: 
			listClass.remove.deleteContent(data, _information);
			return commandType::REMOVE;
			break;
								 
		case commandType::REDO:
			data.redoData();
			break;
							   
		case commandType::UNDO:
			data.undoData();
			break;
		case commandType::SEARCH:{
			std::string command, keyword;
			command = _information.substr(0, _information.find_first_of(" "));
			keyword = _information.substr(_information.find_first_of(" ")+1);
			keyword = keyword.substr(0, keyword.find_first_of(" "));
			_information = command;
			int category = determineCategory();
			keyword = keyword.substr(keyword.find_first_of(" ")+1);
		
			if (listClass.search.searchFile(data, keyword, category)) {
			return commandType::SEARCH;
			}
			else {
				return 0; //search error
			}
			break;
								 }
		case commandType::SORT:
			listClass.sortFile.getSortCat() = determineCategory();
			if (listClass.sortFile.sortContent(data)) {
				return commandType::SORT;
			}
			else {
				return 0; //sort error
			}
			break;
		case commandType::EXIT:
			_isEnd = true;
			break;
		case commandType::INVALID:
			break;
	}
	

	return commandType::INVALID;
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
		data.get_tempEntry().month =listClass.date.getMonth(); 
		data.get_tempEntry().year = listClass.date.getYear(); ;
		data.get_tempEntry().isFloat = false;
	}
	else {
		data.get_tempEntry().day = 0;
		data.get_tempEntry().isFloat = true;
	}

	if (priority) {
		data.get_tempEntry().priority = _priority;
	}
	else {
		data.get_tempEntry().priority = "LOW  ";
	}
	if (cat) {
		data.get_tempEntry().category = _cat;
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
		if (listClass.time.extractTime(tStr, count)) {
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
			_priority = listClass.priority.getPriority();
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
			_cat = listClass.category.getCat();
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
	std::vector <std::string> extra;
	std::vector <std::string> extraBack;
	std::vector <std::string> extraCAT_IMPT;
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

int &Parser::getDay() {
	return _day;
}

int &Parser::getMonth() {
	return _month;
}

int &Parser::getYear() {
	return _year;
}

int &Parser::getSTime() {
	return _sTime;
}
		
int &Parser::getETime() {
	return _eTime;
}

std::string &Parser::getCat() {
	return _cat;
}

std::string &Parser::getPriority() {
	return _priority;
}


