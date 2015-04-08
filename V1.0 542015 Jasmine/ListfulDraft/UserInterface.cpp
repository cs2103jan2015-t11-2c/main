#include "UserInterface.h"

void UserInterface::centralizePrintToUser(std::string text, std::ostringstream &space) {
	space.str("");
	space.clear();

	for (int i = 0; i < (80 - text.size())/2; i++) {
		space << " ";
	}
	return;
}

void UserInterface::runProgram() {
	std::string msg = "";
	std::string quote = "";
	std::string extName = "";
	std::ostringstream errMsg;
	std::ostringstream floating;
	std::ostringstream scheduled;
	std::ostringstream deadline;

	int i = 0;
	int output = 0;
	bool isReminder = false;

	Classes listClass;
	Parser parse;
	DataStore data;
	UserMessage outputToUser;
	FileLocation file;

	quote = quoteOfTheDay(outputToUser);

	 while (!parse.isRunProgram()) {
		homeScreen(outputToUser, listClass, quote);
		isReminder = false;
		clearData(data, errMsg, floating, scheduled, deadline);

		if (i == 0) {
			startUpScreen(data, listClass, file, parse, msg, extName, outputToUser, errMsg, floating, scheduled, deadline, isReminder);
		}
		i = 1;

		if (_userInput == "remind" || _userInput == "reminder") {
			isReminder = true;
			showReminder(data, listClass, msg, floating, scheduled, deadline, outputToUser, isReminder);
		}
		else {
			output = parse.carryOutCommand(listClass, data, errMsg, floating, scheduled, deadline);
			
			if (output == listClass.commandType::EXIT) {
				errMsg << " [" << file.getName() << "]\n\n ";
			}
			
			msg = outputToUser.getCommandMsg()[output];
			if (getOutputToUser(data, msg, extName, errMsg, floating, scheduled, deadline, outputToUser, isReminder) != "") {
				determineOutput(data, getOutputToUser(data, msg, extName, errMsg, floating, scheduled, deadline, outputToUser, isReminder), output);
			}
			
			if (output == (listClass.commandType::REMOVE + 15)) {
				determineOutput(data, getOutputToUser(data, msg, extName, errMsg, floating, scheduled, deadline, outputToUser, isReminder), output);
				getline(std::cin, _userInput);
				if (_userInput != "") {
					if (listClass.remove.deleteMore(data, _userInput, errMsg)) {
						std::cout << "\n" << errMsg << "\n\n";
					}
					else {
						std::cout << "\n" << errMsg << "\n\n";
					}
				}
			}
			std::cout << outputToUser.getProgMsg()[1] << " ";
			getline(std::cin, _userInput);
			parse.init(_userInput);
			
	std::cout << _userInput << std::endl;
			if (parse.isHelp(_userInput)) {
				outputCommand(outputToUser);
				std::cout << " ";
				getline(std::cin, _userInput);
				parse.init(_userInput);
			}
			system("CLS");
		}
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

void UserInterface::determineOutput(DataStore &data, std::string msg, int output) {
	std::cout << msg << "\n";
	if (output != 1) {
		std::cout << "\n";
	}
	if (output < 7 && output != 1) {
		data.savePrevAction(msg);
	}
	return;
}

void UserInterface::startUpScreen(DataStore &data, Classes &listClass, FileLocation &file, Parser &parse, std::string &msg, std::string &extName, UserMessage outputToUser, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, bool isReminder) {
	std::string fileName = "";

	outputCommand(outputToUser);
	std::cout << outputToUser.getProgMsg()[5] << "\n";

	readFileName(fileName, outputToUser);
	extractFileName(fileName, extName, file);

	msg = outputToUser.getFileMsg()[file.openFile(data, parse, listClass)];
	std::cout << "\n" << getOutputToUser(data, msg, extName, errMsg, floating, scheduled, deadline, outputToUser, isReminder) << "\n\n";
			
	data.getFileName() = file.getName();
			
	isReminder = true;
	showReminder(data, listClass, msg, floating, scheduled, deadline, outputToUser, isReminder);
	return;
}

void UserInterface::showReminder(DataStore data, Classes &listClass, std::string &msg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, UserMessage outputToUser, bool isReminder) {
	msg = outputToUser.getFileMsg()[2];
	listClass.display.getReminder(data, floating, scheduled, deadline);
	
	if (getOutputToUser(data, msg, msg, floating, floating, scheduled, deadline, outputToUser, isReminder) != "") {
		listClass.display.setColour(12);
		std::cout << getOutputToUser(data, msg, msg, floating, floating, scheduled, deadline, outputToUser, isReminder) << "\n";
		listClass.display.setColour(7);
	}
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

std::string UserInterface::getOutputToUser(DataStore data, std::string msg, std::string extName, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, UserMessage outputToUser, bool isReminder) {
	size_t count = std::count(msg.begin(), msg.end(), '%');
	std::ostringstream oss;
	std::string cutOff = "";
	
	if (count > 3) {
		if (isReminder && (floating.str() != "" || scheduled.str() != "" || deadline.str() != "")) {
			count = msg.find_first_of("%");
			oss << msg.substr(0, count) << "\n";
		}
		else if (isReminder) {
			oss << outputToUser.getFileMsg()[3] << "\n";
			return oss.str();
		}

		if (floating.str() != "" && scheduled.str() != "" && deadline.str() != "") {
			oss << outputToUser.getDisplayMsg()[0] << floating.str() << "\n\n" << outputToUser.getDisplayMsg()[1] << scheduled.str() << "\n\n" << outputToUser.getDisplayMsg()[2] << deadline.str();
		}
		else if (floating.str() != "" && scheduled.str() == "" && deadline.str() != "") {
			oss << outputToUser.getDisplayMsg()[0] << floating.str() << "\n\n" << outputToUser.getDisplayMsg()[2] << deadline.str();
		}
		else if (floating.str() != "" && scheduled.str() != "" && deadline.str() == "") {
			oss << outputToUser.getDisplayMsg()[0] << floating.str() << "\n\n" << outputToUser.getDisplayMsg()[1] << scheduled.str();
		}
		else if (floating.str() == "" && scheduled.str() != "" && deadline.str() != "") {
			oss << outputToUser.getDisplayMsg()[1] << scheduled.str() << "\n\n" << outputToUser.getDisplayMsg()[2] << deadline.str();
		}
		else if (floating.str() != "" && scheduled.str() == "" && deadline.str() == "") {
			oss << outputToUser.getDisplayMsg()[0] << floating.str();
		}
		else if (floating.str() == "" && scheduled.str() != "" && deadline.str() == "") {
			oss << outputToUser.getDisplayMsg()[1] << scheduled.str();
		}
		else if (floating.str() == "" && scheduled.str() == "" && deadline.str() != "") {
			oss << outputToUser.getDisplayMsg()[2] << deadline.str();
		}
		return oss.str();
	}
	else if (count == 3) {
		data.get_tempEntry().subject = " \"" + data.get_tempEntry().subject + "\"";
		sprintf_s(msgToUser, msg.c_str(), extName.c_str(), data.get_tempEntry().subject.c_str(), errMsg.str().c_str());
		return msgToUser;
	}
	else if (count == 2) {
		sprintf_s(msgToUser, msg.c_str(), extName.c_str(), errMsg.str().c_str());
		return msgToUser;
	}
	else if (count == 1) {
		sprintf_s(msgToUser, msg.c_str(), extName.c_str());
		return msgToUser;
	}
	return msg;
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
	Display show;
	
	if (dateOrTime == 1) {
		show.printZero(show.countDigit(now.tm_mday), oss, 2);
		oss << (now.tm_mday) << "-";
		show.printZero(show.countDigit(now.tm_mon + 1), oss, 2);
		oss << (now.tm_mon + 1) << "-" << (now.tm_year + 1900);
	}
	else {
		show.printZero(show.countDigit(now.tm_hour), oss, 2);
		oss << (now.tm_hour) << ":";
		show.printZero(show.countDigit(now.tm_min), oss, 2);
		oss << (now.tm_min);
	}
	return oss.str();
}

void UserInterface::outputCommand(UserMessage outputToUser) {
	std::cout << outputToUser.getProgMsg()[0] << outputToUser.getProgMsg()[1];
}

void UserInterface::homeScreen(UserMessage outputToUser, Classes &listClass, std::string quote) {
	listClass.display.setColour(7);
	for (i = 2; i < 5; i++) {
		if (i == 3) {
			sprintf_s(msgToUser, outputToUser.getProgMsg()[i].c_str(), getCurrent(outputToUser, 1).c_str());
			std::cout << msgToUser;
		}
		else {
			std::cout << outputToUser.getProgMsg()[i];
		}
	}
	
	listClass.display.setColour(3);
	std::cout << quote << "\n";

	listClass.display.setColour(15);
	sprintf_s(msgToUser, outputToUser.getTime().c_str(), getCurrent(outputToUser).c_str());
	std::cout << msgToUser << "\n";

	listClass.display.setColour(7);
	return;
}