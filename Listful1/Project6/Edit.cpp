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

void Edit::editFunction(std::string &fileName, DataStore &data, std::string command, std::string userInput, int index){
	if (data.getDataBaseSize() == 0) {
		std::cout << "File is currently empty.\n";
		return;
	}
	category = determineCategory(command);
	switch (category) {
		case SUBJECT:{
			data.editSubject(userInput, index-1);
			std::cout << "Subject edited!" << std::endl;
			break;
		             }
		case TIME:{
			std::string userStartTime;
			int startTime;
			std::string userEndTime;
			int endTime;
			userStartTime = userInput.substr(1, 5);
			startTime = atoi(userStartTime.c_str());
			userEndTime = userInput.substr(userInput.find_first_of("-")+1, 4);
			endTime = endTime = atoi(userEndTime.c_str());

			data.editTime(startTime, endTime, index-1);
			std::cout << "Time edited!" << std::endl;
			break;
		          }
		case DATE:{
			std::string userDateDay = userInput.substr(1, 3);
			int dateDay = atoi(userDateDay.c_str());
			std::string userDateMonth = userInput.substr(4, 3);
			int dateMonth = atoi(userDateMonth.c_str());
			std::string userDateYear = userInput.substr(7, 5);
			int dateYear = atoi(userDateYear.c_str());

			data.editDate(dateDay, dateMonth, dateYear, index-1);
			std::cout << "Date edited!" << std::endl;
			break;
		          }
		case IMPT:{
			
			break;
				 }
		case CATEGORY:{
			
			break;
					  }
		default:
			std::cout << "Edit command is invalid.\n";
			return;

}
}
	/*
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
*/
