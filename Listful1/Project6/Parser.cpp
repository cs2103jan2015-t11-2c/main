#include "Parser.h"

Parser::Choice Parser::userCommandAlpha(std::string command){
	Choice enumCommand;	
	if (command == "add"){
		enumCommand = ADD;
	}
	else if (command == "display"){
		enumCommand = DISPLAY;
	}
	else if (command == "delete"){
		enumCommand = DELETE;
	}
	else if (command == "edit"){
		enumCommand = EDIT;
	}
	else if (command == "search"){
		enumCommand = SEARCH;
	}
	else if (command == "clear"){
		enumCommand = CLEAR;
	}
	else if (command == "exit"){
		enumCommand = EXIT;
	}
	return enumCommand;
}

int Parser::userCommandNum(std::string command){
	int commandNumber = atoi(command.c_str());
	return commandNumber;
}


void Parser::determineCommandAlpha(std::string input, Parser::Choice enumCommand){
	switch (enumCommand){
			case ADD:{
//				addFunction(input);		add function will take in user input as an entire string then break it up in add
				break;
				   }
			case DISPLAY:{
//				displayFunction(input);
//				display function will take in user input (if any as user can just type display and 
//				default will be to display tasks TODAY or something) as entire string then process it
				break;
				   }
			case DELETE:{
//				deleteFunction(input);		same idea
				break;
				   }
			case EDIT:{
//				editFunction(input)
				break;
				}
			case SEARCH:{
//				searchFunction(input)
				break;
				}
			case CLEAR: {
//				clearFunction();
				break;
				}
			default:{
				std::cout << "Invalid command.\n";
				std::cin >> command;
				break;
				}
		}
}

void Parser::determineCommandNum(std::string input,int commandNumber){
	switch (commandNumber){
			case 1:{
//				addFunction(input);		add function will take in user input as an entire string then break it up in add
				break;
				   }
			case 2:{
//				displayFunction(input);
//display function will take in user input (if any as user can just type display and default will be to display tasks TODAY or something) as entire string then process it
				break;
				   }
			case 3:{
//				deleteFunction(input);		same idea
				break;
				   }
			case 4:{
//				editFunction(input)
				break;
				}
			case 5:{
//				searchFunction(input)
				break;
				}
			case 6: {
//				clearFunction();
				break;
				}
			default:
				std::cout << "Invalid command.\n";
				std::cin >> command;
				break;
		}
}

