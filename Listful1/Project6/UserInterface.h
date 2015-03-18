#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Parser.h"

#include <ctime>
#include <cstdlib>


//static const int FILE_INDEX;

class UserInterface {
	private:
		std::vector<std::string> _quotes;

		//stores command from user
		int command; 

		int fileSize;

		static const std::string MESSAGE_WELCOME;
		static const std::string MESSAGE_ACTION;

		static const std::string MESSAGE_ADD;
		static const std::string MESSAGE_DELETE;
		static const std::string MESSAGE_CLEAR;
		static const std::string MESSAGE_EMPTY;
		static const std::string MESSAGE_SORT;

		static const std::string ERROR_COMMAND;
		static const std::string ERROR_DELETE;
		static const std::string ERROR_ADD;
		static const std::string ERROR_SEARCH;

	public:	
		void printStarRow();
		void centralizeOutput(std::string text);
		void runProgram(char *[]);
		void addQuote();
		std::string quoteOfTheDay();
		void userAction();
		void homeScreen();
//		void checkFileCreated(std::string &fileName);
};
#endif
