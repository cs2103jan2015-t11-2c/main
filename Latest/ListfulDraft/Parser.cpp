#include "Parser.h"

//Separates the user input to be the command string and information string and initialises private vector in parser
void Parser::init(std::string info) {
	extraFront.push_back("from");
	extraFront.push_back("due");
	extraFront.push_back("by"); 
	extraFront.push_back("on");
	extraFront.push_back("at");
	extraFront.push_back("to");
	extraFront.push_back("before");
	extraFront.push_back("for");
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
	extraFront2.push_back("also");
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

	_information = info;
	removeFrontChar(_information);
	removeBackChar(_information);
	return;
}



void Parser::separateWord(DataStore &data, bool &pastDate, bool & checkTime) {
	date = false;
	time = false;
	cat = false;
	priority = false;
	complete = false;
	
	retrieveDate(pastDate);
	retrieveTime(checkTime);
	retrievePriority();
	retrieveCategory();
	retrieveCompleteAndRefNo(data);
	
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
		data.get_tempEntry().category = "GENERAL ";
	}
	
	removeFrontChar(_information);
	removeBackChar(_information);
	data.get_tempEntry().subject = _information;
	return;
}



bool Parser::getMonth(DataStore &data) {
	int month = listClass.date.determineMonth(_information);
	if (month < 13) {
		data.get_tempEntry().month = month;
		return true;
	}
	return false;
}

void Parser::retrieveDate(bool &pastDate) {
	std::string dStr = _information;
	size_t start = 0;
	size_t end = 0;
	int count = 0;
	bool getNewDate = false;

	do {
		if (!listClass.date.checkForDate(dStr, pastDate, _information, start, getNewDate)) {
			extractRemainingStr(dStr, start, end);
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

void Parser::retrieveTime(bool &checkTime) {
	std::string tStr = _information;
	int count = 0;
	size_t start = 0;
	size_t end = 0;
	int i = 0;

	do {
		if (listClass.time.checkForTime(tStr, count, checkTime)) {
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
		extractRemainingStr(tStr, start, end);
	} while (end != std::string::npos);
	return;
}

void Parser::retrievePriority() {
	std::string pStr = _information;
	std::string str = "";
	size_t start = 0;
	size_t end = 0;
	int i = 0;
	int impt = 0;
	size_t found = 0;

	do {
		getFirstWord( str, pStr, start, found);
		impt = listClass.determinePriority(str);
		if (!listClass.priority.checkForPriority(impt, pStr, found)) {
			extractRemainingStr(pStr, start, end);
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

void Parser::retrieveCategory() {
	std::string pStr = _information;
	std::string str = "";
	size_t start = 0;
	size_t end = 0;
	size_t found = 0;
	int word = 0;
	int catNum = 0;

	do {
		getFirstWord(str, pStr, start, found);
		catNum = listClass.determineCategory(str);
		if (!listClass.category.checkForCat(catNum, pStr, found)) {
			extractRemainingStr(pStr, start, end);
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

//To separate out the information into its time, date, category, priority and subject
void Parser::retrieveCompleteAndRefNo(DataStore &data) {
	size_t found = _information.find(" | yes");
	if (found != std::string::npos) {
		data.get_tempEntry().isComplete = true;
		complete = true;
	}
	else {
		data.get_tempEntry().isComplete = false;
		complete = false;
	}

	data.get_tempEntry().referenceNo = data.getData().size() + 1;
	return;
}



void Parser::getEditInfo(std::vector <int> &editCat, std::string originalStr) {
	if (time) {
		editCat.push_back(listClass.fieldType::TIME);
	}
	if (date) {
		editCat.push_back(listClass.fieldType::DATE);
	}
	if (priority) {
		editCat.push_back(listClass.fieldType::PRIORITY);
	}
	if (cat) {
		editCat.push_back(listClass.fieldType::CATEGORY);
	}
	if (editCat.size() == 0 || (_information != originalStr && _information != "")) {
		editCat.push_back(listClass.fieldType::SUBJECT);
	}
	return;
}

void Parser::assignCat(DataStore &data, int &category) {
	if (time) {
		category = listClass.fieldType::TIME;
	}
	else if (date) {
		category = listClass.fieldType::DATE;
	}
	else if (priority) {
		category = listClass.fieldType::PRIORITY;
	}
	else if (cat) {
		category = listClass.fieldType::CATEGORY;
	}
	else {
		category = listClass.fieldType::SUBJECT;
	}
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
			isExtraWord(word, found, cat, BACK, count);
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
	if (check > find && isExtraWord(word, find, cat, FRONT, count)) {
		count++;
		return cutExtraWord(find, count, cat);
	}
	return;
}

void Parser::getFirstWord(std::string &str, std::string pStr, size_t start, size_t &found) {
	found = _information.find_first_of(" ", start);
	removeBackChar(pStr);
	if (found == std::string::npos) {
		found = _information.size();
	}
	str = _information.substr(start, found - start);
	found = pStr.find(str) + str.size();
	return;
}

//Identifies if the words is an extra words, meaning a word to complement the other categories
//which we won't want in our subject
//3 different vector for three different cases since there are different extra words before and after 
//for different types (time & date, category & importance) 
bool Parser::isExtraWord(std::string word, size_t found, int cat, int frontOrBack, int count) {
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
void Parser::extractRemainingStr(std::string &tStr, size_t &start, size_t &end) {
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



bool &Parser::getDate() {
	return date;
}

bool &Parser::getTime() {
	return time;
}

bool &Parser::getCat() {
	return cat;
}

bool &Parser::getPriority() {
	return priority;
}

bool &Parser::getComplete() {
	return complete;
}