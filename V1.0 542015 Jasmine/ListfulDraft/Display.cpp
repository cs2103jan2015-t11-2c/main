#include "Display.h"

const int Display::FLOAT_SUB_SIZE = 45;
const int Display::SCHEDULE_SUB_SIZE = 32;
const int Display::DEADLINE_SUB_SIZE = 37;

bool Display::getDisplay(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	if (data.getData().empty()) {
		return false;
	}
	
	int i = 0;
	bool updateFile = false;
	
	while (i < data.getData().size() && data.getData()[i].isFloat) {
		floating << (i + 1) << ". " << getDataString(data, i, updateFile) << std::endl;
		i++;
	}
	floating << std::endl;

	while (i < data.getData().size() && data.getData()[i].isTimedTask) {
		scheduled << (i + 1) << ". " << getDataString(data, i, updateFile) << std::endl;
		i++;
	}
	scheduled << std::endl;

	while (i < data.getData().size() && !data.getData()[i].isTimedTask) {
		deadline << (i + 1) << ". " << getDataString(data, i, updateFile) << std::endl;
		i++;
	}
	return true;
}

//To get one entry
std::string Display::getDataString(DataStore &data, int index, bool updateFile) {
	std::ostringstream dataString;

	if (data.getData()[index].isFloat) {
		printSub(data, dataString, FLOAT_SUB_SIZE, index, updateFile);
	}
	else if (data.getData()[index].isTimedTask) {
		printSub(data, dataString, SCHEDULE_SUB_SIZE, index, updateFile);
		printDate(data, dataString, index);
	}
	else {
		printSub(data, dataString, DEADLINE_SUB_SIZE, index, updateFile);
		printDate(data, dataString, index);
	}

	printTime(data, dataString, index);
	printCat(data, dataString, index);
	printDone(data, dataString, index);
	return dataString.str();
}

void Display::printSub(DataStore &data, std::ostringstream &dataString, int count, int index, bool updateFile) {
	if (data.getData()[index].subject.size() > count && !updateFile) {
		std::string cutOff = data.getData()[index].subject.substr(0, count);
		dataString << cutOff << ".. | ";
	}
	else {
		dataString << data.getData()[index].subject;
		printSpace(dataString, count - data.getData()[index].subject.size());
		dataString << " | ";
	}
	return;
}

void Display::printDate(DataStore &data, std::ostringstream &dataString, int index) {
	int nDay = countDigit(data.getData()[index].day);
	int nMonth = countDigit(data.getData()[index].month);
	int nYear = countDigit(data.getData()[index].year);

	printZero(nDay, dataString, 2);
	dataString << data.getData()[index].day << '/';	
	printZero(nMonth, dataString, 2);
	dataString << data.getData()[index].month << '/' << data.getData()[index].year;
	dataString << " | ";
	return;
}

void Display::printTime(DataStore &data, std::ostringstream &dataString, int index) {
	int sTime = countDigit(data.getData()[index].startTime);
	int eTime = countDigit(data.getData()[index].endTime);

	if (data.getData()[index].isTimedTask) {
		printZero(sTime, dataString, 4);
		dataString << data.getData()[index].startTime << '-';
		printZero(eTime, dataString, 4);
		dataString << data.getData()[index].endTime;
	}
	else if (data.getData()[index].isFloat) {
		if (data.getData()[index].startTime != data.getData()[index].endTime) {
			printZero(sTime, dataString, 4);
			dataString << data.getData()[index].startTime << '-';
			printZero(eTime, dataString, 4);
			dataString << data.getData()[index].endTime;
		}
		else if (data.getData()[index].startTime != 0) {
			printZero(sTime, dataString, 4);
			dataString << data.getData()[index].startTime;
			printSpace(dataString, 5);
		}
		else {
			printSpace(dataString, 9);
		}
	}
	else if (data.getData()[index].startTime != 0) {
		printZero(sTime, dataString, 4);
		dataString << data.getData()[index].startTime;
	}
	else {
		printSpace(dataString, 4);
	}
	dataString << " | ";
	return;
}

void Display::printCat(DataStore &data, std::ostringstream &dataString, int index) {
	dataString << data.getData()[index].category << " | ";
	return;
}

void Display::printDone(DataStore &data, std::ostringstream &dataString, int index) {
	if (data.getData()[index].isComplete) {
		dataString << "yes";
	}
	else {
		dataString << "no";
	}
	return;
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
}

void Display::setColour(int value){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}