//determine the command entered and run the program
<<<<<<< HEAD
void Parser::determineCommand(DataStore &data, std::string fileName, int command, int &fileSize, Add &add, Delete &remove, Display &display, Edit &edit, Clear &deleteFile, Sort &sort){
=======
/*void Parser::determineCommand(DataStore &data, std::string fileName, int command, int &fileSize, Add &add, Delete &remove, Display &display, Edit &edit, Clear &deleteFile){
>>>>>>> 4cf39fe5503bf7a8da74137fa9628ff0060487a6
	switch (command){
			case 1:{
				getline(std::cin, userInput);
				std::string sub = userContent();
				
				assert(!userInput.empty());

				int ST = startTime();
				int ET = endTime();
				int DD = dateDay();
				int MM = dateMonth();
				int YYYY = dateYear();
				std::string p = userPriority();
				std::string cat =  userCat();

				add.addContent(fileName, fileSize, sub, ST, ET, DD, MM, YYYY, p, cat, data);
				fileSize++;
				break;
				   }
			case 2:{
				std::string displayStr = getDisplay();

				assert(!displayStr.empty());

				display.displayContent(fileName, data, displayStr, 0);
				break;
				   }
			case 3:{
				int deleteIndex = getDelete();


				try{
					remove.deleteContent(fileName, data, deleteIndex);
				}
				catch (const char *msg){
					cerr << msg << std::endl;
				}
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
			case 5:{
				string field;
				std::cin >>field;
				sort.sortContent(fileName, data, field);
				break;
				}
			case 6: {
					deleteFile.clearFile(fileName, data);
				break;
				}
			default:
				std::cout << "Invalid command.\n";
				std::cin >> command;
				break;
		}
}*/

//to separate the user content
std::string Parser::userContent(){
	std::string userContent = userInput.substr(0, userInput.find_first_of(".,?!"));
	return userContent;
}

//to check if date is found
bool Parser::isDate() {
	size_t found;

	found = userInput.find("/");
	if (found != std::string::npos) {
		return true;
	}

	return false;
}

// to check time is found
bool Parser::isTime() {
	size_t found;

	found = userInput.find("-");
	if (found != std::string::npos) {
		return true;
	}

	return false;
}

//to get the field to be deleted
int Parser::getDelete() {
	int deleteStr;
	std::cin >> deleteStr;
	return deleteStr;
}

//to get the command for the type of display
std::string Parser::getDisplay() {
	std::string displayStr;
	std::cin >> displayStr;
	return displayStr;
}

//to get the category to edit
std::string Parser::getEditCat() {
	std::string cat;
	std::cin >> cat;
	return cat;
}

//to get the day to be edited and to convert the string to integer form
int Parser::editDay(){
	std::string userDateDay = userInput.substr(0, 2);
	int dateDay = atoi(userDateDay.c_str());
	return dateDay;
}

//to get the month to be edited and to convert the string to integer form
int Parser::editMonth(){
	std::string userDateMonth = userInput.substr(3, 2);
	int dateMonth = atoi(userDateMonth.c_str());
	return dateMonth;
}

//to get the year to be edited and to convert the string to integer form
int Parser::editYear(){
	std::string userDateYear = userInput.substr(6, 4);
	int dateYear = atoi(userDateYear.c_str());
	
	return dateYear;
}

//to get the start time to be edited and to convert the string to integer form
int Parser::editSTime(){
	std::string userStartTime;
	int startTime;

	userStartTime = userInput.substr(0, 4);
	startTime = atoi(userStartTime.c_str());
	
	return startTime;
}

//to get the end time to be edited and to convert the string to integer form
int Parser::editETime(){
	std::string userEndTime;
	int endTime;

	userEndTime = userInput.substr(userTime().find_first_of("-")+1, 4);
	endTime = endTime = atoi(userEndTime.c_str());

	return endTime;
}

//to parse the user date
std::string Parser::userDate(){
	std::string userDate = userInput.substr(userInput.find_first_of(".,?!")+2,10);

	return userDate;
}

//to parse the date and convert it to integer form
int Parser::dateDay(){
	std::string userDateDay = userDate().substr(0, 2);
	int dateDay = atoi(userDateDay.c_str());
	return dateDay;
}

//to parse the month and convert it to integer form
int Parser::dateMonth(){
	std::string userDateMonth = userDate().substr(3, 2);
	int dateMonth = atoi(userDateMonth.c_str());
	return dateMonth;
}

//to parse the year and convert it to integer form
int Parser::dateYear(){
	std::string userDateYear = userDate().substr(6, 4);
	int dateYear = atoi(userDateYear.c_str());
	return dateYear;
}

//to parse the time
std::string Parser::userTime(){
	std::string userTime = userInput.substr(userInput.find_first_of(".,?!")+14, 9);

	return userTime;
}

//to determine the start time of the event
int Parser::startTime(){
	std::string userStartTime;
	int startTime;

	userStartTime = userTime().substr(0, 4);
	startTime = atoi(userStartTime.c_str());
	return startTime;
}

//to determine the end time of the event
int Parser::endTime(){
	std::string userEndTime;
	int endTime;

	userEndTime = userTime().substr(userTime().find_first_of("-")+1, 4);
	endTime = endTime = atoi(userEndTime.c_str());
	return endTime;
}

//to determine the category
std::string Parser::userCat(){
	std::string userCat = userInput.substr(userInput.find_last_of(" ")+1, userInput.size());

	return userCat;
}

// to determine priority
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