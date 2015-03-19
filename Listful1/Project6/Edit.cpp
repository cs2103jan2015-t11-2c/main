#include "Edit.h"

//to determine the category to edit
int Edit::determineCategory(std::string category) {
	if (category == "date") {
		return subCategory::DATE;
	}
	else if (category == "subject") {
		return subCategory::SUBJECT;
	}
	else if (category == "time") {
		return subCategory::TIME;
	}
	else if (category == "impt") {
		return subCategory::IMPT;
	}
	else if (category == "category") {
		return subCategory::CATEGORY;
	}
	else {
		return subCategory::INVALID;
	}
}

//to edit the content
void Edit::editContent(std::string &fileName, DataStore &data, std::string command, int index, std::string newEntry, int newNum1, int newNum2, int newNum3) {
	
	if (data.getDataBaseSize() == 0) {
		std::cout << "File is currently empty.\n";
		return;
	}

	category = determineCategory(command);

	switch (category) {
		case SUBJECT:
			data.getDataIter()[index - 1].subject = newEntry;
			break;

		case TIME:
			data.getDataIter()[index - 1].startTime = newNum1;
			data.getDataIter()[index - 1].endTime = newNum2;
			break;
		
		case DATE:
			data.getDataIter()[index - 1].day = newNum1;
			data.getDataIter()[index - 1].month = newNum2;
			data.getDataIter()[index - 1].year = newNum3;
			break;
		
		case IMPT:
			data.getDataIter()[index - 1].impt = newEntry;
			break;

		case CATEGORY:
			data.getDataIter()[index - 1].category = newEntry;
			break;

		default:
			std::cout << "Edit command is invalid.\n";
			return;
	}

	data.updateFile(fileName);
	std::cout << "Entry " << index << " is successfully edited:\n" << data.getDataString(index-1);
}