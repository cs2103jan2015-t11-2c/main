#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "FileLocation.h"
#include "UserMessage.h"

#define MAX 400

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
		std::string getOutputToUser(DataStore, std::string, std::string, std::ostringstream &);
		void extractFileName(std::string &, std::string &);
		std::string getPath();
		void userAction(UserMessage);
		std::string quoteOfTheDay(UserMessage);
		void outputCommand(UserMessage);
		void homeScreen(UserMessage);
};

#endif