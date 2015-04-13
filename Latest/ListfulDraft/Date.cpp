//@author A0110670W
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
		return monthType::INVALIDMONTH;
	}
}

int Date::determineDay(std::string &str) {	
	if (str == "mon" || str == "monday") {
		str = "Monday";
		return dayType::MON;
	}
	else if (str == "tue" || str == "tuesday") {
		str = "Tuesday";
		return dayType::TUE;
	}
	else if (str == "wed" || str == "wednesday") {
		str = "Wednesday";
		return dayType::WED;
	}
	else if (str == "thur" || str == "thursday") {
		str = "Thursday";
		return dayType::THUR;
	}
	else if (str == "fri" || str == "friday") {
		str = "Friday";
		return dayType::FRI;
	}
	else if (str == "sun" || str == "sunday") {
		str = "Sunday";
		return dayType::SUN;
	}
	else if (str == "sat" || str == "saturday") {
		str = "Saturday";
		return dayType::SAT;
	}
	else {
		return dayType::INVALIDDAY;
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
	found = str.find_first_of(" ");

	while (found != std::string::npos && found == 0) {
		str = str.substr(1);
		found = str.find_first_of(" ");
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

bool Date::retrieveDayIfNext(std::string &dateDayWord, size_t end, std::string str) {
	if (dateDayWord == "next") {
		if (end != std::string::npos) {
			dateDayWord = str.substr(end + 1);
			end = dateDayWord.find_first_of(" ");
			if (end != std::string::npos) {
				dateDayWord = dateDayWord.substr(0, end);
			}
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

bool Date::getDayOfWeek(std::string dateDayWord, tm now, int count) {
	changeToLower(dateDayWord);
	int dayWord = determineDay(dateDayWord);
	int i = 0;
	struct tm *timeInfo;
	const char *weekday[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	timeInfo = &now;

	if (dayWord != dayType::INVALIDDAY) {
		for (;;) {
			mktime(timeInfo);
			if (weekday[timeInfo->tm_wday] == dateDayWord) {
				if (count == 1 && i > 7) {
					break;
				}
				else if (count == 0) {
					break;
				}
			}
			timeInfo->tm_mday = timeInfo->tm_mday + 1;
			i++;
		}
		_day = timeInfo->tm_mday;
		_month = timeInfo->tm_mon + 1;
		_year = timeInfo->tm_year + 1900;
		return true;
	} 
	return false;
}

bool Date::getTdyTmr(std::string dateWord,tm now, bool &pastDate) {
	changeToLower(dateWord);
	if (dateWord == "today" || dateWord == "tdy" || dateWord == "tday" || dateWord == "later" || dateWord == "tonight") {
		_day = (now.tm_mday);
	}
	else if (dateWord == "tomorrow" || dateWord == "tmr" || dateWord == "tomoro" || dateWord == "tmrw") {
		_day = (now.tm_mday) + 1;
	}
	else {
		return false;
	}
	_month = (now.tm_mon + 1);
	_year = (now.tm_year + 1900);

	if (!isValidDate(pastDate)) {
		_day = 1;
		_month++;
	}
	return true;
}

bool Date::dateInLetter(std::string &str) {
	size_t end = str.find_first_of(" ");
	std::string dateDayWord = "";
	int count = 0;
	bool pastDate = false;
	time_t t = time(0);   
	struct tm now;
	localtime_s(&now, &t);

	if (end == std::string::npos) {
		dateDayWord = str;
	}
	else {
		dateDayWord = str.substr(0, end);
	}	

	//Exception for sat and wed and sun
	if (dateDayWord == "sat" || dateDayWord == "sun" || dateDayWord == "wed") {
		return false;
	}

	//If current word is 'next' get the next word to check for day of the week
	if (retrieveDayIfNext(dateDayWord, end, str)) {
		count++;
	}
	
	if (getDayOfWeek(dateDayWord, now, count)) {
		if (count == 1) {
			str = str.substr(end + 1);
			end = str.find_first_of(" ");
		}
	}
	else if (!getTdyTmr(dateDayWord, now, pastDate)) {
		return false;
	}

	if (end == std::string::npos) {
		str = "";
	}
	else {
		str = str.substr(end + 1);
	}
	return true;
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
	if (start != std::string::npos && start == 1 && tStr[0] == '/') {
		tStr = tStr.substr(1);
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
	size_t index = originalStr.find_first_of(" ", (originalStr.find(newStr) + 5));
	
	Timing timer;
	time_t t = time(0);   
	struct tm now;
	localtime_s(&now, &t);

	//Cut off DD/MM
	tStr = newStr;

	if (!extractNum(newStr, count, _year)) {
		_year = (now.tm_year + 1900);
		return;
	}
	else if (originalStr[originalStr.find(newStr) - 1] == '/') {
		if (count == newStr.size()) {
			tStr = "";
		}
		else if (count == 2 || count == 4) {
			tStr = newStr.substr(count);
			if (count == 2) {
				_year = _year + 2000;
			}
		}
		return;
	}
	else if (count != 4) {
		_year = (now.tm_year + 1900);
		return;
	}
	//Listful can only accept tasks up to 50 years in the redo and 10 years back
	else if (_year < (now.tm_year + 1890) || _year > (now.tm_year + 1950)) {
		_year = (now.tm_year + 1900);
		return;
	}
	else if (_year >= (now.tm_year + 1900) && _year <= (now.tm_year + 1900) + 5) {
		if (count == newStr.size()) {
			tStr = "";
		}
		else {
			tStr = newStr.substr(count);
		}
		return;
	}
	else {
		if (index != std::string::npos) {
			std::string findTime = originalStr.substr((originalStr.find(newStr) + 4), index - (originalStr.find(newStr) + 4));
			changeToLower(findTime);
			removeNonDateChar(findTime);
			if (findTime[0] == '-' || findTime == "to" ||  findTime == "am" || findTime == "pm" || findTime == "a.m" || findTime == "p.m" || findTime == "a.m." || findTime == "p.m.") {
				_year = (now.tm_year + 1900);
				return;
			}
		}

		//To check if the number after the month is a year or a time
		timer.removeNonTimeChar(str);
		if (timer.checkForTime(str, noOfTime, checkTime)) {
			index = 0;
			//If any time is found before this '_year' then _year is a real year
			str = originalStr.substr(0, originalStr.find_last_of(" ", start));
			while (index != std::string::npos && index < start) {
				noOfTime = 0;
				index = str.find_first_of(" ", index);
				if (index != std::string::npos) {
					index = str.find_first_not_of(" ", index);
					str = str.substr(index);
				}
				if (timer.checkForTime(str, noOfTime, checkTime)) {
					if (count == newStr.size()) {
						tStr = "";
					}
					else {
						tStr = newStr.substr(count);
					}
					return;
				}
			}
				
			index = 0;
			//If a timed task timing is found after the year then _year is a real year
			if (count != newStr.size()) {
				str = newStr.substr(count);
				timer.removeNonTimeChar(str);
				while (index != std::string::npos) {
					noOfTime = 0;
					index = str.find_first_of(" ", index);
					if (index != std::string::npos) {
						index = str.find_first_not_of(" ", index);
						str = str.substr(index);
					}
					if (timer.checkForTime(str, noOfTime, checkTime)) {
						tStr = newStr.substr(count);
						return;
					}
				}
			}
		}
	}
	return;
}

//To invalidate dates like the 32th dec
bool Date::isValidDate(bool &pastDate) {
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
		if (_year < (now.tm_year + 1900)) {
			pastDate = true;
		}
		else if (_year == (now.tm_year + 1900) && _month < (now.tm_mon + 1)) {
			pastDate = true;
		}
		else if (_year == (now.tm_year + 1900) && _month == (now.tm_mon + 1) && _day < (now.tm_mday)) {
			pastDate = true;
		}
	}
	return true;
}

//To identify if the current first word of the string is a date
bool Date::checkForDate(std::string &tStr, bool &pastDate, std::string originalStr, size_t index, bool getNewDate) {
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
		else {
			newStr = newStr.substr(start);
			removeNonDateChar(newStr);
			if (newStr != "" && newStr[0] == '/') {
				newStr = newStr.substr(1);
			}
			takeYear(tStr, newStr, originalStr, index);
		}
	}
	//MM/DD
	else if (takeMonth (tStr, start, end)) {
		newStr = tStr.substr(start);
		removeNonDateChar(newStr);
		if (!takeDay(newStr, start)) {
			return false;
		}
		else {
			newStr = newStr.substr(start);
			removeNonDateChar(newStr);
			if (newStr != "" && newStr[0] == '/') {
				newStr = newStr.substr(1);
			}
			takeYear(tStr, newStr, originalStr, index);
		}
	}
	else if (dateInLetter(tStr)) {
		return true;
	}
	else {
		return false;
	}
	//If user is entering a date but it is wrong due to typo
	if (!isValidDate(pastDate) && !getNewDate) {
		std::cout << " possible date [ " << _day << '/' << _month << " ] entered but invalid\n\n new date?\n\n ";
		getline(std::cin, newDate);
		getNewDate = true;
		if (newDate == "") {
			return	false;
		}
		return checkForDate(newDate, pastDate, originalStr, index, getNewDate);
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