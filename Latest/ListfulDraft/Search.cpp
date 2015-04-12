#include "Search.h"

const int Search::FLOAT_SUB_SIZE = 44;
const int Search::NON_FLOAT_SUB_SIZE = 31;

bool Search::displayContent(DataStore &data, std::string info, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	if (info == "today" || info == "tdy" || info == "tday" || info == "later" || info == "tonight") {
		getToday(data, floating, scheduled, deadline, errMsg);
	}
	else if (info == "tomorrow" || info == "tmr" || info == "tomoro" || info == "tmrw") {
		getTmr(data, floating, scheduled, deadline, errMsg);
	}
	else if (info == "over" || info == "overdue" || info == "past" || info == "yesterday") {
		getOverDue(data, floating, scheduled, deadline, errMsg);
	}
	else if (info == "done" || info == "complete" || info == "completed" || info == "finished" || info == "finish") {
		getComplete(data, floating, scheduled, deadline, errMsg);
	}
	else if (info == "remind" || info == "reminder" || info == "due") {
		getReminder(data, floating, scheduled, deadline, errMsg);
	}
	else if (info == "float" || info == "to do") {
		getFloat(data, floating, errMsg);
	}
	else if (info == "scheduled" || info == "schedule" || info == "time table" || info == "plan") {
		getScheduled(data, scheduled, errMsg);
	}
	else if (info == "deadline" || info == "due") {
		getDeadline(data, deadline, errMsg);
	}
	else if (info == "all") {
		return getDisplay(data, errMsg, floating, scheduled, deadline);
	}
	else if (info[0] >= '0' && info[0] <= '9') {
		getFullString(info, data, errMsg, floating, scheduled, deadline);
	}

	if (data.getTempData().size() != 0) {
		return true;
	}
	return false;
}


void Search::updateDisplayData(DataStore &data, int i) {
	data.getTempData().push_back(data.getData()[i]);
	data.getTempIndexList().push_back(i);
}


void Search::getFloat(DataStore &data, std::ostringstream &floating, std::ostringstream &errMsg) {
	int i = 0;
	std::ostringstream ignore;
	bool updateFile = false;
	data.getTempIndexList().clear();
	data.getTempData().clear();
	
	while (i < data.getData().size() && !data.getData()[i].isComplete && data.getData()[i].isFloat) {
		updateDisplayData(data, i);
		i++;
	}

	if (data.getTempData().size() == 0) {
		errMsg << "no to do tasks are found";
		return;
	}
	stringGetter(data, floating, ignore, ignore);
	return;
}

void Search::getScheduled(DataStore &data, std::ostringstream &scheduled, std::ostringstream &errMsg) {
	int i = 0;
	std::ostringstream ignore;
	bool updateFile = false;
	data.getTempData().clear();
	data.getTempIndexList().clear();
	
	while (i < data.getData().size()) {
		if (!data.getData()[i].isComplete && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
			updateDisplayData(data, i);
		}
		i++;
	}

	if (data.getTempData().size() == 0) {
		errMsg << "no scheduled tasks are found";
		return;
	}
	stringGetter(data, ignore, scheduled, ignore);
	return;
}

void Search::getDeadline(DataStore &data, std::ostringstream &deadline, std::ostringstream &errMsg) {
	int i = 0;
	std::ostringstream ignore;
	bool updateFile = false;
	data.getTempData().clear();
	data.getTempIndexList().clear();

	while (i < data.getData().size()) {
		if (!data.getData()[i].isComplete && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
			updateDisplayData(data, i);
		}
		i++;
	}

	if (data.getTempData().size() == 0) {
		errMsg << "no deadline tasks are found";
		return;
	}
	stringGetter(data, ignore, ignore, deadline);
	return;
}



void Search::getToday(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::ostringstream &errMsg) {
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
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == (now.tm_mday) && data.getData()[i].month == (now.tm_mon + 1) && data.getData()[i].year == (now.tm_year + 1900)) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == (now.tm_mday) && data.getData()[i].month == (now.tm_mon + 1) && data.getData()[i].year == (now.tm_year + 1900)) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	if (data.getTempData().size() == 0) {
		errMsg << "no tasks due today";
		return;
	}
	stringGetter(data, floating, scheduled, deadline);
	return;
}

