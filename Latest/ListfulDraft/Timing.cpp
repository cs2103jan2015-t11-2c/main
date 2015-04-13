//@author A0110670W
#include "Timing.h"

Timing::Timing() {
	_startTime = 0;
	_endTime = 0;
	
	_linkWord.push_back("-");
	_linkWord.push_back("to");
	_linkWord.push_back("till");
	_linkWord.push_back("until");
	_linkWord.push_back("up to");
	_linkWord.push_back("up till");
	_linkWord.push_back("up until");
}


bool Timing::extractNum (std::string line, int &count, int &num) {
	size_t end = 0;
	int noOfMin = 0;

	//If time is in 7.00 or 7:00 format for example
	size_t nonNum = line.find_first_of(".:");
	if (nonNum != std::string::npos && nonNum > 2) {
		nonNum = std::string::npos;
	}

	while (end != std::string::npos  && (line[end] >= '0' && line[end] <= '9')) {
		if (end == count) {
			num = (num * 10) + (line[end] - '0');
			count++;
		}
  		else if ((end == count + 1) && nonNum != std::string::npos) {
			num = (num * 10) + (line[end] - '0');
			count++;
			noOfMin++;
		}
		else {
			break;
		}

		if ((end + 1) == line.size()) {
			end = std::string::npos;
		}
		else {
			end = line.find_first_of("0123456789", end + 1);
		}
	}
	if (count == 1 && num == 0) {
		return false;
	}
	else if (nonNum != std::string::npos && noOfMin != 2) {
		return false;
	}
	else if (nonNum != std::string::npos) {
		count++;
		return true;
	}
	else if (count <= 4 && count != 0 && num < 2400) {
		return true;
	}
	return false;
}

bool Timing::checkForTime (std::string &line, int &noOfTime, bool &checkTime) {
	std::string str = line;
	size_t index = 0;
	size_t index2 = 0;
	int noOfWord = 0;

	if (takeTime(str, noOfTime, checkTime)) {
		removeNonTimeChar(str);
		line = str;
		countWord(str, noOfWord);
		if (noOfWord > 3) {
			return true;
		}
		else {
			int temp = noOfWord;
			while (index != std::string::npos && noOfWord > 0) {
				index = str.find_first_of(" -", index);
				if(str[index] == '-') {
					index++;
				}
				else if (index != std::string::npos) {
					index = str.find_first_not_of(" -", index);
				}

				str = str.substr(index);
				removeNonTimeChar(str);
				noOfWord--;
			}
			if (temp != 0 && takeTime(str, noOfTime, checkTime)) {
				checkTime = false;
				checkTime = checkStartEnd();
				line = str;
				return true;
			}
			else {
				line = str;
				return true;
			}
		}
	}
	return false;
}


