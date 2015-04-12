#include "UserInterface.h"

void UserInterface::runProgram() {
	std::string msg = "";
	std::string quote = "";
	std::string extName = "";
	_userInput = "";

	int i = 0;
	int output = 0;
	bool isReminder = false;
	bool isOver = false;
	size_t found = 0;

	quote = quoteOfTheDay(outputToUser);

	while (parseF.isRunProgram()) {
		clearData(data, errMsg, floating, scheduled, deadline);
		homeScreen(outputToUser, listClass, quote);
		isReminder = false;
		isOver = false;

		found = _userInput.find_first_of(" ");

		if (i == 0 || _userInput == "save" || _userInput == "save file") {
			data.getData().clear();
			startUpScreen(data, listClass, file, parseF, msg, extName, outputToUser, errMsg, floating, scheduled, deadline, isReminder, isOver);
		}/*
		//To save in a different location
		else if (found != std::string::npos && _userInput.substr(0, found) == "save") {
			
		}*/

		if (_userInput == "remind" || _userInput == "reminder" || _userInput == "due") {
			showReminder(data, listClass, msg, floating, scheduled, deadline, outputToUser);
		}
		else if (_userInput == "over" || _userInput == "overdue") {
			showOverDue(data, listClass, msg, floating, scheduled, deadline, outputToUser);
		}
		else if (i == 1) {
			output = parseF.carryOutCommand(listClass, data, errMsg, floating, scheduled, deadline);
			
			if (output == (listClass.commandType::EXIT + 1)) {
				errMsg << " [" << file.getName() << "]\n\n ";
			}

			msg = outputToUser.getCommandMsg()[output];
			getOutputToUser(output, data, msg, extName, errMsg, floating, scheduled, deadline, outputToUser, isReminder, isOver, listClass);
		}
		i = 1;
		defaultScreen(listClass, outputToUser, parseF);
	}
	return;
}



void UserInterface::clearData(DataStore &data, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	errMsg.str("");
	errMsg.clear();
	floating.str("");
	floating.clear();
	scheduled.str("");
	scheduled.clear();
	deadline.str("");
	deadline.clear();
	data.get_tempEntry() = data.get_emptyEntry();
	return;
}

void UserInterface::getStringToDisplay(std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, UserMessage outputToUser, Classes listClass) {
	if (floating.str() != "") {
		listClass.search.setColour(6);
		std::cout << "\n"  << outputToUser.getDisplayMsg()[0];
		listClass.search.setColour(7);
		std::cout << floating.str();
	}
	if (scheduled.str() != "") {
		listClass.search.setColour(6);
		std::cout << "\n" << outputToUser.getDisplayMsg()[1];
		listClass.search.setColour(7);
		std::cout << scheduled.str();
	}
	if (deadline.str() != "") {
		listClass.search.setColour(6);
		std::cout << "\n" << outputToUser.getDisplayMsg()[2];
		listClass.search.setColour(7);
		std::cout << deadline.str();
	}
	return;
}

void UserInterface::getOutputToUser(int output, DataStore &data, std::string msg, std::string extName, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, UserMessage outputToUser, bool isReminder, bool isOver, Classes listClass) {
	size_t count = std::count(msg.begin(), msg.end(), '%');
	std::ostringstream oss;
	std::string cutOff = "";
	bool isFinal = false;

	if (count > 3 || output == 22) {
		remindAndDueHeader(isReminder, isOver, floating, scheduled, deadline, listClass, outputToUser, count, oss, msg);
		if (!isOver && !isReminder && msg != outputToUser.getCommandMsg()[1] && output != 22) {
			std::ostringstream empty;
			data.clearData(empty, empty, empty);
			sprintf_s(msgToUser, msg.c_str(), extName.c_str(), data.get_tempEntry().subject.c_str(), errMsg.str().c_str(), empty.str().c_str());
			oss << msgToUser;
			if (output != 8 && output != 9) {
				oss << "\n";
			}
			std::cout << oss.str();
		}
		getStringToDisplay(floating, scheduled, deadline, outputToUser, listClass);

		//To record the previous changes
		if (output < 8 && output != 1) {
			data.savePrevAction(oss.str());
		}
		return;
	}
	else if (count == 2) {
		sprintf_s(msgToUser, msg.c_str(), extName.c_str(), errMsg.str().c_str());
		if (output < 8 && output != 1) {
			data.savePrevAction(msgToUser);
		}
		std::cout << "\n" << msgToUser;
		return;
	}
	else if (count == 1) {
		sprintf_s(msgToUser, msg.c_str(), extName.c_str());
		if (output < 8 && output != 1) {
			data.savePrevAction(msgToUser);
		}
		std::cout << "\n" << msgToUser;
		return;
	}
	std::cout << "\n" << msg << "\n";
	return;
}




