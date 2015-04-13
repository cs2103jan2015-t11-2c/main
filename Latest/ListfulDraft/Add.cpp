#include "Add.h"

//To add floating and non-floating where the floating tasks
//If a clash (subject or time and date) is found, it will still add but a warning message will be output
bool Add::addContent(DataStore &data, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, bool isTemp) {
	if (data.get_tempEntry().subject == "") {
		return false;
	}

	if (!data.getData().empty() && !isTemp) {
		checkDuplicate(data, errMsg);
	}
	
	data.clearData(floating, scheduled, deadline);
	insertionAdd(data, isTemp, errMsg, floating, scheduled, deadline);
	return true;
}

//Checks if the date clashes
bool Add::isSameDate(DataStore data, int index) {
	if (data.getData()[index].year == data.get_tempEntry().year && data.getData()[index].month == data.get_tempEntry().month && data.getData()[index].day == data.get_tempEntry().day) {
		return true;
	}
	return false;
}

//Checks if time clashes
bool Add::isSameTime(DataStore data, int index) {
	int num1 = data.getData()[index].endTime;
	int num2 = data.get_tempEntry().endTime;
	
	//To take note of '12am' since it is considered 0 so that we can get the correct duration
	if (num1 == 0) {
		num1 = 2400;
	}
	if (num2 == 0) {
		num2 = 2400;
	}
	
	//To check if the tasks entered have overlapping times or not
	if (data.getData()[index].startTime == data.get_tempEntry().startTime) {
		return true;
	}
	if (data.getData()[index].startTime <= data.get_tempEntry().startTime) {
		if ((data.get_tempEntry().startTime - data.getData()[index].startTime) < (num1 - data.getData()[index].startTime)) {
			return true;
		}
	}
	if (data.getData()[index].startTime >= data.get_tempEntry().startTime) {
		 if ((data.getData()[index].startTime - data.get_tempEntry().startTime) < (num2 - data.get_tempEntry().startTime)) {
			return true;
		 }
	}
	return false;
}

//Outputs warning message if date or time has passed
void Add::checkDateTime(DataStore data, std::ostringstream &errMsg, bool pastDate, bool checkTime) {
	int index = 0;
	if (pastDate) {
		errMsg << std::endl << " WARNING: date entered has already past (undo/edit adviced)";
	}
	if (checkTime && data.get_tempEntry().endTime > data.get_tempEntry().startTime && data.get_tempEntry().endTime != 0) {
		errMsg << std::endl << " end time entered earlier then start time (undo/edit adviced)";
	}
	return;
}

void Add::checkDuplicate(DataStore data, std::ostringstream &errMsg) {
	int index = 0;

	//Once a clash is found there is no need to search for further clashes since our program informs the user of any initial clashes already
	for (index = 0; index != data.getData().size(); index++) {
		if ((data.getData()[index].isFloat == data.get_tempEntry().isFloat) && (data.getData()[index].isTimedTask == data.get_tempEntry().isTimedTask)) {
			if (!data.getData()[index].isComplete) {
				if (data.getData()[index].subject == data.get_tempEntry().subject) {
					errMsg << std::endl << " WARNING: subject clash ";
					if (!data.getData()[index].isFloat && (isSameDate(data, index)) && (isSameTime(data, index))) {
						errMsg << "timing clash ";
					}
					errMsg << " (undo/edit adviced)";
					return;
				}
				else if (!data.getData()[index].isFloat && (isSameDate(data, index)) && (isSameTime(data, index))) {
					errMsg << std::endl << " WARNING: timing clash (undo/edit adviced)";
					return;
				}
			}
		}
	}
	return;
}

void Add::insertionAdd(DataStore &data, bool isTemp, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	Search search;
	
	//Empty
	if (data.getData().empty() && !isTemp) {
		data.getData().push_back(data.get_tempEntry());
	}
	else if (data.getTempData().empty() && isTemp) {
		data.getTempData().push_back(data.get_tempEntry());
	}
	//Float
	else if (data.get_tempEntry().isFloat) {
		floatAdd(data, isTemp);
	}
	//Scheduled
	else if (data.get_tempEntry().isTimedTask && !data.get_tempEntry().isFloat) {
		if (!isTemp && !scheduledAdd(data, isTemp)) {
			data.getData().push_back(data.get_tempEntry());
		}
		else if (isTemp && !scheduledAdd(data, isTemp)) {
			data.getTempData().push_back(data.get_tempEntry());
		}
	}
	//Deadline
	else if (!data.get_tempEntry().isTimedTask && !data.get_tempEntry().isFloat) {
		if (!isTemp && !deadlineAdd(data, isTemp)) {
			data.getData().push_back(data.get_tempEntry());
		}
		else if (isTemp && !deadlineAdd(data, isTemp)) {
			data.getTempData().push_back(data.get_tempEntry());
		}
	}

	if (!isTemp) {
		search.getEntry(data, floating, scheduled, deadline, errMsg);
	}
	return;
}

