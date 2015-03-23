#include "Date.h"

int Date::determineMonth(std::string str) {
	size_t found;
	
	if (str == "jan") {
		return monthType::JAN;
	}
	else if (str == "feb") {
		return monthType::FEB;
	}
	else if (str == "mar") {
		return monthType::MAR;
	}
	else if (str == "apr") {
		return monthType::APR;
	}
	else if (str == "may") {
		return monthType::MAY;
	}
	else if (str == "jun") {
		return monthType::JUN;
	}
	else if (str == "jul") {
		return monthType::JUL;
	}
	else if (str == "aug") {
		return monthType::AUG;
	}
	else if (str == "sep") {
		return monthType::SEP;
	}
	else if (str == "oct") {
		return monthType::OCT;
	}
	else if (str == "nov") {
		return monthType::NOV;
	}
	else if (str == "dec") {
		return monthType::DEC;
	}
	else {
		return monthType::INVALID;
	}
}

bool Date::extractNum(std::string &tStr, size_t &start, size_t &end, int &count, int &num) {
	while (tStr[end] >= '0' && tStr[end] <= '9' && end != std::string::npos) {
		if (end == (start + count)) {
			num = (num * 10) + (tStr[end] - '0');
			count++;
			end = tStr.find_first_of("0123456789", end + 1);

			if (end == std::string::npos) {
				return true;
			}
		}
	}
	if (num != 0) {
		return true;
	}
	return false;
}

void Date::removeNonDateChar(std::string &str) {
	size_t found;
	found = str.find_first_of(" /.-");

	while (found != std::string::npos && found == 0) {
		str = str.substr(1, str.size() - 1);
		found = str.find_first_of(" /.-");
	}
}

bool Date::isDay(std::string &tStr, size_t &start, size_t &end) {
	int count = 0;

	if (!extractNum(tStr, start, end, count, _day)) {
		return false;
	}
	else {
		start = count;
		if (_day > 31 || count == 0) {
			return false;
		}
		return true;
	}
}

bool Date::isMonth(std::string &tStr, size_t &start, size_t &end) {
	int count = 0;
	std::string str;
	removeNonDateChar(tStr);
	start = tStr.find_first_of("0123456789", 0);
	
	//If month is in numbers
	if (start != std::string::npos && start == 0) {
		end = start;
		if (!extractNum(tStr, start, end, count, _month)) {
			return false;
		}
		end = count;
	}
	//If month is in words
	else {
		start = 0;
		str = tStr.substr(start, 3);
		changeToLower(str);
		_month = determineMonth(str);
		end = tStr.find_first_of(" /.-123456789", start + 1);
		if (end == std::string::npos) {
			end = tStr.size();
		}
	}

	if (_month > 12) {
		return false;
	}
	start = end;
	return true;
}

//To invalidate dates like the 32th dec
bool Date::isDayMonth() {
	if (_month == 2 && _day > 29) {
		return false;
	}	
	else if ((_month < 8 && _month%2 == 1) || (_month > 7 && _month%2 == 0)) {
		if (_day > 31) {
			return false;
		}
	}
	else if (_day > 30) {
			return false;
	}
	return true;
}

void Date::isYear(std::string &tStr, std::string &newStr) {
	int i;
	int count = 0;
	size_t index1 = 0;
	size_t index2 = 0;
	
	if (!extractNum(newStr, index1, index2, count, _year)) {
		_year = 2015;
		tStr = newStr;
		return;
	}

	//add in the condition that you cannot add a year less than the current year
	if (count != 4) {
		
			std::cout << "hello" << std::endl;
		_year = 2015;
		tStr = newStr;
		return;
	}
	newStr = newStr.substr(count, newStr.size() - count);
	tStr = newStr;
}

bool Date::extractDate(std::string &tStr) {
	_day = 0;
	_month = 0;
	_year = 0;
	std::string newStr;
	size_t start = 0;
	size_t end = 0;
	
	//DD/MM
	if (isDay(tStr, start, end)) {
		newStr = tStr.substr(start, tStr.size() - start);
		removeNonDateChar(newStr);
		if (!isMonth(newStr, start, end)) {
			return false;
		}
	}
	//MM/DD
	else if (isMonth (tStr, start, end)) {
		newStr = tStr.substr(end, tStr.size() - end);
		removeNonDateChar(newStr);
		if (!isDay(tStr, start, end)) {
			return false;
		}
	}
	else {
		return false;
	}
	
	if (!isDayMonth()) {
		return false;
	}
	
	newStr = newStr.substr(start, newStr.size() - start);
	removeNonDateChar(newStr);
	isYear(tStr, newStr);

	return true;
}

void Date::changeToLower(std::string &str) {
	int i;
	for (i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = 'a' + (str[i] - 'A');	
		}
	}
}

int Date::getDay() {
	return _day;
}

int Date::getMonth() {
	return _month;
}

int Date::getYear() {
	return _year;
}