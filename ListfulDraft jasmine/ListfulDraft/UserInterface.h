#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Parser.h"

class UserInterface {
	private:
		std::vector <std::string> _quotes;

		std::string _userInput;

	public:
		UserInterface() {};

		void printStarRow();
		void centralizePrintToUser(std::string);
		void printToUser(std::string);
		void addQuote();
		std::string quoteOfTheDay();
		void userAction();
		void printSpace(int);
		std::string runProgram(char *[]);
		void homeScreen();
};

#endif