bool Timing::takeTime(std::string &line, int &noOfTime, bool &checkTime) {
	int count = 0;
	int time = 0;

	if (!extractNum(line, count, time)) {
		return false;
	}

	checkAMPM(line, count, time, checkTime, noOfTime);

	if (!checkTime && time < 100 && count < 4) {
		return false;
	}
	else if (!(isTimeValid(time))) {
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

void Timing::checkAMPM (std::string &originalStr, int count, int &num, bool &checkTime, int noOfTime) {
	std::string line = originalStr;
	std::string remainingStr = originalStr.substr(count);
	changeToLower(line);
	
	size_t foundAM = line.find("am");
	size_t foundAM2 = line.find("a.m");
	size_t foundPM = line.find("pm");
	size_t foundPM2 = line.find("p.m");
	size_t i = line.find("-");
	size_t j = line.find("to");
	checkTime = false;
	
	if (foundAM != std::string::npos && ((foundAM - count) < 2)) {
		if (count <= 2 && num == 12) {
			num = 0;
		}
		else if (count <= 2) {
			num = num * 100;
		}
		else if (num == 1200) {
			num = 0;
		}
		extractRemainingStr(originalStr, line, foundAM);
		checkTime = true;
	}
	else if (foundAM2 != std::string::npos && ((foundAM2 - count) < 2)) {
		if (count <= 2 && num == 12) {
			num = 0;
		}
		else if (count <= 2) {
			num = num * 100;
		}
		extractRemainingStr(originalStr, line, foundAM2);
		checkTime = true;
	}
	else if (foundPM != std::string::npos && ((foundPM - count) < 2)) {
		if (count <= 2) {
			num = (num * 100) + 1200;
		}
		else {
			num = num + 1200;
		}
		extractRemainingStr(originalStr, line, foundPM);
		checkTime = true;
	}
	else if (foundPM2 != std::string::npos && ((foundPM2 - count) < 2)) {
		if (count <= 2) {
			num = (num * 100) + 1200;
		}
		else {
			num = num + 1200;
		}
		extractRemainingStr(originalStr, line, foundPM2);
		checkTime = true;
	}
	//assume pm if not indicated
	else {
		if ((count > 2 && count < 4) || (num > 100 && num < 959 && count == 4)) {
			num = num + 1200;
		}
		else if (count <= 2) {
			if (i != std::string::npos || j != std::string::npos || noOfTime == 1) {
				while (remainingStr[0] == ' ') {
					remainingStr = remainingStr.substr(1);
					count++;
				}
				if ((i - count) <= 1 || (j - count) <= 1 || noOfTime == 1) {
					if (num == 12) {
						num = num * 100;
					}
					else {
						num = (num * 100) + 1200;
						checkTime = true;
					}
				}
			}
		}

		if (count != line.size()) {
			originalStr = originalStr.substr(count);
		}
		else {
			originalStr = "";
		}
	}

	if (num == 2400) {
		num = 1200;
	}
	return;
}

bool Timing::isTimeValid(int num) {
	assert(num>=0);

	if (num/100 > 23) {
		return false;
	}
	
	if (num%100 > 59) {
		return false;
	}
	return true;
}


//Count no. of words between two possible times
void Timing::countWord(std::string str, int &noOfWord) {
	size_t nextTime = str.find_first_of("0123456789");
	size_t found = str.find_first_of(",.?!");
	if (found != std::string::npos && found < nextTime) {
		return;
	}
	
	size_t found2 = str.find_first_of("-");
	if (found2 != std::string::npos && found2 < 2 && found2 < nextTime) {
		noOfWord = 1;
		return;
	}
	
	size_t index = str.find_first_of(" ");
	for (int i = _linkWord.size() - 1; i >= 0; i--) {
		size_t found = str.find(_linkWord[i]);
		if (found != std::string::npos && found <= index + 1) {
			while (index != std::string::npos && nextTime != std::string::npos) {
				if (index < nextTime) {
					noOfWord++;
					index = str.find_first_of(" ", index + 1);
					if (index != std::string::npos) {
						index = str.find_first_not_of(" ", index);
					}
				}
				else {
					return;
				}
			}
		}
	}
	return;
}

void Timing::changeToLower(std::string &str) {
	int i = 0;
	for (i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = 'a' + (str[i] - 'A');
		}
	}
	return;
}

//Cuts off 'am' and 'pm'
void Timing::extractRemainingStr(std::string &originalStr, std::string &line, size_t found) {
	size_t space = line.find_first_of(" -", found + 2);

	if (space == std::string::npos) {
		originalStr = "";
	}
	else {
		line = line.substr(space);
		originalStr = originalStr.substr(originalStr.size() - line.size());
	}
	return;
}

//Assume that the task will be adeadline task if only one time is entered
void Timing::removeNonTimeChar(std::string &str) {
	size_t found;
	found = str.find_first_of(" ");

	while (found != std::string::npos && found == 0) {
		str = str.substr(1);
		found = str.find_first_of(" ");
	}
	return;
}


void Timing::updateTime() {
	_endTime = _startTime;
	return;
}

bool Timing::checkStartEnd() {
	int eTime = _endTime;
	if (eTime == 0) {
		eTime = 2400;
	}
	if (eTime < _startTime) {
		return true;
	}
	return false;
}


int &Timing::getStart() {
	return _startTime;
}

int &Timing::getEnd() {
	return _endTime;
}