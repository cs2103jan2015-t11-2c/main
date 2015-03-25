#include "Add.h"
//to add content
void Add::addContent(std::string &fileName, int &index, std::string subject, int startTime, int endTime, int day, int month, int year, std::string impt, std::string category, DataStore &data) {
	char choice;
	data.entryType(index, subject, startTime, endTime, day, month, year, impt, category); 

	if (!data.getDataBase().empty() && isDuplicate(data)) {			
		//Gives user a choice to add the text in the file despite the duplicate
		std::cout << "Y to ignore/N to cancel" << std::endl;
		std::cin >> choice;
		if (choice == 'N') {
			std::cout << "\n";
			return;
		}
	}

	data.updateDataBase();
	data.updateFile(fileName);
	
	std::cout << "Entry added successfully in " << fileName << std::endl;
	//sprintf_s(messageToUser, MESSAGE_ADD.c_str(), fileName.c_str(), readInLine.c_str());
	//output(messageToUser);
}

//to check if the field added has the same date
bool Add::isSameDate(DataStore &data, int index, int day, int month, int year) {
	if (data.getDataBase()[index].year == year && data.getDataBase()[index].month == month && data.getDataBase()[index].day == day) {
		return true;
	}

	return false;
}

//to check if the time added has the same time
bool Add::isSameTime(DataStore &data, int index, int startTime, int endTime) {
	if ((data.getDataBase()[index].startTime <= startTime) && (data.getDataBase()[index].endTime >= startTime)) {
		return true;
	}
	else if ((data.getDataBase()[index].startTime <= endTime) && (data.getDataBase()[index].endTime >= endTime)) {
		return true;
	}

	return false;
}

// check for clashes in the current database
bool Add::isDuplicate(DataStore &data) {
	
	//Once a clash is found there is no need to search for further clashes since our program informs the user of any initial clashes already
	for (int index = 0; index != data.getDataBaseSize(); index++) {
		if (data.getDataBase()[index].subject == data.getEntry().subject) {
			std::cout << "Entry's subject already exists:\n" << data.getDataString(index) << "\n";
			return true;
		}
		if ((isSameDate(data, index, data.getEntry().day, data.getEntry().month, data.getEntry().year)) && (isSameTime(data, index, data.getEntry().startTime, data.getEntry().endTime))) {
			std::cout << "Entry's timing clashes with an existing one:\n" << data.getDataString(index) << "\n";
			return true;
		}
	}
	
	return false;
}