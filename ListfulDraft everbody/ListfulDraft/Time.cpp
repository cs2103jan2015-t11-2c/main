#include "Time.h"

Time::Time() {
	_startTime = 0;
	_endTime = 0;
}

//to change case
void Time::changeToLower(std::string &str) {
	int i = 0;
	for (i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = 'a' + (str[i] - 'A');
		}
	}
	return;
}

//to check validity of hour
bool Time::checkHourValid(int num) {
	int time = num/100;
	if (time > 23) {
		return false;
	}
	return true;
}

//to check validity of minute
bool Time::checkMinValid(int num) {
	int min = num%100;
	if (min > 59) {
		return false;
	}
	return true;
}

//Cuts off 'am' and 'pm'
void Time::updateStr(std::string &originalStr, std::string &line, size_t found) {
	size_t space = line.find_first_of(" ", found+2);
	if (space == std::string::npos) {
		originalStr = "";
	}
	else {
		line = line.substr(space + 1);
		originalStr = originalStr.substr(originalStr.size() - line.size());
	}
	return;
}

//to extract numbers
bool Time::extractNum (std::string line, int &count, int &num) {
	size_t start = 0;
	size_t end = 0;
	int noOfMin = 0;
	size_t nonNum = line.find_first_of(".:", start);
	if (!(nonNum != std::string::npos && nonNum < 2)) {
		nonNum = std::string::npos;
	}

	while (end != std::string::npos  && (line[end] >= '0' && line[end] <= '9')) {
		if (end == (start + count)) {
			num = (num * 10) + (line[end] - '0');
			count++;
		}
  		else if (end == (start + count + 1) && nonNum != std::string::npos) {
			num = (num * 10) + (line[end] - '0');
			count++;
			noOfMin++;
		}
		end = line.find_first_of("0123456789", end + 1);
	}
	if (count == 1 && num == 0) {
		return false;
	}
	else if (nonNum != std::string::npos && noOfMin != 2) {
		return false;
	}
	else if (count <= 4 && count != 0) {
		return true;
	}
	return false;
}

//Assume that the task will take one hour if the user doesnt key in an end time
void Time::updateTime() {
	_endTime = _startTime + 100;

	if (_endTime == 2400) {
		_endTime = 0;
	}
	return;
}

// to remove characters that are not supposed to be in the time
void Time::removeNonTimeChar(std::string &str) {
	size_t found;
	found = str.find_first_of(" -");

	while (found != std::string::npos && found == 0) {
		str = str.substr(1);
		found = str.find_first_of(" -");
	}
	return;
}

// to count the number of words
int Time::countWord(std::string str) {
	size_t nextTime = str.find_first_of("0123456789");
	size_t index = str.find_first_of(" ,");
	int count = 0;

	while (index != std::string::npos && nextTime != std::string::npos) {
		if (index < nextTime) {
			removeNonTimeChar(str);
			index = str.find_first_of(" ,", index + 1);
			count++;
		}
		else {
			return count;
		}
	}
	return count;
}

// to extract the time
bool Time::checkDate(std::string line, int count) {
	size_t start = count;
	changeToLower(line);
	size_t find = line.find("am");
	
	if (line[start] == '/') {
		return true;
	}
	start = line.find_first_of("jfmajsnodJFMAJSNOD", start);
	if (line[start] != std::string::npos && ((start - count) < 2)) {
		if (find == std::string::npos) {
			return true;
		}
		else if (find - count >= 2) {
			return true;
		}
	}
	return false;
}

bool Time::takeTime(std::string &originalStr, std::string &line, int &noOfTime) {
	int count = 0;
	int time = 0;

	if (!extractNum(line, count, time)) {
		return false;
	}

	if (checkDate(line, count)) {
		return false;
	}
	checkAMPM(originalStr, line, count, time);
	if (time < 100 && count != 4) {
		return false;
	}
	else if (!(checkHourValid(time) && checkMinValid(time))) {
		return false;
	}
	else if (noOfTime == 0) {
		_startTime = time;
		noOfTime++;
		time = 0;
	}
	else if (noOfTime == 1) {
		_endTime = time;
		noOfTime++;
	}
	return true;
}

// to check am and  pm
void Time::checkAMPM (std::string &originalStr, std::string &line, int count, int &num) {
	changeToLower(line);
	size_t foundAM = line.find("am");
	size_t foundAM2 = line.find("a.m");
	size_t foundPM = line.find("pm");
	size_t foundPM2 = line.find("p.m");

	if (foundAM != std::string::npos && ((foundAM - count) <= 2)) {
		if (count <= 2 && num == 12) {
			num = 0;
		}
		else if (count <= 2) {
			num = num * 100;
		}
		updateStr(originalStr, line, foundAM);
	}
	else if (foundAM2 != std::string::npos && ((foundAM2 - count) <= 2)) {
		if (count <= 2 && num == 12) {
			num = 0;
		}
		else if (count <= 2) {
			num = num * 100;
		}
		updateStr(originalStr, line, foundAM2);
	}
	else if (foundPM != std::string::npos && ((foundPM - count) <= 2)) {
		if (count <= 2) {
			num = (num * 100) + 1200;
		}
		else {
			num = num + 1200;
		}
		updateStr(originalStr, line, foundPM);
	}
	else if (foundPM2 != std::string::npos && ((foundPM2 - count) <= 2)) {
		if (count <= 2) {
			num = (num * 100) + 1200;
		}
		else {
			num = num + 1200;
		}
		updateStr(originalStr, line, foundPM2);
	}
	else {
		if (count <= 2) {
			num = (num * 100) + 1200;
		}
		else if (count < 4) {
			num = num + 1200;
		}
		originalStr = originalStr.substr(count + 1);
	}

	if (num == 2400) {
		num = 1200;
	}
	removeNonTimeChar(originalStr);
	return;
}

//to extract the time
bool Time::extractTime (std::string &line, int &noOfTime) {
	std::string str = line;
	std::string tStr = line;
	size_t index = 0;
	int noOfWord = 0;

	if (takeTime(str, tStr, noOfTime)) {
		noOfWord = countWord(str);
		if (noOfWord > 2 || noOfWord == 0) {
			line = str;
			return true;
		}
		else {
			while (noOfWord > 0) {
				index = str.find_first_of(" ,", index);
				index = str.find_first_not_of(" ,", index);
				noOfWord--;
			}
			str = str.substr(index);
			removeNonTimeChar(str);
			tStr = str;
			if (takeTime(str, tStr, noOfTime)) {
				line = str;
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}
}

/*void Time::checkStartEnd() {
	//Assume that a to do task with time entered requires at most 6 hours to complete
	if ((_endTime > _startTime) && (_startTime >= 1200)) {
		_startTime = _startTime - 1200;
	}
}*/

//to get start time
int Time::getStart() {
	return _startTime;
}

//to get end time
int Time::getEnd() {
	return _endTime;
}