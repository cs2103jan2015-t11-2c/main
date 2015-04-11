#include "Display.h"

const int Display::FLOAT_SUB_SIZE = 44;
const int Display::NON_FLOAT_SUB_SIZE = 31;

void Display::updateDisplayData(DataStore &data, int i) {
	data.getTempData().push_back(data.getData()[i]);
	data.getTempIndexList().push_back(i);
}

bool Display::displayContent(DataStore &data, std::string info, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	if (info == "today" || info == "tdy" || info == "tday" || info == "later" || info == "tonight") {
		getToday(data, floating, scheduled, deadline);
	}
	else if (info == "tomorrow" || info == "tmr" || info == "tomoro" || info == "tmrw") {
		getTmr(data, floating, scheduled, deadline);
	}
	else if (info == "over" || info == "overdue" || info == "past" || info == "yesterday") {
		getOverDue(data, floating, scheduled, deadline);
	}
	else if (info == "done" || info == "complete" || info == "completed" || info == "finished" || info == "finish") {
		getComplete(data, floating, scheduled, deadline);
	}
	else if (info == "remind" || info == "reminder" || info == "due") {
		getReminder(data, floating, scheduled, deadline);
	}
	else if (info == "float" || info == "to do") {
		getFloat(data, floating);
	}
	else if (info == "scheduled" || info == "schedule" || info == "time table" || info == "plan") {
		getScheduled(data, scheduled);
	}
	else if (info == "due" || info == "to do") {
		getDeadline(data, deadline);
	}
	else if (info == "all") {
		return getDisplay(data, errMsg, floating, scheduled, deadline);
	}

	if (floating != "" || scheduled != "" || deadline != "") {
		return true;
	}
	return false;
}

void Display::getEntry(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	int i = 0;
	bool updateFile = false;
	data.getTempIndexList().clear();
	data.getTempData().clear();
	
	while (i < data.getData().size()) {
		if (data.getData()[i].referenceNo == data.get_tempEntry().referenceNo) {
			if (data.getData()[i].isFloat) {
				floating << " 1. " << getDataString(data, i, updateFile) << std::endl;
				updateDisplayData(data, i);
				return;
			}
			else if (data.getData()[i].isTimedTask) {
				scheduled << " 1. " << getDataString(data, i, updateFile) << std::endl;
				updateDisplayData(data, i);
				return;
			}
			else {
				deadline << " 1. " << getDataString(data, i, updateFile) << std::endl;
				updateDisplayData(data, i);
				return;
			}
		}
		i++;
	}
}

void Display::getOverDue(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	time_t t = time(0);   
	struct tm now;
	localtime_s(&now, &t);
	int i = 0;
	int j = 0;
	bool updateFile = false;
	data.getTempData().clear();
	data.getTempIndexList().clear();

	while (i < data.getData().size() && data.getData()[i].isFloat) {
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].year <= (now.tm_year + 1900) && data.getData()[i].month <= (now.tm_mon + 1) && data.getData()[i].day < (now.tm_mday)) {
				scheduled << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if(data.getData()[i].year <= (now.tm_year + 1900) && data.getData()[i].month <= (now.tm_mon + 1) && data.getData()[i].day < (now.tm_mday)) {
				deadline << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}
	return;
}

void Display::getPriority(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	int i = 0;
	int j = 0;
	bool updateFile = false;
	data.getTempIndexList().clear();
	data.getTempData().clear();

	while (i < data.getData().size() && data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].priority == data.get_tempEntry().priority) {
				floating << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].priority == data.get_tempEntry().priority) {
				scheduled << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].priority == data.get_tempEntry().priority) {
				deadline << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}
	return;
}

void Display::getCat(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	int i = 0;
	int j = 0;
	bool updateFile = false;
	data.getTempIndexList().clear();
	data.getTempData().clear();

	while (i < data.getData().size() && data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].category == data.get_tempEntry().category) {
				floating << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].category == data.get_tempEntry().category) {
				scheduled << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].category == data.get_tempEntry().category) {
				deadline << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}
	return;
}

