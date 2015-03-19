#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Parser.h"

class UserInterface {
	private:
		static const std::string MESSAGE_WELCOME;
		static const std::string MESSAGE_ACTION;

		static const std::string MESSAGE_ADD;
		static const std::string MESSAGE_DELETE;
		static const std::string MESSAGE_CLEAR;
		static const std::string MESSAGE_EDIT;
		static const std::string MESSAGE_SORT;
		static const std::string MESSAGE_SEARCH;
		static const std::string MESSAGE_UNDO;
		static const std::string MESSAGE_REDO;

		static const std::string ERROR_COMMAND;
		static const std::string ERROR_DELETE;
		static const std::string ERROR_ADD;
		static const std::string ERROR_SEARCH;
		static const std::string ERROR_EDIT;
		static const std::string ERROR_SORT;
		static const std::string ERROR_UNDO;
		static const std::string ERROR_REDO;

		static const std::string MESSAGE_EMPTY;

		std::vector <std::string> _quotes;

		std::string _userInput;

		DataStore data;
		Parser parse;
		Add add;
		Display display;
		Delete remove;
		Edit edit;
		Clear clearFile;

	public:
		UserInterface() {};

		void printStarRow();
		void centralizePrintToUser(std::string);
		void printToUser(std::string);
		void addQuote();
		std::string quoteOfTheDay();
		void userAction();
		void runProgram(char *[]);
		void homeScreen();
};

#endif