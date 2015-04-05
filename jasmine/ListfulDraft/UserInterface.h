#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "FileLocation.h"
#include "UserMessage.h"


class UserInterface {
	private:
		std::string _userInput;

		std::string _outputToUser;

		int i;

	public:
		UserInterface() {};

		void centralizePrintToUser(std::string, std::ostringstream &);
		void runProgram(char *[]);
		void extractFileName(std::string, std::string &);
		void userAction(UserMessage);
		std::string quoteOfTheDay(UserMessage);
		void homeScreen(UserMessage);
};

#endif