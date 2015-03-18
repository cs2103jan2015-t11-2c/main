#include "Parser.h"

void Parser::determineCommand(DataStore &data, std::string fileName, int command, int &fileSize, Add &add, Delete &remove, Display &display, Edit &edit, Clear &deleteFile){
	std::string logInput;
	Log log;
	
	switch (command){
			case 1:{
				getline(std::cin, userInput);
				std::string sub = userContent();
				int ST = startTime();
				int ET = endTime();
				int DD = dateDay();
				int MM = dateMonth();
				int YYYY = dateYear();
				std::string p = userPriority();
				std::string cat =  userCat();

				add.addContent(fileName, fileSize, sub, ST, ET, DD, MM, YYYY, p, cat, data);
				logInput = "User added " + sub;
				log.log(logInput);

				fileSize++;
				break;
				   }
			case 2:{
				std::string displayStr = getDisplay();
				display.displayContent(fileName, data, displayStr, 0);
				break;
				   }
			case 3:{
				int deleteIndex = getDelete();
				remove.deleteContent(fileName, data, deleteIndex);
				fileSize--;
				break;
				   }
			case 4:{
				std::cin >> index;
				std::cin >> command;
				getline(std::cin, userInput);
				int ST = editSTime();
				int ET = editETime();
				int DD = editDay();
				int MM = editMonth();
				int YYYY = editYear();
				std::string p = userPriority();
				std::string cat = userCat();
				if (isDate()) {
					edit.editContent(fileName, data, userInput, index, userInput, editDay(), editMonth(), editYear());
				}
				else if (isTime()) {
					edit.editContent(fileName, data, cat, index, userInput, editSTime(), editETime());
				}
				else {
					edit.editContent(fileName, data, cat, index, userInput);
				}
				break;
				}
			case 5:
				break;
			case 6: {
					deleteFile.clearFile(fileName, data);
				break;
				}
			default:
				std::cout << "Invalid command.\n";
				std::cin >> command;
				break;
		}
}

std::string Parser::userContent(){
	std::string userContent = userInput.substr(0, userInput.find_first_of(".,?!"));
	return userContent;
}

bool Parser::isDate() {
	size_t found;

	found = userInput.find("/");
	if (found != std::string::npos) {
		return true;
	}

	return false;
}

bool Parser::isTime() {
	size_t found;

	found = userInput.find("-");
	if (found != std::string::npos) {
		return true;
	}

	return false;
}

int Parser::getDelete() {
	int deleteStr;
	std::cin >> deleteStr;
	return deleteStr;
}

std::string Parser::getDisplay() {
	std::string displayStr;
	std::cin >> displayStr;
	return displayStr;
}

std::string Parser::getEditCat() {
	std::string cat;
	std::cin >> cat;
	return cat;
}

int Parser::editDay(){
	std::string userDateDay = userInput.substr(0, 2);
	int dateDay = atoi(userDateDay.c_str());
	return dateDay;
}

int Parser::editMonth(){
	std::string userDateMonth = userInput.substr(3, 2);
	int dateMonth = atoi(userDateMonth.c_str());
	return dateMonth;
}

int Parser::editYear(){
	std::string userDateYear = userInput.substr(6, 4);
	int dateYear = atoi(userDateYear.c_str());
	
	return dateYear;
}

int Parser::editSTime(){
	std::string userStartTime;
	int startTime;

	userStartTime = userInput.substr(0, 4);
	startTime = atoi(userStartTime.c_str());
	
	return startTime;
}

int Parser::editETime(){
	std::string userEndTime;
	int endTime;

	userEndTime = userInput.substr(userTime().find_first_of("-")+1, 4);
	endTime = endTime = atoi(userEndTime.c_str());

	return endTime;
}

std::string Parser::userDate(){
	std::string userDate = userInput.substr(userInput.find_first_of(".,?!")+2,10);

	return userDate;
}

int Parser::dateDay(){
	std::string userDateDay = userDate().substr(0, 2);
	int dateDay = atoi(userDateDay.c_str());
	return dateDay;
}

int Parser::dateMonth(){
	std::string userDateMonth = userDate().substr(3, 2);
	int dateMonth = atoi(userDateMonth.c_str());
	return dateMonth;
}

int Parser::dateYear(){
	std::string userDateYear = userDate().substr(6, 4);
	int dateYear = atoi(userDateYear.c_str());
	return dateYear;
}

std::string Parser::userTime(){
	std::string userTime = userInput.substr(userInput.find_first_of(".,?!")+14, 9);

	return userTime;
}

int Parser::startTime(){
	std::string userStartTime;
	int startTime;

	userStartTime = userTime().substr(0, 4);
	startTime = atoi(userStartTime.c_str());
	return startTime;
}

int Parser::endTime(){
	std::string userEndTime;
	int endTime;

	userEndTime = userTime().substr(userTime().find_first_of("-")+1, 4);
	endTime = endTime = atoi(userEndTime.c_str());
	return endTime;
}

std::string Parser::userCat(){
	std::string userCat = userInput.substr(userInput.find_last_of(" ")+1, userInput.size());

	return userCat;
}

std::string Parser::userPriority(){
//	int lengthPriority = (userInput.size() - userInput.find_first_of(".,?!")-25) - (userInput.size()- userInput.find_last_of(","));
	int a = userInput.size() - userInput.find_first_of(".,?!")-25;
	int b = userInput.size()- userInput.find_last_of(",");
	std::string userPriority = userInput.substr(userInput.find_first_of(".,?!")+25, a-b);

	return userPriority;
}



/*void Parser::testParser(){
	std::string text = getUserInput();
	std::cout << "Day = " << dateDay(userDate(text)) << std::endl;
	std::cout << "month = " << dateMonth(userDate(text)) << std::endl;
	std::cout << "year = " << dateYear(userDate(text)) << std::endl;
	std::cout << "user content = " << userContent(text) << std::endl;
	std::cout << "user date = " << userDate(text) << std::endl;
	std::cout << "user time = " << userTime(text) << std::endl;
	std::cout << "user priority = " << userPriority(text) << std::endl;
	std::cout << "start time = " << startTime(userTime(text)) << std::endl;
	std::cout << "end time = " << endTime(userTime(text)) << std::endl;
}*/