void Display::getTime(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	int i = 0;
	int j = 0;
	bool updateFile = false;
	data.getTempData().clear();
	data.getTempIndexList().clear();

	while (i < data.getData().size() && data.getData()[i].isFloat && data.get_tempEntry().isFloat) {
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == data.get_tempEntry().day && data.getData()[i].month ==  data.get_tempEntry().month && data.getData()[i].year ==  data.get_tempEntry().year) {
				if (data.getData()[i].startTime >= data.get_tempEntry().startTime) {
					scheduled << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
					updateDisplayData(data, i);
					j++;
				}
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == data.get_tempEntry().day && data.getData()[i].month ==  data.get_tempEntry().month && data.getData()[i].year ==  data.get_tempEntry().year) {
				if (data.getData()[i].startTime >= data.get_tempEntry().startTime) {
					deadline << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
					updateDisplayData(data, i);
					j++;
				}
			}
		}
		i++;
	}
	return;
}

void Display::getDay(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	int i = 0;
	int j = 0;
	bool updateFile = false;
	data.getTempIndexList().clear();
	data.getTempData().clear();

	while (i < data.getData().size() && data.getData()[i].isFloat) {
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == data.get_tempEntry().day && data.getData()[i].month ==  data.get_tempEntry().month && data.getData()[i].year ==  data.get_tempEntry().year) {
				scheduled << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == data.get_tempEntry().day && data.getData()[i].month ==  data.get_tempEntry().month && data.getData()[i].year ==  data.get_tempEntry().year) {
				deadline << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}
	return;
}

void Display::getTmr(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	time_t t = time(0);   
	struct tm now;
	localtime_s(&now, &t);
	int i = 0;
	int j = 0;
	bool updateFile = false;
	data.getTempIndexList().clear();
	data.getTempData().clear();

	while (i < data.getData().size() && data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == (now.tm_mday + 1) && data.getData()[i].month == (now.tm_mon + 1) && data.getData()[i].year == (now.tm_year + 1900)) {
				floating << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == (now.tm_mday + 1) && data.getData()[i].month == (now.tm_mon + 1) && data.getData()[i].year == (now.tm_year + 1900)) {
				scheduled << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == (now.tm_mday + 1) && data.getData()[i].month == (now.tm_mon + 1) && data.getData()[i].year == (now.tm_year + 1900)) {
				deadline << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}
	return;
}

void Display::getToday(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	time_t t = time(0);   
	struct tm now;
	localtime_s(&now, &t);
	int i = 0;
	int j = 0;
	bool updateFile = false;
	data.getTempData().clear();
	data.getTempIndexList().clear();

	while (i < data.getData().size() && data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == (now.tm_mday) && data.getData()[i].month == (now.tm_mon + 1) && data.getData()[i].year == (now.tm_year + 1900)) {
				floating << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == (now.tm_mday) && data.getData()[i].month == (now.tm_mon + 1) && data.getData()[i].year == (now.tm_year + 1900)) {
				scheduled << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == (now.tm_mday) && data.getData()[i].month == (now.tm_mon + 1) && data.getData()[i].year == (now.tm_year + 1900)) {
				deadline << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
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

void Display::getFloat(DataStore &data, std::ostringstream &floating) {
	int i = 0;
	bool updateFile = false;
	data.getTempIndexList().clear();
	data.getTempData().clear();
	
	while (i < data.getData().size() && !data.getData()[i].isComplete && data.getData()[i].isFloat) {
		floating << " " << (i + 1) << ". " << getDataString(data, i, updateFile) << std::endl;
		updateDisplayData(data, i);
		i++;
	}
	return;
}

void Display::getScheduled(DataStore &data, std::ostringstream &scheduled) {
	int i = 0;
	bool updateFile = false;
	data.getTempData().clear();
	data.getTempIndexList().clear();
	
	while (i < data.getData().size() && !data.getData()[i].isComplete && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		scheduled << " " << (i + 1) << ". " << getDataString(data, i, updateFile) << std::endl;
		updateDisplayData(data, i);
		i++;
	}
	return;
}

void Display::getDeadline(DataStore &data, std::ostringstream &deadline) {
	int i = 0;
	bool updateFile = false;
	data.getTempData().clear();
	data.getTempIndexList().clear();

	while (i < data.getData().size() && !data.getData()[i].isComplete && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		deadline << " " << (i + 1) << ". " << getDataString(data, i, updateFile) << std::endl;
		updateDisplayData(data, i);
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
	data.getTempData().clear();
	data.getTempIndexList().clear();
	
	while (i < data.getData().size() && data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].year == (now.tm_year + 1900) && data.getData()[i].month == (now.tm_mon + 1) && ((data.getData()[i].day - (now.tm_mday) < 3) && (data.getData()[i].day - (now.tm_mday) >= 0))) {
				floating << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].year == (now.tm_year + 1900) && data.getData()[i].month == (now.tm_mon + 1) && ((data.getData()[i].day - (now.tm_mday) < 3) && (data.getData()[i].day - (now.tm_mday) >= 0))) {
				scheduled << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].year == (now.tm_year + 1900) && data.getData()[i].month == (now.tm_mon + 1) && ((data.getData()[i].day - (now.tm_mday) < 3) && (data.getData()[i].day - (now.tm_mday) >= 0))) {
				deadline << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
				updateDisplayData(data, i);
				j++;
			}
		}
		i++;
	}
	return;
}

