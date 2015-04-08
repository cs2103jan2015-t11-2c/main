#include "Display.h"

const int Display::FLOAT_SUB_SIZE = 44;
const int Display::NON_FLOAT_SUB_SIZE = 31;

void Display::getToday(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	time_t t = time(0);   
	struct tm now;
	localtime_s(&now, &t);
	int i = 0;
	int j = 0;
	bool updateFile = false;

	while (i < data.getData().size() && data.getTempData()[i].isFloat) {
		if (data.getData()[i].day == (now.tm_mday) && data.getData()[i].month == (now.tm_mon + 1) && data.getData()[i].year == (now.tm_year + 1900)) {
			floating << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
			j++;
		}
		i++;
	}

	while (i < data.getTempData().size() && data.getTempData()[i].isTimedTask) {
		if (data.getData()[i].day == (now.tm_mday) && data.getData()[i].month == (now.tm_mon + 1) && data.getData()[i].year == (now.tm_year + 1900)) {
			scheduled << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
			j++;
		}
		i++;
	}

	while (i < data.getTempData().size() && !data.getTempData()[i].isTimedTask) {
		if (data.getData()[i].day == (now.tm_mday) && data.getData()[i].month == (now.tm_mon + 1) && data.getData()[i].year == (now.tm_year + 1900)) {
			deadline << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
			j++;
		}
		i++;
	}
	return;
}

void Display::getChange(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	int i = 0;
	int j = 0;
	bool updateFile = false;
	int day = data.get_tempEntry().day;
	int month = data.get_tempEntry().month;
	int year = data.get_tempEntry().year;
	
	while (i < data.getData().size()) {
		if (data.getData()[i].isFloat && data.get_tempEntry().isFloat && !data.getData()[i].isTimedTask  && !data.get_tempEntry().isTimedTask) {
			floating << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
			j++;
		}
		else if (data.getData()[i].isTimedTask && data.get_tempEntry().isTimedTask && !data.getData()[i].isFloat && !data.get_tempEntry().isFloat) {
			if (data.getData()[i].day == day && data.getData()[i].month == month && data.getData()[i].year == year) {
				scheduled << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				j++;
			}
		}
		else if (!data.getData()[i].isTimedTask && !data.get_tempEntry().isTimedTask && !data.getData()[i].isFloat && !data.get_tempEntry().isFloat) {
			if (data.getData()[i].day == day && data.getData()[i].month == month && data.getData()[i].year == year) {
				deadline << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				j++;
			}
		}
		i++;
	}
	return;
}

std::string Display::getDate(DataStore &data, int index, bool isTemp) {
	std::ostringstream dataString;
	printDate(data, dataString, index, isTemp);
	return dataString.str();
}

std::string Display::getTime(DataStore &data, int index, bool isTemp) {
	std::ostringstream dataString;
	printTime(data, dataString, index, isTemp);
	return dataString.str();
}

std::string Display::getTempDataString(DataStore &data, int index, bool updateFile, int index2) {
	std::ostringstream dataString;
	bool isTemp = true;

	if (data.getTempData()[index].isFloat) {
		if  ((index2 < 0 && (index + 1) > 9) || ((index2) + 1 > 9)) {
			printSub(data, dataString, FLOAT_SUB_SIZE - 1, index, updateFile, isTemp);
		}
		else {
			printSub(data, dataString, FLOAT_SUB_SIZE, index, updateFile, isTemp);
		}
	}
	else {
		if ((index2 < 0 && (index + 1) > 9) || ((index2) + 1 > 9)) {
			printSub(data, dataString, NON_FLOAT_SUB_SIZE - 1, index, updateFile, isTemp);
		}
		else {
			printSub(data, dataString, NON_FLOAT_SUB_SIZE, index, updateFile, isTemp);
		}
		dataString << " | ";
		printDate(data, dataString, index, isTemp);
	}
	dataString << " | ";
	printTime(data, dataString, index, isTemp);
	dataString << " | ";
	printCat(data, dataString, index, isTemp);
	dataString << " | ";
	printDone(data, dataString, index, isTemp);
	return dataString.str();
}