void Search::getTmr(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::ostringstream &errMsg) {
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
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == (now.tm_mday + 1) && data.getData()[i].month == (now.tm_mon + 1) && data.getData()[i].year == (now.tm_year + 1900)) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == (now.tm_mday + 1) && data.getData()[i].month == (now.tm_mon + 1) && data.getData()[i].year == (now.tm_year + 1900)) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	if (data.getTempData().size() == 0) {
		errMsg << "no tasks due tomorrow";
		return;
	}
	stringGetter(data, floating, scheduled, deadline);
	return;
}



void Search::getComplete(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::ostringstream &errMsg) {
	int i = 0;
	int j = 0;
	bool updateFile = false;
	data.getTempData().clear();
	data.getTempIndexList().clear();
	
	while (i < data.getData().size() && data.getData()[i].isFloat) {
		if (data.getData()[i].isComplete) {
			updateDisplayData(data, i);
		}
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (data.getData()[i].isComplete) {
			updateDisplayData(data, i);
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (data.getData()[i].isComplete) {
			updateDisplayData(data, i);
		}
		i++;
	}

	if (data.getTempData().size() == 0) {
		errMsg << "completed tasks found";
		return;
	}
	stringGetter(data, floating, scheduled, deadline);
	return;
}

void Search::getReminder(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::ostringstream &errMsg) {
	int i = 0;
	int j = 0;
	bool updateFile = false;
	time_t t = time(0);   
	struct tm now;
	localtime_s(&now, &t);
	data.getTempData().clear();
	data.getTempIndexList().clear();
	
	while (i < data.getData().size() && data.getData()[i].isFloat) {
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].year == (now.tm_year + 1900) && data.getData()[i].month == (now.tm_mon + 1) && ((data.getData()[i].day - (now.tm_mday) < 3) && (data.getData()[i].day - (now.tm_mday) >= 0))) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].year == (now.tm_year + 1900) && data.getData()[i].month == (now.tm_mon + 1) && ((data.getData()[i].day - (now.tm_mday) < 3) && (data.getData()[i].day - (now.tm_mday) >= 0))) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}
	if (data.getTempData().size() == 0) {
		errMsg << "no tasks due for the next three days";
		return;
	}
	stringGetter(data, floating, scheduled, deadline);
	return;
}

void Search::getOverDue(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::ostringstream &errMsg) {
	time_t t = time(0);   
	struct tm now;
	localtime_s(&now, &t);
	int i = 0;
	data.getTempData().clear();
	data.getTempIndexList().clear();

	while (i < data.getData().size() && data.getData()[i].isFloat) {
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].year <= (now.tm_year + 1900) && data.getData()[i].month <= (now.tm_mon + 1) && data.getData()[i].day < (now.tm_mday)) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if(data.getData()[i].year <= (now.tm_year + 1900) && data.getData()[i].month <= (now.tm_mon + 1) && data.getData()[i].day < (now.tm_mday)) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}
	std::cout << "agf" << data.getTempData().size() << std::endl;
	if (data.getTempData().size() == 0) {
		errMsg << "no tasks are overdue";
		return;
	}
	stringGetter(data, floating, scheduled, deadline);
	return;
}



bool Search::getRemainingStr(std::string &cutOff, std::string &remaining, int count) {
	if (remaining.size() > count) {
		cutOff = remaining.substr(0, count);
		remaining = remaining.substr(count);
		return true;
	}
	return false;
}