void UserInterface::readFileName(std::string &fileName, UserMessage outputToUser) {
	std::cout << outputToUser.getProgMsg()[6];
	
	//If user does not key in .txt
	getline(std::cin, fileName);
	size_t found = fileName.find(".txt");
	if (found == std::string::npos) {
		fileName = fileName + ".txt";
	}
	return;
}

void UserInterface::extractFileName(std::string &fileName, std::string &name, FileLocation &file) {
	size_t found = fileName.find_last_of("\\");
	
	if (found == std::string::npos) {
		name = fileName;
		fileName = getPath() + "\\" + fileName;
	}
	else {
		name = fileName.substr(found + 1);
	}
	file.getName() = fileName; 
	return;
}

//If user does not key in directory path
std::string UserInterface::getPath() {
    char buffer[MAX_PATH];
    
	GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}



void UserInterface::remindAndDueHeader(bool isReminder, bool isOver, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, Classes listClass, UserMessage outputToUser, int count, std::ostringstream &oss, std::string msg) {
		if (isReminder && !isOver && (floating.str() != "" || scheduled.str() != "" || deadline.str() != "")) {
			count = msg.find_first_of("%");
			oss << msg.substr(0, count);
			listClass.search.setColour(14);
			std::cout << "\n"  << oss.str();
		}
		else if (isOver && !isReminder && (floating.str() != "" || scheduled.str() != "" || deadline.str() != "")) {
			count = msg.find_first_of("%");
			oss << msg.substr(0, count);
			listClass.search.setColour(12);
			std::cout << oss.str();
		}
		else if (isReminder) {
			oss << outputToUser.getFileMsg()[3] << "\n";
			listClass.search.setColour(14);
			std::cout << "\n"  << oss.str();
			listClass.search.setColour(7);
		}
		else if (isOver) {
			oss << outputToUser.getFileMsg()[5] << "\n";
			listClass.search.setColour(12);
			std::cout << oss.str();
			listClass.search.setColour(7);
		}
		return;
}

void UserInterface::showOverDue(DataStore data, Classes &listClass, std::string &msg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, UserMessage outputToUser) {
	clearData(data, floating, floating, scheduled, deadline);
	bool isReminder = false;
	bool isOver = true;
	listClass.search.getOverDue(data, floating, scheduled, deadline, errMsg);
	msg = outputToUser.getFileMsg()[4];
	getOutputToUser(10, data, msg, msg, floating, floating, scheduled, deadline, outputToUser, isReminder, isOver, listClass);
	listClass.search.setColour(7);
	return;
}

void UserInterface::showReminder(DataStore data, Classes &listClass, std::string &msg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, UserMessage outputToUser) {
	clearData(data, floating, floating, scheduled, deadline);
	bool isReminder = true;
	bool isOver = false;
	listClass.search.getReminder(data, floating, scheduled, deadline, errMsg);
	msg = outputToUser.getFileMsg()[2];
	getOutputToUser(10, data, msg, msg, floating, floating, scheduled, deadline, outputToUser, isReminder, isOver, listClass);
	listClass.search.setColour(7);
	return;
}



void UserInterface::outputCommand(UserMessage outputToUser, Classes listClass) {
	std::cout << outputToUser.getProgMsg()[0];
	listClass.search.setColour(6);
	std::cout << outputToUser.getProgMsg()[1];
	listClass.search.setColour(7);
}

