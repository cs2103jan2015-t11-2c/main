#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "FileLocation.h"
#include "UserMessage.h"

#define MAX 1000

class UserInterface {
	private:
		std::string _userInput;

		std::string _outputToUser;

		int i;

		char msgToUser[MAX];

	public:
		UserInterface() {};

		void centralizePrintToUser(std::string, std::ostringstream &);
		void runProgram();
		void readFileName(std::string &, UserMessage);
		void showReminder(DataStore, Classes &, std::string &, std::ostringstream &, std::ostringstream &, std::ostringstream &, UserMessage, bool);
		std::string getOutputToUser(DataStore, std::string, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, UserMessage, bool);
		void determineOutput(DataStore &, std::string, int);
		void startUpScreen(DataStore &, Classes &, FileLocation &, Parser &, std::string &, std::string &, UserMessage , std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, bool);
		void extractFileName(std::string &, std::string &, FileLocation &);
		std::string getPath();
		std::string quoteOfTheDay(UserMessage);
		std::string getCurrent(UserMessage, int = 0);
		void outputCommand(UserMessage);
		void homeScreen(UserMessage, Classes &, std::string);
};

#endif