void Search::getFullString(std::string info, DataStore &data, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	int num = 0;
	bool updateFile = false;
	bool isTemp = true;
	std::string cutOff = "";

	num = atoi(info.c_str());
	if (num > data.getTempData().size()) {
		errMsg << "index out of range";
		return;
	}
	std::string remainingStr = data.getTempData()[num].subject;
	
	if (data.getTempData()[num].isFloat) {
		floating << "  1. ";
		if (getRemainingStr(cutOff, remainingStr, FLOAT_SUB_SIZE)) {
			floating << cutOff << " | " << getTime(data, num, isTemp) << " | " << data.getTempData()[num].category << " | " << data.getTempData()[num].priority << std::endl;
			while (getRemainingStr(cutOff, remainingStr, FLOAT_SUB_SIZE)) {
				floating << cutOff;
				printSpace(floating, FLOAT_SUB_SIZE - cutOff.size());
				floating << " |           |          | " << std::endl;
			}
			floating << remainingStr << " |           |          | " << std::endl;
		}
		else if (data.getTempData().size() < FLOAT_SUB_SIZE) {
			floating << getTempDataString(data, num, updateFile) << std::endl;
		}
	}
	else if (data.getTempData()[num].isTimedTask) {
		scheduled << "  1. ";
		if (getRemainingStr(cutOff, remainingStr, FLOAT_SUB_SIZE)) {
			scheduled << cutOff << " | " << getTime(data, num, isTemp) << " | " << data.getTempData()[num].category << " | " << data.getTempData()[num].priority << std::endl;
			while (getRemainingStr(cutOff, remainingStr, FLOAT_SUB_SIZE)) {
				scheduled << cutOff;
				printSpace(scheduled, FLOAT_SUB_SIZE - cutOff.size());
				scheduled << " |           |          | " << std::endl;
			}
			scheduled << remainingStr << " |           |          | " << std::endl;
		}
		else if (data.getTempData().size() < FLOAT_SUB_SIZE) {
			scheduled << getTempDataString(data, num, updateFile) << std::endl;
		}
	}
	else {
		deadline << "  1. ";
		if (getRemainingStr(cutOff, remainingStr, FLOAT_SUB_SIZE)) {
			deadline << cutOff << " | " << getTime(data, num, isTemp) << " | " << data.getTempData()[num].category << " | " << data.getTempData()[num].priority << std::endl;
			while (getRemainingStr(cutOff, remainingStr, FLOAT_SUB_SIZE)) {
				deadline << cutOff;
				printSpace(deadline, FLOAT_SUB_SIZE - cutOff.size());
				deadline << " |           |          | " << std::endl;
			}
			deadline << remainingStr << " |           |          | " << std::endl;
		}
		else if (data.getTempData().size() < FLOAT_SUB_SIZE) {
			deadline << getTempDataString(data, num, updateFile) << std::endl;
		}
	}
	data.get_tempEntry() = data.getTempData()[num];
	data.getTempData().clear();
	int i = 0;
	while (data.get_tempEntry().referenceNo != data.getData()[data.getTempIndexList()[i]].referenceNo) {
		i++;
	}
	i = data.getTempIndexList()[i];
	data.getTempIndexList().clear();
	data.getTempData().push_back(data.get_tempEntry());
	data.getTempIndexList().push_back(i);
	return;
}

void Search::getEntry(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::ostringstream &errMsg) {
	int i = 0;
	bool updateFile = false;
	data.getTempIndexList().clear();
	data.getTempData().clear();
	
	while (i < data.getData().size()) {
		if (data.getData()[i].referenceNo == data.get_tempEntry().referenceNo) {
			if (data.getData()[i].isFloat) {
				floating << " 1. " << getDataString(data, i, updateFile, 1) << std::endl;
				updateDisplayData(data, i);
				return;
			}
			else if (data.getData()[i].isTimedTask) {
				scheduled << " 1. " << getDataString(data, i, updateFile, 1) << std::endl;
				updateDisplayData(data, i);
				return;
			}
			else {
				deadline << " 1. " << getDataString(data, i, updateFile, 1) << std::endl;
				updateDisplayData(data, i);
				return;
			}
		}
		i++;
	}
}



void Search::getPriority(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::ostringstream &errMsg) {
	int i = 0;
	int j = 0;
	data.getTempIndexList().clear();
	data.getTempData().clear();

	while (i < data.getData().size() && data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].priority == data.get_tempEntry().priority) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].priority == data.get_tempEntry().priority) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].priority == data.get_tempEntry().priority) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	if (data.getTempData().size() == 0) {
		errMsg << "no tasks with priority " << data.get_tempEntry().priority << " found";
		return;
	}
	stringGetter(data, floating, scheduled, deadline);
	return;
}

void Search::getCat(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::ostringstream &errMsg) {
	int i = 0;
	int j = 0;
	data.getTempIndexList().clear();
	data.getTempData().clear();

	while (i < data.getData().size() && data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].category == data.get_tempEntry().category) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].category == data.get_tempEntry().category) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].category == data.get_tempEntry().category) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	if (data.getTempData().size() == 0) {
		errMsg << "no tasks under the category " << data.get_tempEntry().category << " found";
		return;
	}
	stringGetter(data, floating, scheduled, deadline);
	return;
}

