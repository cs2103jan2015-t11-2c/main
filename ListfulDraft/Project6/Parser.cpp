#include "Parser.h"
/*
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
*/
void Parser::determineCommand(DataStore &data, std::string fileName, int command, int &fileSize, Add &add, Delete &remove, Display &display, Edit &edit, Clear &deleteFile, Sort &sort, Search &search){

//void Parser::determineCommand(DataStore &data, std::string fileName, int command, int &fileSize, Add &add, Delete &remove, Display &display, Edit &edit, Clear &deleteFile){

	switch (command){
			case 1:{
				getline(std::cin, userInput);
				std::string sub = userContent();
				
				assert(!sub.empty());
				
				int ST = startTime();
				int ET = endTime();
				int DD = dateDay();
				int MM = dateMonth();
				int YYYY = dateYear();
				std::string p = userPriority();
				std::string cat = userCat();
				
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
				string editCommand;
				std::cin >> index;
				std::cin >> editCommand;
				getline(std::cin, userInput);
					edit.editFunction(fileName, data, editCommand, userInput, index);
				break;
				}
			case 5:{
				std::string keyword, type;
				std::cin >> type;
				getline(std::cin, keyword);
					search.searchFile(fileName, data, keyword, type);
				break;
				}
			case 6: {
					deleteFile.clearFile(fileName, data);
				break;
				}
			case 8: {
				std::string field;
				std::cin >>field;
				sort.sortContent(fileName, data, field);
				break;
				}
			default:
				std::cout << "Invalid command.\n";
				std::cin >> command;
				break;
		}
}

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
	userStartTime = userTime().substr(0, 4);
	
	int ST = atoi(userStartTime.c_str());
	
	return ST;
}

//to determine the end time of the event
int Parser::endTime(){
	std::string userEndTime;

	userEndTime = userTime().substr(userTime().find_first_of("-")+1, 4);
	int ET = atoi(userEndTime.c_str());
	return ET;
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