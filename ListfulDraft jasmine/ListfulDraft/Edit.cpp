#include "Edit.h"

bool Edit::editContent(DataStore &data, std::string userInput, int index, int category){

	if (data.getData().size() == 0) {
		std::cout << "File is currently empty.\n";
		return false;
	}
	
	switch (category) {
		case DATE:{
			std::string userDateDay = userInput.substr(1, 3);
			int dateDay = atoi(userDateDay.c_str());
			std::string userDateMonth = userInput.substr(4, 3);
			int dateMonth = atoi(userDateMonth.c_str());
			std::string userDateYear = userInput.substr(7, 5);
			int dateYear = atoi(userDateYear.c_str());

			data.getData()[index-1].day = dateDay;
			data.getData()[index-1].month = dateMonth;
			data.getData()[index-1].year = dateYear;
			std::cout << "Date edited!" << std::endl;
			break;
		          }
		case SUBJECT:{
			data.getData()[index-1].subject= userInput;
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

			data.getData()[index-1].startTime = startTime;
			data.getData()[index-1].endTime = endTime;
			std::cout << "Time edited!" << std::endl;
			break;
		          }
		case PRIORITY:{
			data.getData()[index-1].priority = userInput;
			std::cout << "Priority edited!" << std::endl;
			break;
				 }
		case CATEGORY:{
			data.getData()[index-1].category = userInput;
			std::cout << "Category edited!" << std::endl;
			break;
					  }
		default:
			std::cout << "Edit command is invalid.\n";		

	}
		data.updateFile();
		data.savePrevFile();
			return true;
}
	