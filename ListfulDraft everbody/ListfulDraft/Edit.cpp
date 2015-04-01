#include "Edit.h"

bool Edit::editContent(DataStore &data, std::string userInput, int index, int category){

	if (data.getData().size() == 0) {
		std::cout << "File is currently empty.\n";
		return false;
	}
	
	switch (category) {
		case DATE:{
			std::string userDateDay = userInput.substr(0, 2);
			int dateDay = atoi(userDateDay.c_str());
			std::string userDateMonth = userInput.substr(3, 2);
			int dateMonth = atoi(userDateMonth.c_str());
			std::string userDateYear = userInput.substr(6, 4);
			int dateYear = atoi(userDateYear.c_str());

			data.getData()[index].day = dateDay;
			data.getData()[index].month = dateMonth;
			data.getData()[index].year = dateYear;
			std::cout << "Date edited!" << std::endl;
			break;
		          }
		case SUBJECT:{
			data.getData()[index].subject= userInput;
			std::cout << "Subject edited!" << std::endl;
			break;
		             }
		case TIME:{
			std::string userStartTime;
			int startTime;
			std::string userEndTime;
			int endTime;
			userStartTime = userInput.substr(0, 4);
			startTime = atoi(userStartTime.c_str());
			userEndTime = userInput.substr(userInput.find_first_of("-")+1, 4);
			endTime = endTime = atoi(userEndTime.c_str());

			data.getData()[index].startTime = startTime;
			data.getData()[index].endTime = endTime;
			std::cout << "Time edited!" << std::endl;
			break;
		          }
		case PRIORITY:{
			data.getData()[index].priority = userInput;
			std::cout << "Priority edited!" << std::endl;
			break;
				 }
		case CATEGORY:{
			data.getData()[index].category = userInput;
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
	