void Search::getTime(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::ostringstream &errMsg) {
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
					updateDisplayData(data, i);
				}
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == data.get_tempEntry().day && data.getData()[i].month ==  data.get_tempEntry().month && data.getData()[i].year ==  data.get_tempEntry().year) {
				if (data.getData()[i].startTime >= data.get_tempEntry().startTime) {
					updateDisplayData(data, i);
				}
			}
		}
		i++;
	}

	if (data.getTempData().size() == 0) {
		errMsg << "no tasks due on " << data.get_tempEntry().day << '/' << data.get_tempEntry().month << '/' << data.get_tempEntry().year;
		errMsg << " at " << data.get_tempEntry().startTime;
		return;
	}
	stringGetter(data, floating, scheduled, deadline);
	return;
}

void Search::getDay(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::ostringstream &errMsg) {
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
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask && !data.getData()[i].isFloat) {
		if (!data.getData()[i].isComplete) {
			if (data.getData()[i].day == data.get_tempEntry().day && data.getData()[i].month ==  data.get_tempEntry().month && data.getData()[i].year ==  data.get_tempEntry().year) {
				updateDisplayData(data, i);
			}
		}
		i++;
	}

	if (data.getTempData().size() == 0) {
		errMsg << "no tasks due on " << data.get_tempEntry().day << '/' << data.get_tempEntry().month << '/' << data.get_tempEntry().year;
		return;
	}
	stringGetter(data, floating, scheduled, deadline);
	return;
}



void Search::getTempDisplay(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::ostringstream &errMsg) {
	int i = 0;
	bool updateFile = false;
	
	if (data.getTempData().size() == 0) {
		return;
	}

	while (i < data.getTempData().size() && data.getTempData()[i].isFloat) {
		updateDisplayData(data, i);
		i++;
	}

	while (i < data.getTempData().size() && data.getTempData()[i].isTimedTask) {
		updateDisplayData(data, i);
		i++;
	}

	while (i < data.getTempData().size() && !data.getTempData()[i].isTimedTask) {
		updateDisplayData(data, i);
		i++;
	}
	stringGetter(data, floating, scheduled, deadline);
	return;
}

//Completed tasks not displayed
bool Search::getDisplay(DataStore &data, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
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
			updateDisplayData(data, i);
		}
		i++;
	}

	while (i < data.getData().size() && data.getData()[i].isTimedTask) {
		if (!data.getData()[i].isComplete) {
			updateDisplayData(data, i);
		}
		i++;
	}

	while (i < data.getData().size() && !data.getData()[i].isTimedTask) {
		if (!data.getData()[i].isComplete) {
			updateDisplayData(data, i);
		}
		i++;
	}

	if (data.getTempData().empty()) {
		errMsg << "all tasks are completed";
		return false;
	}
	stringGetter(data, floating, scheduled, deadline);
	return true;
}