bool Add::scheduledAdd(DataStore &data, bool isTemp) {
	std::vector <Entry>::iterator iter;
	std::vector <Entry> check;
	int index = 0;

	setData(data, check, isTemp);
	for (iter = check.begin(); iter !=check.end(); iter++) {
		if ((*iter).isTimedTask) {
			if (pushData(data, check, iter, index, isTemp)) {
				setDataBack(data, check, isTemp);
				return true;
			}
		}
		if ((*iter).isTimedTask && (*iter).isComplete) {
			check.insert(iter, data.get_tempEntry());
			setDataBack(data, check, isTemp);
			return true;
		}
		if (!(*iter).isFloat && !(*iter).isTimedTask) { 
			check.insert(iter, data.get_tempEntry());
			setDataBack(data, check, isTemp);
			return true;
		}
		index++;
	}
	return false;
}

bool Add::deadlineAdd(DataStore &data, bool isTemp) {
	std::vector <Entry>::iterator iter;
	std::vector <Entry> check;
	int index = 0;

	setData(data, check, isTemp);
	for (iter = check.begin(); iter != check.end(); iter++) {
		if (!(*iter).isTimedTask && !(*iter).isFloat && !(*iter).isComplete) {
			if (pushData(data, check, iter, index, isTemp)) {
				setDataBack(data, check, isTemp);
				return true;
			}
		}
		if ((!(*iter).isTimedTask && !(*iter).isFloat) && (*iter).isComplete) { 
			check.insert(iter, data.get_tempEntry());
			setDataBack(data, check, isTemp);
			return true;
		}
		index++;
	}
	return false;
}

void Add::floatAdd(DataStore &data, bool isTemp) {
	std::vector <Entry>::iterator iter;
	std::vector <Entry> check;
	int index = 0;
	
	setData(data, check, isTemp);	
	for (iter = check.begin(); iter != check.end(); iter++) {
		if ((*iter).isFloat && !(*iter).isComplete && pushData(data, check, iter, index, isTemp)) {
			setDataBack(data, check, isTemp);
			return;
		}
		if (((*iter).isFloat && (*iter).isComplete)) { 
			check.insert(iter, data.get_tempEntry());
			setDataBack(data, check, isTemp);
			return;
		}
		if (!(*iter).isFloat) {	
			check.insert(iter, data.get_tempEntry());
			setDataBack(data, check, isTemp);
			return;
		}
		if ((iter + 1) == check.end()) {
			check.push_back(data.get_tempEntry());
			setDataBack(data, check, isTemp);
			return;
		}
		index++;
	}
	return;
}

bool Add::pushData(DataStore &data, std::vector <Entry> &check, std::vector <Entry>::iterator iter, int index, bool isTemp) {
	if (isSameDate(data, index) && !isTemp) {
		if ((*iter).startTime > data.get_tempEntry().startTime) {
			check.insert(iter, data.get_tempEntry());
			return true;
		}
		else if ((*iter).startTime == data.get_tempEntry().startTime) {
			if ((*iter).endTime > data.get_tempEntry().endTime) {
				check.insert(iter, data.get_tempEntry());
				return true;
			}
		}
	}
	//Cmp day
	else if (((*iter).year == data.get_tempEntry().year) && ((*iter).month == data.get_tempEntry().month) && ((*iter).day > data.get_tempEntry().day)) {
		if (!isTemp) {
			check.insert(iter, data.get_tempEntry());
		}
		else {
			check.insert(iter, data.get_tempEntry());
		}
		return true;
	}
	//Cmp month
	else if (((*iter).year == data.get_tempEntry().year) && ((*iter).month > data.get_tempEntry().month)) {
		if (!isTemp) {
			check.insert(iter, data.get_tempEntry());
		}
		else {
			check.insert(iter, data.get_tempEntry());
		}
		return true;
	}
	//Cmp year
	else if (((*iter).year > data.get_tempEntry().year)) {
		if (!isTemp) {
			check.insert(iter, data.get_tempEntry());
		}
		else {
			check.insert(iter, data.get_tempEntry());
		}
		return true;
	}
	return false;
}

void Add::setData(DataStore &data, std::vector <Entry> &check, bool isTemp) {
	if (!isTemp) {
		check = data.getData();
	}
	else {
		check = data.getTempData();
	}
	return;
}

void Add::setDataBack(DataStore &data, std::vector <Entry> &check, bool isTemp) {
	if (!isTemp) {
		data.getData() = check;
	}
	else {
		data.getTempData() = check;
	}
	return;
}