void Display::getTempDisplay(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	int i = 0;
	bool updateFile = false;
	
	while (i < data.getTempData().size() && data.getTempData()[i].isFloat) {
		floating << " " << (i + 1) << ". " << getTempDataString(data, i, updateFile) << std::endl;
		i++;
	}

	while (i < data.getTempData().size() && data.getTempData()[i].isTimedTask) {
		scheduled << " " << (i + 1) << ". " << getTempDataString(data, i, updateFile) << std::endl;
		i++;
	}

	while (i < data.getTempData().size() && !data.getTempData()[i].isTimedTask) {
		deadline << " " << (i + 1) << ". " << getTempDataString(data, i, updateFile) << std::endl;
		i++;
	}
	return;
}

void Display::getReminder(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	int i = 0;
	int j = 0;
	bool updateFile = false;
	time_t t = time(0);   
	struct tm now;
	localtime_s(&now, &t);
	
	while (i < data.getData().size() && data.getData()[i].isFloat) {
		if (data.getData()[i].year == (now.tm_year + 1900) && data.getData()[i].month == (now.tm_mon + 1) && (data.getData()[i].day - (now.tm_mday) < 3)) {
			floating << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
			j++;
		}
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask) {
		if (data.getData()[i].year == (now.tm_year + 1900) && data.getData()[i].month == (now.tm_mon + 1) && (data.getData()[i].day - (now.tm_mday) < 3)) {
			scheduled << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
			j++;
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask) {
		if (data.getData()[i].year == (now.tm_year + 1900) && data.getData()[i].month == (now.tm_mon + 1) && (data.getData()[i].day - (now.tm_mday) < 3)) {
			deadline << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
			j++;
		}
		i++;
	}
	return;
}

bool Display::getDisplay(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	if (data.getData().empty()) {
		return false;
	}
	
	int i = 0;
	bool updateFile = false;
	
	while (i < data.getData().size() && data.getData()[i].isFloat) {
		floating << " " << (i + 1) << ". " << getDataString(data, i, updateFile) << std::endl;
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask) {
		scheduled << " " << (i + 1) << ". " << getDataString(data, i, updateFile) << std::endl;
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask) {
		deadline << " " << (i + 1) << ". " << getDataString(data, i, updateFile) << std::endl;
		i++;
	}
	return true;
}

std::string Display::getDataString(DataStore &data, int index, bool updateFile, int index2) {
	std::ostringstream dataString;
	bool isTemp = false;

	if (data.getData()[index].isFloat) {
		if ((index2 < 0 && (index + 1) > 9) || ((index2) + 1 > 9)) {
			printSub(data, dataString, FLOAT_SUB_SIZE - 1, index, updateFile, isTemp);
		}
		else {
			printSub(data, dataString, FLOAT_SUB_SIZE, index, updateFile, isTemp);
		}
	}
	else {
		if ((index2 < 0 && (index + 1) > 9) || ((index2) + 1 > 9)) {
			printSub(data, dataString, NON_FLOAT_SUB_SIZE - 1, index, updateFile, isTemp);
		}
		else {
			printSub(data, dataString, NON_FLOAT_SUB_SIZE, index, updateFile, isTemp);
		}
		dataString << " | ";
		printDate(data, dataString, index, isTemp);
	}
	dataString << " | ";
	printTime(data, dataString, index, isTemp);
	dataString << " | ";
	printCat(data, dataString, index, isTemp);
	dataString << " | ";
	printDone(data, dataString, index, isTemp);
	return dataString.str();
}

void Display::printSub(DataStore &data, std::ostringstream &dataString, int count, int index, bool updateFile, bool isTemp) {
	if (!isTemp) {
		if (data.getData()[index].subject.size() > count && !updateFile) {
			std::string cutOff = data.getData()[index].subject.substr(0, count - 2);
			dataString << cutOff << "..";
		}
		else {
			dataString << data.getData()[index].subject;
			printSpace(dataString, count - data.getData()[index].subject.size());
		}
	}
	else {
		if (data.getTempData()[index].subject.size() > count && !updateFile) {
			std::string cutOff = data.getTempData()[index].subject.substr(0, count - 2);
			dataString << cutOff << "..";
		}
		else {
			dataString << data.getTempData()[index].subject;
			printSpace(dataString, count - data.getTempData()[index].subject.size());
		}
	}
	return;
}

void Display::printDate(DataStore &data, std::ostringstream &dataString, int index, bool isTemp) {
	if (!isTemp) {
		int nDay = countDigit(data.getData()[index].day);
		int nMonth = countDigit(data.getData()[index].month);
		int nYear = countDigit(data.getData()[index].year);

		printZero(nDay, dataString, 2);
		dataString << data.getData()[index].day << '/';	
		printZero(nMonth, dataString, 2);
		dataString << data.getData()[index].month << '/' << data.getData()[index].year;
	}
	else {
		int nDay = countDigit(data.getTempData()[index].day);
		int nMonth = countDigit(data.getTempData()[index].month);
		int nYear = countDigit(data.getTempData()[index].year);

		printZero(nDay, dataString, 2);
		dataString << data.getTempData()[index].day << '/';	
		printZero(nMonth, dataString, 2);
		dataString << data.getTempData()[index].month << '/' << data.getTempData()[index].year;
	}
	return;
}

void Display::printTime(DataStore &data, std::ostringstream &dataString, int index, bool isTemp) {
	if (!isTemp) {
		int sTime = countDigit(data.getData()[index].startTime);
		int eTime = countDigit(data.getData()[index].endTime);

		if (data.getData()[index].startTime == 0 && (data.getData()[index].startTime == data.getData()[index].endTime)) {
			printSpace(dataString, 9);
		}
		else if (data.getData()[index].startTime == data.getData()[index].endTime) {
			printZero(sTime, dataString, 4);
			dataString << data.getData()[index].startTime;
			printSpace(dataString, 5);
		}
		else {
			printZero(sTime, dataString, 4);
			dataString << data.getData()[index].startTime << '-';
			printZero(eTime, dataString, 4);
			dataString << data.getData()[index].endTime;
		}
	}
	else {
		int sTime = countDigit(data.getTempData()[index].startTime);
		int eTime = countDigit(data.getTempData()[index].endTime);

		if (data.getTempData()[index].startTime == 0 && (data.getTempData()[index].startTime == data.getTempData()[index].endTime)) {
			printSpace(dataString, 9);
		}
		else if (data.getTempData()[index].startTime == data.getTempData()[index].endTime) {
			printZero(sTime, dataString, 4);
			dataString << data.getTempData()[index].startTime;
			printSpace(dataString, 5);
		}
		else {
			printZero(sTime, dataString, 4);
			dataString << data.getTempData()[index].startTime << '-';
			printZero(eTime, dataString, 4);
			dataString << data.getTempData()[index].endTime;
		}
	}
	return;
}

void Display::printCat(DataStore &data, std::ostringstream &dataString, int index, bool isTemp) {
	if (!isTemp) {
		dataString << data.getData()[index].category;
	}
	else {
		dataString << data.getTempData()[index].category;
	}
	return;
}

void Display::printDone(DataStore &data, std::ostringstream &dataString, int index, bool isTemp) {
	if (!isTemp) {
		if (data.getData()[index].isComplete) {
			dataString << "yes";
		}
		else {
			dataString << "no";
		}
		return;
	}
	else {
		if (data.getTempData()[index].isComplete) {
			dataString << "yes";
		}
		else {
			dataString << "no";
		}
		return;
	}
}

int Display::countDigit(int num) {
	int count = 0;
	
	if (num == 0) {
		return 1;
	}

	while (num > 0) {
		count++;
		num = num/10;
	}
	return count;
}

//To ensure that the no of digits for time and date are 4 and 2 respectively
void Display::printZero(int num, std::ostringstream &dataString, int count) {
	while (num < count) {
		dataString << '0';
		num++;
	}
	return;
}

//To equalize the columns of each output entry
void Display::printSpace(std::ostringstream &dataString, int count) {
	while (count > 0) {
		dataString << " ";
		count--;
	}
	return;
}

void Display::setColour(int value){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}