#include "Date.h"

int Date::determineMonth(std::string str) {	
	if (str == "jan" || str == "january") {
		return monthType::JAN;
	}
	else if (str == "feb" || str == "february") {
		return monthType::FEB;
	}
	else if (str == "mar" || str == "march") {
		return monthType::MAR;
	}
	else if (str == "apr" || str == "april") {
		return monthType::APR;
	}
	else if (str == "may") {
		return monthType::MAY;
	}
	else if (str == "jun" || str == "june") {
		return monthType::JUN;
	}
	else if (str == "jul" || str == "july") {
		return monthType::JUL;
	}
	else if (str == "aug" || str == "august") {
		return monthType::AUG;
	}
	else if (str == "sep" || str == "sepptember") {
		return monthType::SEP;
	}
	else if (str == "oct" || str == "october") {
		return monthType::OCT;
	}
	else if (str == "nov" || str == "november") {
		return monthType::NOV;
	}
	else if (str == "dec" || str == "december") {
		return monthType::DEC;
	}
	else {
		return monthType::INVALID;
	}
}

//To return possible time values only
bool Date::extractNum(std::string tStr, size_t &start, size_t &end, int &count, int &num) {
	while (end != std::string::npos && (tStr[end] >= '0' && tStr[end] <= '9')) {
		if (end == (start + count)) {
			num = (num * 10) + (tStr[end] - '0');
			count++;
		}
		end = tStr.find_first_of("0123456789", end + 1);
	}
	if (count <= 4 && num != 0) {
		return true;
	}
	return false;
}

void Date::removeNonDateChar(std::string &str) {
	size_t found;
	found = str.find_first_of(" /.-");

	while (found != std::string::npos && found == 0) {
		str = str.substr(1);
		found = str.find_first_of(" /.-");
	}
	return;
}

//To identify a potential day
bool Date::takeDay(std::string &tStr, size_t &start, size_t &end) {
	int count = 0;
	start = 0;
	end = 0;

	if (!extractNum(tStr, start, end, count, _day)) {
		return false;
	}
	else {
		if (count > 2) {
			return false;
		}
		start = count;
		return true;
	}
}

//To identify a potential month
bool Date::takeMonth(std::string &tStr, size_t &start, size_t &end) {
	int count = 0;
	std::string str;
	start = tStr.find_first_of("0123456789", 0);
	
	//If month is in numbers
	if (start != std::string::npos && start == 0) {
		end = start;
		if (!extractNum(tStr, start, end, count, _month)) {
			return false;
		}
		else if (count > 2) {
			return false;
		}
		end = count - 1;
	}
	//If month is in words
	else {
		end = tStr.find_first_of(" /.-1234567890");
		if (end == std::string::npos) {
			end = tStr.size();
		}
		str = tStr.substr(0, end);
		changeToLower(str);
		_month = determineMonth(str);
		if (_month == 13) {
			return false;
		}
	}
	start = end;
	return true;
}

//To identify if any year entered, else default year will be the current year
void Date::takeYear(std::string &tStr, std::string &newStr) {
	int i = 0;
	int count = 0;
	size_t index1 = 0;
	size_t index2 = 0;
	
	if (!extractNum(newStr, index1, index2, count, _year) || count != 4) {
		_year = 2015;
		tStr = newStr;
		return;
	}

	//add in the condition that you cannot add a year less than the current year
	newStr = newStr.substr(count);
	tStr = newStr;
	return;
}

//To invalidate dates like the 32th dec
bool Date::isDayMonth() {
	if (_month > 12) {
		return false;
	}
	else if (_month == 2 && _day > 29) {
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

//To identify if the current first word of the string is a date
bool Date::extractDate(std::string &tStr) {
	_day = 0;
	_month = 0;
	_year = 0;
	std::string newStr = "";
	std::string newDate = "";
	size_t start = 0;
	size_t end = 0;

	//DD/MM
	if (takeDay(tStr, start, end)) {
		newStr = tStr.substr(start);
		removeNonDateChar(newStr);
		if (!takeMonth(newStr, start, end)) {
			return false;
		}
	}
	//MM/DD
	else if (takeMonth (tStr, start, end)) {
		newStr = tStr.substr(start);
		removeNonDateChar(newStr);
		if (!takeDay(newStr, start, end)) {
			return false;
		}
	}
	else {
		return false;
	}

	newStr = newStr.substr(start);
	removeNonDateChar(newStr);
	takeYear(tStr, newStr);
	
	//If user is entering a date but it is wrong due to typo
	if (!isDayMonth()) {
		std::cout << "invalid date entered, please re-enter date: ";
		getline(std::cin, newDate);
		if (newDate == "") {
			return	false;
		}
		while (!extractDate(newDate)) {
			std::cout << "invalid date entered, please re-enter date: ";
			getline(std::cin, newDate);
			return extractDate(newDate);
		}
	}
	return true;
}

//To make entering the month not case-sensitive
void Date::changeToLower(std::string &str) {
	int i;
	for (i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = 'a' + (str[i] - 'A');	
		}
	}
	return;
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