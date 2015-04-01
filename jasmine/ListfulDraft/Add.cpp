#include "Add.h"

//To add floating and non-floating where the floating tasks
//If a clash (subject or time and date) is found, it will still add but a warning message will be output
bool Add::addContent(DataStore &data, std::ostringstream &errMsg) {
	if (data.get_tempEntry().subject == "") {
		return false;
	}

	if (!data.getData().empty() && isDuplicate(data, errMsg)) {
		errMsg << " (undo to remove add)";
	}
	insertionAdd(data);
	data.updateFile();
	data.savePrevFile();
	return true;
}

//Checks if the date clashes
bool Add::isSameDate(DataStore data, int index) {
	if (data.get_tempEntry().isFloat) {
		return false;
	}

	if (data.getData()[index].year == data.get_tempEntry().year && data.getData()[index].month == data.get_tempEntry().month && data.getData()[index].day == data.get_tempEntry().day) {
		return true;
	}
	return false;
}

//Checks if time clashes
bool Add::isSameTime(DataStore data, int index) {
	int num1 = 0;
	int num2 = 0;

	//To take note of '12am' since it is considered 0 so that we can get the correct duration
	if (data.getData()[index].endTime == 0) {
		num1 = 2400;
	}
	else {
		num1 = data.getData()[index].endTime;
	}

	if (data.get_tempEntry().endTime == 0) {
		num2 = 2400;
	}
	else {
		num2 = data.get_tempEntry().endTime;
	}
	int duration1 = num1 - data.getData()[index].startTime;
	int duration2 = num2 - data.get_tempEntry().startTime;

	//To check if the tasks entered have overlapping times or not
	if (data.getData()[index].startTime == data.get_tempEntry().startTime) {
		return true;
	}
	
	if (data.getData()[index].startTime <= data.get_tempEntry().startTime) {
		if ((data.get_tempEntry().startTime - data.getData()[index].startTime) < duration1) {
			return true;
		}
	}
	
	if (data.getData()[index].startTime >= data.get_tempEntry().startTime) {
		 if ((data.getData()[index].startTime - data.get_tempEntry().startTime) < duration2) {
			return true;
		 }
	}
	return false;
}

//Outputs warning message if subject or time and date clashes
bool Add::isDuplicate(DataStore data, std::ostringstream &errMsg) {
	int index = 0;

	//Once a clash is found there is no need to search for further clashes since our program informs the user of any initial clashes already
	for (index = 0; index != data.getData().size(); index++) {
		errMsg.clear();
		if (data.getData()[index].subject == data.get_tempEntry().subject) {
			errMsg << std::endl << "WARNING: subject clash ";
			if ((isSameDate(data, index)) && (isSameTime(data, index))) {
				errMsg << "timing clash ";
			}
			return true;
		}
		if ((isSameDate(data, index)) && (isSameTime(data, index))) {
			errMsg << std::endl << "WARNING: timing clash ";
			return true;
		}
	}
	return false;
}

//Adding non-floating tasks on the same day
bool Add::sameDayAdd(DataStore &data) {
	std::vector <Entry>::iterator iter;
	int index = 0;

	for (iter = data.getData().begin(); iter != data.getData().end(); iter++) {
		if (isSameDate(data, index) && ((*iter).startTime > data.get_tempEntry().startTime)) {
			data.getData().insert(iter, data.get_tempEntry());
			return true;
		}
		index++;
	}
	return false;
}

//Adding non-floating tasks on with different dates if the new task is the nearest due task
bool Add::diffDayAdd(DataStore &data) {
	std::vector <Entry>::iterator iter;

	for (iter = data.getData().begin(); iter != data.getData().end(); iter++) {
		if (!(*iter).isFloat) {
			if (((*iter).year == data.get_tempEntry().year) && ((*iter).month == data.get_tempEntry().month) && ((*iter).day > data.get_tempEntry().day)) {
				data.getData().insert(iter, data.get_tempEntry());
				return true;
			}
			else if (((*iter).year == data.get_tempEntry().year) && ((*iter).month > data.get_tempEntry().month)) {
				data.getData().insert(iter, data.get_tempEntry());
				return true;
			}
			else if (((*iter).year > data.get_tempEntry().year)) {
				data.getData().insert(iter, data.get_tempEntry());
				return true;
			}
		}
	}
	return false;
}

void Add::floatAdd(DataStore &data) {
	std::vector <Entry>::iterator iter;

	for (iter = data.getData().begin(); iter != data.getData().end(); iter++) {
		if (!(*iter).isFloat) {
			data.getData().insert(iter, data.get_tempEntry());
			return;
		}
	}
	data.getData().push_back(data.get_tempEntry());
	return;
}

void Add::insertionAdd(DataStore &data) {
	if (data.getData().empty()) {
		data.getData().push_back(data.get_tempEntry());
	}
	else if (data.get_tempEntry().isFloat) {
		floatAdd(data);
	}
	else if (!sameDayAdd(data) && !diffDayAdd(data)) {
		//Adding non-floating tasks on with different dates if the new task is the furthest due task
		data.getData().push_back(data.get_tempEntry());
	}
	return;
}