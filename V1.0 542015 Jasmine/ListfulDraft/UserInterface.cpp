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
	std::string extName = "";
	std::ostringstream errMsg;
	std::string fileName = "";

	Classes listClass;
	Parser parse;
	DataStore data;
	UserMessage outputToUser;
	FileLocation file;

	homeScreen(outputToUser);

	//If user does not key in .txt
	getline(std::cin, fileName);
	size_t found = fileName.find(".txt");
	if (found == std::string::npos) {
		fileName = fileName + ".txt";
	}

	extractFileName(fileName, extName);
	file.getName() = fileName;
	msg = outputToUser.getFileMsg()[file.openFile(data, parse, listClass)];
	std::cout << getOutputToUser(data, msg, extName, errMsg) << "\n\n";
	data.init(file.getName());
	do {
		userAction(outputToUser);
		getline(std::cin, _userInput);
		parse.init(_userInput);
		
		if (parse.isClearScreen(_userInput)) {
			std::cout << outputToUser.getClearScreen();
			homeScreen(outputToUser);
		}
		else if (parse.isHelp(_userInput)) {
			outputCommand(outputToUser);
		}
		else {
			errMsg.str("");
			errMsg.clear();

			msg = outputToUser.getCommandMsg()[parse.carryOutCommand(listClass, data, errMsg)];
			std::cout << getOutputToUser(data, msg, extName, errMsg) << "\n\n";
		}
	} while (!parse.isRunProgram());
	return;
}

std::string UserInterface::getOutputToUser(DataStore data, std::string msg, std::string extName, std::ostringstream &errMsg) {
	size_t count = std::count(msg.begin(), msg.end(), '%');

	if (count == 3) {
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

void UserInterface::extractFileName(std::string &fileName, std::string &name) {
	size_t found = fileName.find_last_of("\\");
	if (found == std::string::npos) {
		name = fileName;
		fileName = getPath() + "\\" + fileName;
	}
	else {
		name = fileName.substr(found + 1);
	}
	return;
}

//If user does not key in directory path
std::string UserInterface::getPath() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

void UserInterface::userAction(UserMessage outputToUser) {
	std::cout << outputToUser.getProgMsg()[7];
}

std::string UserInterface::quoteOfTheDay(UserMessage outputToUser) {
	int randNum = 0;
	srand(time(NULL));
	randNum = rand() % outputToUser.getQuote().size();
	return outputToUser.getQuote()[randNum];
}

void UserInterface::outputCommand(UserMessage outputToUser) {
	std::cout << outputToUser.getProgMsg()[0] << outputToUser.getProgMsg()[1];
}

void UserInterface::homeScreen(UserMessage outputToUser) {
	std::ostringstream printSpace;
	std::string quote = "";

	for (i = 2; i < 7; i++) {
		if (i == 5) {
			quote = quoteOfTheDay(outputToUser);
			centralizePrintToUser(quote, printSpace);
			std::cout << printSpace.str() << (quote + "\n\n");
			outputCommand(outputToUser);
			std::cout << (outputToUser.getProgMsg()[i] + "\n");
		}
		else {
			std::cout << outputToUser.getProgMsg()[i];
		}
	}
	return;
}