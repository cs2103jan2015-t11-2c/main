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
		std::string getOutputToUser(DataStore, std::string, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, UserMessage);
		void extractFileName(std::string &, std::string &, FileLocation &);
		std::string getPath();
		std::string quoteOfTheDay(UserMessage);
		std::string getCurrentDate();
		void outputCommand(UserMessage);
		void homeScreen(UserMessage);
};

#endif