void UserInterface::defaultScreen(Classes listClass, UserMessage outputToUser, ParserFacade &parseF) {
	listClass.search.setColour(6);
	std::cout << "\n" << outputToUser.getProgMsg()[1] << " ";
	listClass.search.setColour(7);
	getline(std::cin, _userInput);
	parseF.init(_userInput);
		
	if (parseF.isHelp(_userInput)) {
		outputCommand(outputToUser, listClass);
		std::cout << " ";
		getline(std::cin, _userInput);
		parseF.init(_userInput);
	}
	system("CLS");
	return;
}

void UserInterface::startUpScreen(DataStore &data, Classes &listClass, FileLocation &file, ParserFacade &parseF, std::string &msg, std::string &extName, UserMessage outputToUser, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, bool isReminder, bool isOver) {
	std::string fileName = "";

	outputCommand(outputToUser, listClass);
	std::cout << outputToUser.getProgMsg()[5] << std::endl;

	readFileName(fileName, outputToUser);
	extractFileName(fileName, extName, file);
	msg = outputToUser.getFileMsg()[file.openFile(data, parseF, listClass)];

	//If the user did not enter any location, update fileName to to last access location
	extractFileName(file.getName(), extName, file);

	getOutputToUser(10, data, msg, extName, errMsg, floating, scheduled, deadline, outputToUser, isReminder, isOver, listClass);
	std::cout << "\n\n";
	data.init(file.getName());

	showOverDue(data, listClass, msg, floating, scheduled, deadline, outputToUser);
	showReminder(data, listClass, msg, floating, scheduled, deadline, outputToUser);
	return;
}

void UserInterface::homeScreen(UserMessage outputToUser, Classes &listClass, std::string quote) {
	listClass.search.setColour(7);
	for (i = 2; i < 5; i++) {
		if (i == 3) {
			sprintf_s(msgToUser, outputToUser.getProgMsg()[i].c_str(), getCurrent(outputToUser, 1).c_str());
			std::cout << msgToUser;
		}
		else if (i%2 == 0) {
			listClass.search.setColour(6);
			std::cout << outputToUser.getProgMsg()[i];
			listClass.search.setColour(7);
		}
		else {
			std::cout << outputToUser.getProgMsg()[i];
		}
	}
	listClass.search.setColour(3);
	std::cout << quote << "\n";
	listClass.search.setColour(15);
	sprintf_s(msgToUser, outputToUser.getTime().c_str(), getCurrent(outputToUser).c_str());
	std::cout << msgToUser;
	listClass.search.setColour(7);
	return;
}

std::string UserInterface::quoteOfTheDay(UserMessage outputToUser) {
	int randNum = 0;
	std::ostringstream printSpace;

	srand(time(NULL));
	randNum = rand() % outputToUser.getQuote().size();
	centralizePrintToUser(outputToUser.getQuote()[randNum], printSpace);
	return (printSpace.str() + outputToUser.getQuote()[randNum]);
}

std::string UserInterface::getCurrent(UserMessage outputToUser, int dateOrTime) {
	Timing timer;
	time_t t = time(0);   
	struct tm now;
	localtime_s(&now, &t);
	std::ostringstream oss;
	Search search;
	
	if (dateOrTime == 1) {
		search.printZero(search.countDigit(now.tm_mday), oss, 2);
		oss << (now.tm_mday) << "-";
		search.printZero(search.countDigit(now.tm_mon + 1), oss, 2);
		oss << (now.tm_mon + 1) << "-" << (now.tm_year + 1900);
	}
	else {
		search.printZero(search.countDigit(now.tm_hour), oss, 2);
		oss << (now.tm_hour) << ":";
		search.printZero(search.countDigit(now.tm_min), oss, 2);
		oss << (now.tm_min);
	}
	return oss.str();
}

void UserInterface::centralizePrintToUser(std::string text, std::ostringstream &space) {
	space.str("");
	space.clear();

	for (int i = 0; i < (80 - text.size())/2; i++) {
		space << " ";
	}
	return;
}