#include "UserInterface.h"

void UserInterface::centralizePrintToUser(std::string text, std::ostringstream &space) {
	int position = (80-text.size())/2;

	for (int i=0; i < position; i++){
		space << " ";
	}
	return;
}

void UserInterface::runProgram(char *argv[]) {
	char msgToUser[200];
	size_t count = 0;
	std::string msg = "";
	std::ostringstream errMsg;
	std::string fileName = argv[1];
	std::string extName = "";

	Classes listClass;
	Parser parse;
	DataStore data;
	UserMessage outputToUser;
	FileLocation file;

	file.getName() = fileName;
	homeScreen(outputToUser);
	extractFileName(fileName, extName);
	msg = outputToUser.getFileMsg()[file.openFile(data, parse, listClass)];
	sprintf_s(msgToUser, msg.c_str(), extName.c_str());
	std::cout << msgToUser << "\n";
	
	data.init(fileName);

	do {
		userAction(outputToUser);
		getline(std::cin, _userInput);
		parse.init(_userInput);
		
		if (parse.isClearScreen(_userInput)) {
			std::cout << outputToUser.getClearScreen();
			homeScreen(outputToUser);
		}
		else {
			errMsg.str("");
			errMsg.clear();

			msg = outputToUser.getCommandMsg()[parse.carryOutCommand(listClass, data, errMsg)];
			count = std::count(msg.begin(), msg.end(), '%');
			if (count == 3) {
				sprintf_s(msgToUser, msg.c_str(), extName.c_str(), data.get_tempEntry().subject.c_str(), errMsg.str().c_str());
				std::cout << msgToUser << "\n";
			}
			else if (count == 2) {
				sprintf_s(msgToUser, msg.c_str(), extName.c_str(), errMsg.str().c_str());
				std::cout << msgToUser << "\n";
			}
			else if (count == 1) {
				sprintf_s(msgToUser, msg.c_str(), extName.c_str());
				std::cout << msgToUser << "\n";
			}
			else {
				std::cout << msg << "\n";
			}
		}
	} while (!parse.isRunProgram());
	return;
}

void UserInterface::extractFileName(std::string fileName, std::string &name) {
	size_t found = fileName.find_last_of("\\");
	if (found == std::string::npos) {
		name = fileName;
	}
	else {
		name = fileName.substr(found + 1);
	}
	return;
}

void UserInterface::userAction(UserMessage outputToUser) {
	std::ostringstream printSpace;

	centralizePrintToUser(outputToUser.getProgMsg()[3], printSpace);
	std::cout << printSpace.str() << (outputToUser.getProgMsg()[3] + "\n\n") << (outputToUser.getProgMsg()[4] + "\n");
	printSpace.clear();
}

std::string UserInterface::quoteOfTheDay(UserMessage outputToUser) {
	int randNum = 0;
	srand(time(NULL));

	randNum = rand() % outputToUser.getQuote().size();
	return outputToUser.getQuote()[randNum];
}

void UserInterface::homeScreen(UserMessage outputToUser) {
	std::ostringstream printSpace;
	std::string quote = "";

	for (i = 0; i < 4; i++) {
		if (i == 3) {
			quote = quoteOfTheDay(outputToUser);
			centralizePrintToUser(quote, printSpace);
			std::cout << printSpace.str() << (quote + "\n\n");
			printSpace.clear();
		}
		else {
			std::cout << outputToUser.getProgMsg()[i];
		}
	}
	return;
}