std::string Search::getDataString(DataStore &data, int index, bool updateFile, int index2) {
	std::ostringstream dataString;
	bool isTemp = false;

	if (data.getData()[index].isFloat) {
		if (data.getData().size() > 9 && index2 < 1) {
			printSub(data, dataString, FLOAT_SUB_SIZE - 1, index, updateFile, isTemp);
		}
		else {
			printSub(data, dataString, FLOAT_SUB_SIZE, index, updateFile, isTemp);
		}
	}
	else {
		if (data.getData().size() > 9 && index2 < 0) {
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
	printPriority(data, dataString, index, isTemp);
	return dataString.str();
}

std::string Search::getTempDataString(DataStore &data, int index, bool updateFile) {
	std::ostringstream dataString;
	bool isTemp = true;

	if (data.getTempData()[index].isFloat) {
		if  (data.getTempData().size() > 9) {
			printSub(data, dataString, FLOAT_SUB_SIZE - 1, index, updateFile, isTemp);
		}
		else {
			printSub(data, dataString, FLOAT_SUB_SIZE, index, updateFile, isTemp);
		}
	}
	else {
		if (data.getTempData().size() > 9) {
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
	printPriority(data, dataString, index, isTemp);
	return dataString.str();
}

void Search::stringGetter(DataStore &data, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	int i = 0;
	bool updateFile = false;
	
	while (i < data.getTempData().size()) {
		if (data.getTempData().size() > 9 && i < 9) {
			if (data.getTempData()[i].isFloat) {
				floating << "  " << (i + 1) << ". " << getTempDataString(data, i, updateFile) << std::endl;
			}
			else if (data.getTempData().size() > 9 && data.getTempData()[i].isTimedTask) {
				scheduled << "  " << (i + 1) << ". " << getTempDataString(data, i, updateFile) << std::endl;
			}
			else if (data.getTempData().size() > 9 && !data.getTempData()[i].isTimedTask && !data.getTempData()[i].isFloat) {
				deadline << "  " << (i + 1) << ". " << getTempDataString(data, i, updateFile) << std::endl;
			}
		}
		else {
			if (data.getTempData()[i].isFloat) {
				floating << " " << (i + 1) << ". " << getTempDataString(data, i, updateFile) << std::endl;
			}
			else if (data.getTempData()[i].isTimedTask) {
				scheduled << " " << (i + 1) << ". " << getTempDataString(data, i, updateFile) << std::endl;
			}
			else if (!data.getTempData()[i].isTimedTask && !data.getTempData()[i].isFloat) {
				deadline << " " << (i + 1) << ". " << getTempDataString(data, i, updateFile) << std::endl;
			}
		}
		i++;
	}
	return;
}



void Search::printSub(DataStore &data, std::ostringstream &dataString, int count, int index, bool updateFile, bool isTemp) {
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
		else if (!updateFile) {
			dataString << data.getData()[index].subject;
			printSpace(dataString, count - data.getData()[index].subject.size());
		}
		else if (maxSize > count && updateFile) {
			dataString << data.getData()[index].subject;
			if (data.getData()[index].isFloat) {
				printSpace(dataString, 13);
			}
			printSpace(dataString, maxSize - data.getData()[index].subject.size());
		}
		else if (updateFile) {
			dataString << data.getData()[index].subject;
			printSpace(dataString, count - data.getData()[index].subject.size());
		}
	}
	else if (data.getTempData()[index].subject.size() > count) {
		std::string cutOff = data.getTempData()[index].subject.substr(0, count - 2);
		dataString << cutOff << "..";
	}
	else {
		dataString << data.getTempData()[index].subject;
		printSpace(dataString, count - data.getTempData()[index].subject.size());
	}
	return;
}

void Search::printDate(DataStore &data, std::ostringstream &dataString, int index, bool isTemp) {
	if (!isTemp && !data.getData()[index].isFloat) {
		int nDay = countDigit(data.getData()[index].day);
		int nMonth = countDigit(data.getData()[index].month);
		int nYear = countDigit(data.getData()[index].year);
		
		printZero(nDay, dataString, 2);
		dataString << data.getData()[index].day << '/';	
		printZero(nMonth, dataString, 2);
		dataString << data.getData()[index].month << '/';
		printZero(nYear, dataString, 4);
		dataString << data.getData()[index].year;
	}
	else if (!data.getTempData()[index].isFloat) {
		int nDay = countDigit(data.getTempData()[index].day);
		int nMonth = countDigit(data.getTempData()[index].month);
		int nYear = countDigit(data.getTempData()[index].year);

		printZero(nDay, dataString, 2);
		dataString << data.getTempData()[index].day << '/';	
		printZero(nMonth, dataString, 2);
		dataString << data.getTempData()[index].month << '/';
		printZero(nYear, dataString, 4);
		dataString << data.getTempData()[index].year;
	}
	else {
		printSpace(dataString, 10);
	}
	return;
}

void Search::printTime(DataStore &data, std::ostringstream &dataString, int index, bool isTemp) {
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

void Search::printCat(DataStore &data, std::ostringstream &dataString, int index, bool isTemp) {
	if (!isTemp) {
		dataString << data.getData()[index].category;
	}
	else {
		dataString << data.getTempData()[index].category;
	}
	return;
}

void Search::printPriority(DataStore &data, std::ostringstream &dataString, int index, bool isTemp) {
	if (!isTemp) {
		dataString << data.getData()[index].priority;
	}
	else {
		dataString << data.getTempData()[index].priority;
	}
	return;
}



std::string Search::getDate(DataStore &data, int index, bool isTemp) {
	std::ostringstream dataString;
	printDate(data, dataString, index, isTemp);
	return dataString.str();
}

std::string Search::getTime(DataStore &data, int index, bool isTemp) {
	std::ostringstream dataString;
	printTime(data, dataString, index, isTemp);
	return dataString.str();
}



int Search::countDigit(int num) {
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
void Search::printZero(int num, std::ostringstream &dataString, int count) {
	while (num < count) {
		dataString << '0';
		num++;
	}
	return;
}

//To equalize the columns of each output entry
void Search::printSpace(std::ostringstream &dataString, int count) {
	while (count > 0) {
		dataString << " ";
		count--;
	}
	return;
}



void Search::setColour(int value){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}