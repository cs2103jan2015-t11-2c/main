#include "Date.h"
#include "Timing.h"

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
	else if (str == "sep" || str == "september") {
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

void Date::removeNonDateChar(std::string &str) {
	size_t found;
	found = str.find_first_of(" /");

	while (found != std::string::npos && found == 0) {
		str = str.substr(1);
		found = str.find_first_of(" /");
	}
	return;
}

//To return possible date values only
bool Date::extractNum(std::string tStr, int &count, int &num) {
	size_t end = 0;
	while (end != std::string::npos && (tStr[end] >= '0' && tStr[end] <= '9')) {
		if (end == count) {
			num = (num * 10) + (tStr[end] - '0');
			count++;
		}
		else {
			break;
		}
		if ((end + 1) == tStr.size()) {
			end = std::string::npos;
		}
		else {
			end = tStr.find_first_of("0123456789", end + 1);
		}
		
	}

	if (count <= 4 && num != 0) {
		return true;
	}
	return false;
}

//To take into acc for 1st 2nd 3rd 12th etc
void Date::removeExtraLetters(std::string str, int &count) {
	changeToLower(str);
	size_t i = str.find("th", count);
	size_t j = str.find("st", count);
	size_t k = str.find("nd", count);
	size_t l = str.find("rd", count);
	if (i != std::string::npos || j != std::string::npos || k != std::string::npos || l != std::string::npos) {
		if (i == count || j == count || k == count || l == count) {
			count = count + 2;
		}
	}
	return;
}

//To identify a potential day
bool Date::takeDay(std::string &tStr, size_t &start) {
	int count = 0;

	if (!extractNum(tStr, count, _day)) {
		return false;
	}
	else {
		if (count > 2) {
			return false;
		}
		removeExtraLetters(tStr, count);
		start = count;
		return true;
	}
}

//To identify a potential month
bool Date::takeMonth(std::string &tStr, size_t &start, size_t &end) {
	int count = 0;
	std::string str = "";
	start = tStr.find_first_of("0123456789");

	//If month is in numbers
	if (start != std::string::npos && start == 0) {
		if (!extractNum(tStr, count, _month)) {
			return false;
		}
		else if (count > 2) {
			return false;
		}
		end = count;
	}
	//If month is in words
	else {
		end = tStr.find_first_of(" 1234567890");
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
void Date::takeYear(std::string &tStr, std::string newStr, std::string originalStr, size_t start) {
	int noOfTime = 0;
	std::string str = newStr;
	int count = 0;
	bool checkTime = false;
	size_t index = 0;
	
	Timing timer;
	time_t t = time(0);   
	struct tm now;
	localtime_s(&now, &t);

	//Cut off DD/MM
	tStr = newStr;

	if (!extractNum(newStr, count, _year) || count != 4) {
		_year = (now.tm_year + 1900);
		return;
	}
	//Listful can only accept tasks up to 50 years in the future and 10 years back
	else if (_year < (now.tm_year + 1890) || _year > (now.tm_year + 1950)) {
		_year = (now.tm_year + 1900);
		return;
	}
	//To check if the number after the month is a year or a time
	else {
		timer.removeNonTimeChar(str);
		//If _year is a potential time
		if (timer.extractTime(str, noOfTime, checkTime)) {
			//If a timed task timing or 1000am is found at the current '_year', then _year is not a real year
			if (noOfTime == 2 || checkTime) {
				_year = (now.tm_year + 1900);
				return;
			}
			else {
				//If any time is found before this '_year' then _year is a real year
				str = originalStr.substr(0, originalStr.find_last_of(" ", start));
				while (index != std::string::npos && index < start) {
					noOfTime = 0;
					index = str.find_first_of(" ", index);
					index = str.find_first_not_of(" ", index);
					str = str.substr(index);
					if (timer.extractTime(str, noOfTime, checkTime)) {
						if (count == newStr.size()) {
							tStr = "";
						}
						else {
							tStr = newStr.substr(count);
						}
						return;
					}
				}

				//If a timed task timing is found after the year then _year is a real year
				if (count != newStr.size()) {
					str = newStr;
					str = str.substr(count);
					timer.removeNonTimeChar(str);
					while (index != std::string::npos) {
						noOfTime = 0;
						index = str.find_first_of(" ", index);
						index = str.find_first_not_of(" ", index);
						str = str.substr(index);
						if (timer.extractTime(str, noOfTime, checkTime)) {
							tStr = newStr.substr(count);
							return;
						}
					}
				}
			}
		}
	}
	return;
}

//To invalidate dates like the 32th dec
bool Date::isDayMonth(bool &pastDate) {
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
	else {
		//Get current date
		time_t t = time(0);   
		struct tm now;
		localtime_s(&now, &t);
		std::cout << (now.tm_year + 1900) << "-" << (now.tm_mon + 1) << "-" << (now.tm_mday) << std::endl;
		if (_year < (now.tm_year + 1900)) {
			pastDate = true;
		}
		else if (_month < (now.tm_mon + 1)) {
			pastDate = true;
		}
		else if (_day < (now.tm_mday)) {
			pastDate = true;
		}
	}
	return true;
}

//To identify if the current first word of the string is a date
bool Date::extractDate(std::string &tStr, bool &pastDate, std::string originalStr, size_t index) {
	_day = 0;
	_month = 0;
	_year = 0;
	std::string newStr = "";
	std::string newDate = "";
	size_t start = 0;
	size_t end = 0;
	pastDate = false;

	//DD/MM
	if (takeDay(tStr, start)) {
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
		if (!takeDay(newStr, start)) {
			return false;
		}
	}
	else {
		return false;
	}
	newStr = newStr.substr(start);
	removeNonDateChar(newStr);
	takeYear(tStr, newStr, originalStr, index);

	//If user is entering a date but it is wrong due to typo
	if (!isDayMonth(pastDate)) {
		std::cout << "invalid date entered, please re-enter date: ";
		getline(std::cin, newDate);
		if (newDate == "") {
			return false;
		}
		while (!extractDate(newDate, pastDate, originalStr, index)) {
			std::cout << "invalid date entered, please re-enter date: ";
			getline(std::cin, newDate);
			return extractDate(newDate, pastDate, originalStr, index);
		}
	}
	return true;
}

int &Date::getDay() {
	return _day;
}

int &Date::getMonth() {
	return _month;
}

int &Date::getYear() {
	return _year;
}