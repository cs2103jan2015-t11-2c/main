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
	std::string fileName = "";
	std::string extName = "";
	std::ostringstream errMsg;
	std::ostringstream floating;
	std::ostringstream scheduled;
	std::ostringstream deadline;

	int i = 0;
	int output = 0;

	Classes listClass;
	Parser parse;
	DataStore data;
	UserMessage outputToUser;
	FileLocation file;

	msg = quoteOfTheDay(outputToUser);
	centralizePrintToUser(msg, errMsg);
	
	do {
		homeScreen(outputToUser);
		if (i == 0) {
			std::cout << errMsg.str() << msg << "\n\n";

			readFileName(fileName, outputToUser);
			extractFileName(fileName, extName, file);

			msg = outputToUser.getFileMsg()[file.openFile(data, parse, listClass)];
			std::cout << "\n" << getOutputToUser(data, msg, extName, errMsg, floating, scheduled, deadline, outputToUser) << "\n\n";
			
			data.getFileName() = file.getName();
			
			outputCommand(outputToUser);
			std::cout << outputToUser.getProgMsg()[5] << "\n";
		}
		i = 1;
		if (parse.isClearScreen(_userInput)) {
			msg = outputToUser.getFileMsg()[file.openFile(data, parse, listClass)];
			std::cout << getOutputToUser(data, msg, extName, errMsg, floating, scheduled, deadline, outputToUser) << "\n\n";
			
			outputCommand(outputToUser);
			std::cout << outputToUser.getProgMsg()[5] << "\n";
		}
		else if (parse.isHelp(_userInput)) {
			outputCommand(outputToUser);
		}
		else {
			errMsg.str("");
			errMsg.clear();
			floating.str("");
			floating.clear();
			scheduled.str("");
			scheduled.clear();
			deadline.str("");
			deadline.clear();
			output = parse.carryOutCommand(listClass, data, errMsg, floating, scheduled, deadline);
			msg = outputToUser.getCommandMsg()[output];
			if (getOutputToUser(data, msg, extName, errMsg, floating, scheduled, deadline, outputToUser) != "") {
				if (output == 1) {
					std::cout << getOutputToUser(data, msg, extName, errMsg, floating, scheduled, deadline, outputToUser) << "\n";
				}
				else {
					std::cout << getOutputToUser(data, msg, extName, errMsg, floating, scheduled, deadline, outputToUser) << "\n\n";
				}
				if (output < 9 && output != 1) {
					data.getPastActionLog().push_back(getOutputToUser(data, msg, extName, errMsg, floating, scheduled, deadline, outputToUser));
					
					if (data.getPastActionLog().size() > 12) {
						data.getPastActionLog().erase(data.getPastActionLog().begin());
					}
				}
			}
		}
		std::cout << " ";
		getline(std::cin, _userInput);
		parse.init(_userInput);
		system("CLS");
	} while (!parse.isRunProgram());
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

std::string UserInterface::getOutputToUser(DataStore data, std::string msg, std::string extName, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, UserMessage outputToUser) {
	size_t count = std::count(msg.begin(), msg.end(), '%');
	std::ostringstream oss;
	
	if (count > 3) {
		oss << outputToUser.getDisplayMsg()[0] << floating.str() << outputToUser.getDisplayMsg()[1] << scheduled.str() << outputToUser.getDisplayMsg()[2] << deadline.str();
		return oss.str();
	}
	else if (count == 3) {
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
	srand(time(NULL));
	randNum = rand() % outputToUser.getQuote().size();
	return outputToUser.getQuote()[randNum];
}

std::string UserInterface::getCurrentDate() {
	Timing timer;
	time_t t = time(0);   
	struct tm now;
	localtime_s(&now, &t);
	std::ostringstream oss;
	Display show;

	show.printZero(show.countDigit(now.tm_mday), oss, 2);
	oss << (now.tm_mday) << "-";
	show.printZero(show.countDigit(now.tm_mon + 1), oss, 2);
	oss << (now.tm_mon + 1) << "-" << (now.tm_year + 1900);
	return oss.str();
}

void UserInterface::outputCommand(UserMessage outputToUser) {
	std::cout << outputToUser.getProgMsg()[0] << outputToUser.getProgMsg()[1];
}

void UserInterface::homeScreen(UserMessage outputToUser) {
	for (i = 2; i < 5; i++) {
		if (i == 3) {
			sprintf_s(msgToUser, outputToUser.getProgMsg()[i].c_str(), getCurrentDate().c_str());
			std::cout << msgToUser;
		}
		else {
			std::cout << outputToUser.getProgMsg()[i];
		}
	}
	return;
}