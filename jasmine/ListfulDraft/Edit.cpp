#include "Edit.h"

bool Edit::editContent(DataStore &data, std::string userInput, int index){
	if (data.getData().size() == 0) {
		return false;
	}
	
	switch (_category) {
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
			break;
		    }
		case SUBJECT:{
			data.getData()[index].subject= userInput;
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
			break;
		    }
		case PRIORITY:{
			data.getData()[index].priority = userInput;
			break;
			}
		case CATEGORY:{
			data.getData()[index].category = userInput;
			break;
			}
		default:
			return false;
	}
	data.updateFile();
	data.savePrevFile();
	return true;
}

int &Edit::getCat() {
	return _category;
}