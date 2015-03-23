#include "Time.h"

Time::Time() {
	_startTime = 0;
	_endTime = 0;
}

void Time::changeToLower(std::string &str) {
	int i;
	for (i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = 'a' + (str[i] - 'A');	
		}
	}
}

//Convert to 24 hours format 
//Assume that all are pm unless specified
void Time::convertToTFH(std::string line, size_t foundAM, size_t foundAM2, size_t foundPM, size_t foundPM2, int count, int &num) {
	if ((foundAM != std::string::npos || foundAM2 != std::string::npos) && count <= 2 && num == 12) {
		num = 0;
	}
	else if ((foundAM != std::string::npos || foundAM2 != std::string::npos) && count <= 2) {
	num = num * 100;
	}
	else if ((foundPM != std::string::npos || foundPM2 != std::string::npos) && count <= 2) {
		num = (num * 100) + 1200;
		if (num == 2400) {
			num = 1200;
		}
	}
	else if (foundPM != std::string::npos || foundPM2 != std::string::npos) {
	num = num + 1200;
	}
	else if (count <= 2) {
		
		num = (num * 100) + 1200;
	}
	else if (count < 4) {
		num = num + 1200;
	}
	
}

//Check hour valid
bool Time::checkHourValid(int count, int &num) {
	if (count > 2) {
		return false;
	}
	if (num > 23) {
		return false;
	}
	return true;
}

bool Time::checkMinValid(int &num, int count) {
	int min = num%100;
	if (min > 59) {
		return false;
	}
	return true;
}

void Time::updateStr(std::string &originalStr, std::string &line, size_t found) {
	size_t space = line.find_first_of(" ", found);
	if (space == std::string::npos) {
		originalStr = "";
	}
	else {
		line = line.substr(space);
		originalStr = originalStr.substr(originalStr.size() - line.size());
	}
}

bool Time::checkRealTime (std::string &originalStr, std::string &line, int &i, int &count, int &num) {	
	size_t foundAM = line.find("am");
	size_t foundAM2 = line.find("a.m");
	size_t foundPM = line.find("pm");
	size_t foundPM2 = line.find("p.m");
	size_t space;
	
	if (count == 0 || count > 4) {
		return false;
	}
	
	if (foundAM != std::string::npos && ((foundAM - count) > 1)) {
		return false;
	}
	else if (foundAM2 != std::string::npos && ((foundAM2 - count) > 1)) {
		return false;
	}
	else if (foundPM != std::string::npos && ((foundPM - count) > 1)) {
		return false;
	}
	else if (foundPM2 != std::string::npos && ((foundPM2 - count) > 1)) {
		return false;
	}
	else {
		convertToTFH(line, foundAM, foundAM2, foundPM, foundPM2, count, num);
		if (num == 2400) {
			num = 0;
		}
		else if (num > 2359 || (num < 100 && count != 4)) {
			return false;
		}
		if (!checkMinValid(num, count)) {
			return false;
		}
		
		if (foundAM != std::string::npos) {
			updateStr(originalStr, line, foundAM);
		}
		else if (foundPM != std::string::npos) {
			updateStr(originalStr, line, foundPM);
		}
		else if (foundAM2 != std::string::npos) {
			updateStr(originalStr, line, foundAM2);
		}
		else if (foundPM2 != std::string::npos) {
			updateStr(originalStr, line, foundPM2);
		}
		else {
			originalStr = originalStr.substr(count);
		}
	}

}

void Time::convertTime (std::string line, int &i,int &num, int &count) {
	while ((i < line.size()) && (line[i] >= '0' && line[i] <= '9')) {
		num = (num * 10) + (line[i] - '0');
		count++;
		i++;
	}
}

bool Time::extractTime (std::string &line, int noOfWord) {
	std::string str = line;
	int i;
	int count = 0;
	int num = 0;

	changeToLower(str);
	
	for (i = 0; i <= str.size(); i++) {
		convertTime(str, i, num, count);
		if (str[i] == '.' || str[i] == ':' || str[i] == '-') {
			if (!checkHourValid(count, num)) {
				return false;
			}
			i++;
			convertTime(str, i, num, count);
		}
		if (!checkRealTime(line, str, i, count, num)) {
			return false;
		}
		else if (noOfWord == 0) {
			_startTime = num;
			return true;
		}
		else if (noOfWord == 1) {
			_endTime = num;
			return true;
		}
	}
}

//Assume that the task will take one hour if the user doesnt key in an end time
void Time::updateTime() {
	_endTime = _startTime + 100;

	if (_endTime == 2400) {
		_endTime = 0;
	}
}

void Time::checkStartEnd() {
	//Assume that a to do task with time entered requires at most 6 hours to complete
	if ((_endTime - _startTime) > 600 && (_endTime != 0)) {
		_endTime = _endTime - 1200;
	}
}

int Time::getStart() {
	return _startTime;
}

int Time::getEnd() {
	return _endTime;
}