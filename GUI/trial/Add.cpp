#include "Add.h"

//To add
//If a clash (subject or time and date) is found, it will still add but a warning message will be output
bool Add::addContent(DataStore &data) {
	bool status = true;
	if (!data.getData().empty() && isDuplicate(data)) {
		std::cout << " (undo to remove add)" << std::endl; //put at messages part
		status = false;
	}

	data.getData().push_back(data.get_tempEntry());
	data.updateFile();
	data.savePrevFile();
	return status;
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
	int num1 = 0;
	int num2 = 0;

	//To take note of '12am' since it is considered 0000 so that we can get the correct duration if it is
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
	else if (data.getData()[index].startTime <= data.get_tempEntry().startTime) {
		if ((data.get_tempEntry().startTime - data.getData()[index].startTime) < duration1) {
			return true;
		}
	}
	else if (data.getData()[index].startTime >= data.get_tempEntry().startTime) {
		 if ((data.getData()[index].startTime - data.get_tempEntry().startTime) < duration2) {
			return true;
		 }
	}
	return false;
}

//Outputs warning message if subject or time and date clashes
bool Add::isDuplicate(DataStore data) {
	int index = 0;

	//Once a clash is found there is no need to search for further clashes since our program informs the user of any initial clashes already
	for (index = 0; index != data.getData().size(); index++) {
		if (data.getData()[index].subject == data.get_tempEntry().subject) {
			std::cout << "subject clash ";
			if ((isSameDate(data, index)) && (isSameTime(data, index))) {
			std::cout << "timing clash";
			}
			return true;
		}
		if ((isSameDate(data, index)) && (isSameTime(data, index))) {
			std::cout << "timing clash";
			return true;
		}
	}
	return false;
}