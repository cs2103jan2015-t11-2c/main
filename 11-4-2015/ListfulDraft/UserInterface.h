#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "FileLocation.h"
#include "UserMessage.h"

#define MAX 1000

class UserInterface {
	private:
		std::string _userInput;

		int i;
		char msgToUser[MAX];
		
		Classes listClass;
		ParserFacade parse;
		DataStore data;
		UserMessage outputToUser;
		FileLocation file;
		
		std::ostringstream errMsg;
		std::ostringstream floating;
		std::ostringstream scheduled;
		std::ostringstream deadline;

	public:
		UserInterface() {};

		void centralizePrintToUser(std::string, std::ostringstream &);
		void runProgram();
		void defaultScreen(Classes, UserMessage, ParserFacade &);
		void clearData(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void readFileName(std::string &, UserMessage);
		void showReminder(DataStore, Classes &, std::string &, std::ostringstream &, std::ostringstream &, std::ostringstream &, UserMessage);
		void showOver(DataStore, Classes &, std::string &, std::ostringstream &, std::ostringstream &, std::ostringstream &, UserMessage);
		void remindAndDueHeader(bool, bool, std::ostringstream &, std::ostringstream &, std::ostringstream &, Classes, UserMessage, int, std::ostringstream &, std::string);
		void getStringToDisplay(std::ostringstream &, std::ostringstream &, std::ostringstream &, UserMessage, Classes);
		void getOutputToUser(int, DataStore &, std::string, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, UserMessage, bool, bool, Classes);
		void determineOutput(DataStore &, std::string, int);
		void startUpScreen(DataStore &, Classes &, FileLocation &, ParserFacade &, std::string &, std::string &, UserMessage , std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, bool, bool);
		void extractFileName(std::string &, std::string &, FileLocation &);
		std::string getPath();
		std::string quoteOfTheDay(UserMessage);
		std::string getCurrent(UserMessage, int = 0);
		void outputCommand(UserMessage, Classes);
		void homeScreen(UserMessage, Classes &, std::string);
};

#endif