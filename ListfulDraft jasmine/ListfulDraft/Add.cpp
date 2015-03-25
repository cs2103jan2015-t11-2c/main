#include "Add.h"

bool Add::addContent(DataStore &data, std::string fileName) {
	char choice;

	if (!data.getData().empty() && isDuplicate(data)) {
		//Gives user a choice to add the text in the file despite the duplicate
		std::cout << "Y to ignore/N to cancel" << std::endl;
		std::cin >> choice;
		if (choice == 'N' || choice == 'n') {
			return false;
		}
	}

	data.getData().push_back(data.get_tempEntry());
	data.updateFile(fileName);
	return true;
}

bool Add::isSameDate(DataStore data, int index) {
	if (data.getData()[index].year == data.get_tempEntry().year && data.getData()[index].month == data.get_tempEntry().month && data.getData()[index].day == data.get_tempEntry().day) {
		return true;
	}
	return false;
}

bool Add::isSameTime(DataStore data, int index) {
	int num1 = 0;
	int num2 = 0;

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

	int duration1 = data.getData()[index].endTime - data.getData()[index].startTime;
	int duration2 = data.get_tempEntry().endTime - data.get_tempEntry().startTime;

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

bool Add::isDuplicate(DataStore data) {
	int index = 0;
	//Once a clash is found there is no need to search for further clashes since our program informs the user of any initial clashes already
	for (index = 0; index != data.getData().size(); index++) {
		if (data.getData()[index].subject == data.get_tempEntry().subject) {
			std::cout << "Entry's subject already exists:\n" << data.getDataString(index) << "\n";
			return true;
		}
		if ((isSameDate(data, index)) && (isSameTime(data, index))) {
			std::cout << "Entry's timing clashes with an existing one:\n" << data.getDataString(index) << "\n";
			return true;
		}
	}
	return false;
}