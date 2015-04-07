#include "Add.h"

//To add floating and non-floating where the floating tasks
//If a clash (subject or time and date) is found, it will still add but a warning message will be output
bool Add::addContent(DataStore &data, std::ostringstream &errMsg, bool isTemp) {
	if (data.get_tempEntry().subject == "") {
		return false;
	}

	if (!data.getData().empty() && !isTemp) {
		checkDuplicate(data, errMsg);
	}

	insertionAdd(data, isTemp);
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

//Outputs warning message if subject or time and date clashes
void Add::checkDuplicate(DataStore data, std::ostringstream &errMsg) {
	int index = 0;

	//Once a clash is found there is no need to search for further clashes since our program informs the user of any initial clashes already
	for (index = 0; index != data.getData().size(); index++) {
		if ((data.getData()[index].isFloat == data.get_tempEntry().isFloat) && (data.getData()[index].isTimedTask == data.get_tempEntry().isTimedTask)) {
			if (!data.getData()[index].isComplete) {
				if (data.getData()[index].subject == data.get_tempEntry().subject) {
					std::cout << "3 " << std::endl;
					errMsg << std::endl << " WARNING: subject clash ";
					if (!data.getData()[index].isFloat && (isSameDate(data, index)) && (isSameTime(data, index))) {
						errMsg << "timing clash ";
					}
					errMsg << " (undo/edit adviced)";
					return;
				}
				if (!data.getData()[index].isFloat && (isSameDate(data, index)) && (isSameTime(data, index))) {
					errMsg << std::endl << " WARNING: timing clash (undo/edit adviced)";
					return;
				}
			}
		}
	}
	return;
}

void Add::insertionAdd(DataStore &data, bool isTemp) {
	if (data.getData().empty() && !isTemp) {
		data.getData().push_back(data.get_tempEntry());
	}
	else if (data.getTempData().empty() && isTemp) {
		data.getTempData().push_back(data.get_tempEntry());
	}
	else if (data.get_tempEntry().isFloat) {
		floatAdd(data, isTemp);
	}
	else if (data.get_tempEntry().isTimedTask) {
		if (!scheduledAdd(data, isTemp) && !isTemp) {
			data.getData().push_back(data.get_tempEntry());
		}
		else if (!scheduledAdd(data, isTemp) && isTemp) {
			data.getTempData().push_back(data.get_tempEntry());
		}
	}
	else if (!deadlineAdd(data, isTemp) && !isTemp) {
		data.getData().push_back(data.get_tempEntry());
	}
	else if (!deadlineAdd(data, isTemp) && isTemp) {
		data.getTempData().push_back(data.get_tempEntry());
	}
	return;
}

bool Add::scheduledAdd(DataStore &data, bool isTemp) {
	std::vector <Entry>::iterator iter;
	int index = 0;

	if (!isTemp) {
		for (iter = data.getData().begin(); iter != data.getData().end(); iter++) {
			if ((*iter).isTimedTask) {
				if (pushData(data, iter, index, isTemp)) {
					return true;
				}
			}
			if ((*iter).isTimedTask && (*iter).isComplete) {
				data.getData().insert(iter, data.get_tempEntry());
				return true;
			}
			if (!(*iter).isFloat && !(*iter).isTimedTask) { 
				data.getData().insert(iter, data.get_tempEntry());
				return true;
			}
			index++;
		}
	}
	else {
		for (iter = data.getTempData().begin(); iter != data.getTempData().end(); iter++) {
			if ((*iter).isTimedTask) {
				if (pushData(data, iter, index, isTemp)) {
					return true;
				}
			}
			if ((*iter).isTimedTask && (*iter).isComplete) {
				data.getTempData().insert(iter, data.get_tempEntry());
				return true;
			}
			if (!(*iter).isFloat && !(*iter).isTimedTask) { 
				data.getTempData().insert(iter, data.get_tempEntry());
				return true;
			}
			index++;
		}
	}
	return false;
}

bool Add::deadlineAdd(DataStore &data, bool isTemp) {
	std::vector <Entry>::iterator iter;
	int index = 0;

	if (!isTemp) {
		for (iter = data.getData().begin(); iter != data.getData().end(); iter++) {
			if (!(*iter).isTimedTask && !(*iter).isFloat) {
				if (pushData(data, iter, index, isTemp)) {
					return true;
				}
			}
			if ((!(*iter).isTimedTask && !(*iter).isFloat) && (*iter).isComplete) { 
				data.getData().insert(iter, data.get_tempEntry());
				return true;
			}
			index++;
		}
	}
	else {
		for (iter = data.getTempData().begin(); iter != data.getTempData().end(); iter++) {
			if (!(*iter).isTimedTask && !(*iter).isFloat) {
				if (pushData(data, iter, index, isTemp)) {
					return true;
				}
			}
			if ((!(*iter).isTimedTask && !(*iter).isFloat) && (*iter).isComplete) { 
				data.getTempData().insert(iter, data.get_tempEntry());
				return true;
			}
			index++;
		}
	}
	return false;
}

void Add::floatAdd(DataStore &data, bool isTemp) {
	std::vector <Entry>::iterator iter;
	int index = 0;
	
	if (!isTemp) {
		for (iter = data.getData().begin(); iter != data.getData().end(); iter++) {
			if ((*iter).isFloat && pushData(data, iter, index, isTemp)) {
				return;
			}
			if (((*iter).isFloat && (*iter).isComplete)) { 
				data.getData().insert(iter, data.get_tempEntry());
				return;
			}
			if (!(*iter).isFloat) {
				
				data.getData().insert(iter, data.get_tempEntry());
				return;
			}
			if ((iter + 1) == data.getData().end()) { 
				data.getData().push_back(data.get_tempEntry());
				return;
			}
			index++;
		}
	}
	else {
		for (iter = data.getTempData().begin(); iter != data.getTempData().end(); iter++) {
			if ((*iter).isFloat && pushData(data, iter, index, isTemp)) {
				return;
			}
			if (((*iter).isFloat && (*iter).isComplete)) { 
				data.getTempData().insert(iter, data.get_tempEntry());
				return;
			}
			if (!(*iter).isFloat) {
				data.getTempData().insert(iter, data.get_tempEntry());
				return;
			}
			if ((iter + 1) == data.getTempData().end()) { 
				data.getTempData().push_back(data.get_tempEntry());
				return;
			}
			index++;
		}
	}
	return;
}

bool Add::pushData(DataStore &data, std::vector <Entry>::iterator iter, int index, bool isTemp) {
	if (isSameDate(data, index) && !isTemp) {
		if ((*iter).startTime > data.get_tempEntry().startTime) {
			data.getData().insert(iter, data.get_tempEntry());
			return true;
		}
		else if ((*iter).startTime == data.get_tempEntry().startTime) {
			if ((*iter).endTime < data.get_tempEntry().endTime) {
				data.getData().insert(iter, data.get_tempEntry());
				return true;
			}
		}
	}
	else if (((*iter).year == data.get_tempEntry().year) && ((*iter).month == data.get_tempEntry().month) && ((*iter).day > data.get_tempEntry().day)) {
		if (!isTemp) {
			data.getData().insert(iter, data.get_tempEntry());
		}
		else {
			data.getTempData().insert(iter, data.get_tempEntry());
		}
		return true;
	}
	else if (((*iter).year == data.get_tempEntry().year) && ((*iter).month > data.get_tempEntry().month)) {
		if (!isTemp) {
			data.getData().insert(iter, data.get_tempEntry());
		}
		else {
			data.getTempData().insert(iter, data.get_tempEntry());
		}
		return true;
	}
	else if (((*iter).year > data.get_tempEntry().year)) {
		if (!isTemp) {
			data.getData().insert(iter, data.get_tempEntry());
		}
		else {
			data.getTempData().insert(iter, data.get_tempEntry());
		}
		return true;
	}
	return false;
}