void Display::getComplete(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	int i = 0;
	int j = 0;
	bool updateFile = false;
	data.getTempData().clear();
	data.getTempIndexList().clear();
	
	while (i < data.getData().size() && data.getData()[i].isFloat) {
		if (data.getData()[i].isComplete) {
			floating << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
			updateDisplayData(data, i);
			j++;
		}
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (data.getData()[i].isComplete) {
			scheduled << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
			updateDisplayData(data, i);
			j++;
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (data.getData()[i].isComplete) {
			deadline << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
			updateDisplayData(data, i);
			j++;
		}
		i++;
	}
	return;
}

//Completed tasks not displayed
bool Display::getDisplay(DataStore &data, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	if (data.getData().empty()) {
		errMsg << "file is empty";
		return false;
	}
	int i = 0;
	int j = 0;
	bool updateFile = false;
	data.getTempData().clear();
	data.getTempIndexList().clear();
	
	while (i < data.getData().size() && data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			floating << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
			updateDisplayData(data, i);
			j++;
		}
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask) {
		if (!data.getData()[i].isComplete) {
			scheduled << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
			updateDisplayData(data, i);
			j++;
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask) {
		if (!data.getData()[i].isComplete) {
			deadline << " " << (j + 1) << ". " << getDataString(data, i, updateFile, j) << std::endl;
			updateDisplayData(data, i);
			j++;
		}
		i++;
	}

	if (data.getTempData().empty()) {
		errMsg << "all tasks are completed";
		return false;
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
	int maxSize = 0;

	if (!isTemp) {
		for (int i = 0; i != data.getData().size(); i++) {
			if (data.getData()[i].subject.size() > maxSize) {
				maxSize = data.getData()[i].subject.size();
			}
		}
	
		if (data.getData()[index].subject.size() > count && !updateFile) {
			std::string cutOff = data.getData()[index].subject.substr(0, count - 2);
			dataString << cutOff << "..";
		}
		else {
			dataString << data.getData()[index].subject;
			if (maxSize > count && updateFile) {
				printSpace(dataString, maxSize - data.getData()[index].subject.size());
			}
			else {
				printSpace(dataString, count - data.getData()[index].subject.size());
			}
		}
	}
	else {
		if (data.getTempData()[index].subject.size() > count) {
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
		dataString << data.getData()[index].month;
		printZero(nYear, dataString, 4);
		dataString << '/' << data.getData()[index].year;
	}
	else {
		int nDay = countDigit(data.getTempData()[index].day);
		int nMonth = countDigit(data.getTempData()[index].month);
		int nYear = countDigit(data.getTempData()[index].year);

		printZero(nDay, dataString, 2);
		dataString << data.getTempData()[index].day << '/';	
		printZero(nMonth, dataString, 2);
		dataString << data.getTempData()[index].month;
		printZero(nYear, dataString, 4);
		dataString << '/' << data.getTempData()[index].year;
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