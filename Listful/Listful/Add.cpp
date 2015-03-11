#include "Add.h"
#include "DataStore.h"

Add::Add() {}

void Add::addContent(std::string &fileName, int index, std::string subject, int startTime, int endTime, int day, int month, int year, std::string impt, std::string category, DataStore data) {
	char choice;
	data.entryType(index, subject, startTime, endTime, day, month, year, impt, category); 

	if (data.getDataBase().empty() && isDuplicate(data)) {
			
		//Gives user a choice to add the text in the file despite the duplicate
		std::cin >> choice;
		if (choice == 'n') {
			std::cout << "\n";
			return;
		}
	}

	data.getDataBase().push_back(data.getEntry());
	data.updateFile(fileName);
	
	std::cout << "Entry added successfully in " << fileName;
	//sprintf_s(messageToUser, MESSAGE_ADD.c_str(), fileName.c_str(), readInLine.c_str());
	//output(messageToUser);
}

bool Add::isSameDate(DataStore data, int index, int day, int month, int year) {
	if (data.getDataBase()[index].year == year && data.getDataBase()[index].month == month && data.getDataBase()[index].day == day) {
		return true;
	}

	return false;
}

bool Add::isSameTime(DataStore data, int index, int startTime, int endTime) {
	if ((data.getDataBase()[index].startTime <= startTime) && (data.getDataBase()[index].endTime >= startTime)) {
		return true;
	}
	else if ((data.getDataBase()[index].startTime <= endTime) && (data.getDataBase()[index].endTime >= endTime)) {
		return true;
	}

	return false;
}

bool Add::isDuplicate(DataStore data) {
	
	//Once a clash is found there is no need to search for further clashes since our program informs the user of any initial clashes already
	for (int index = 0; index != data.getDataBase().size(); index++) {
		if (data.getDataBase()[index].subject == data.getEntry().subject) {
			std::cout << "Entry's subject already exists:\n" << data.getDataString(data.getDataIter()) << "\n";
			return true;
		}
		if ((isSameDate(data, index, data.getEntry().day, data.getEntry().month, data.getEntry().year)) && (isSameTime(data, index, data.getEntry().startTime, data.getEntry().endTime))) {
			std::cout << "Entry's timing clashes with an existing one:\n" << data.getDataString(data.getDataIter()) << "\n";
			return true;
		}
	}
	
	return false;
}