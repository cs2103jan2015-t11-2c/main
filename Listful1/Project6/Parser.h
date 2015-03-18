#ifndef PARSER_H
#define PARSER_H

#include "Add.h"
#include "Clear.h"
#include "DataStore.h"
#include "Delete.h"
#include "Display.h"
#include "Edit.h"
#include "Sort.h"
#include "Log.h"

class Parser {
	private:
		int commandIndex;
		int index;
		std::string userInput;
		std::string command;
		
	public:
		Parser() {};

		int getIndex() {
			std::cin >> index;
			return index;
		};

<<<<<<< HEAD
		void determineCommand(DataStore &, std::string, int, int &, Add &, Delete &, Display &, Edit &, Clear &, Sort &);
=======
//		void determineCommand(DataStore &, std::string, int, int &, Add &, Delete &, Display &, Edit &, Clear &);
		enum Choice {
			ADD, DISPLAY, DELETE, EDIT, SEARCH, CLEAR, EXIT
		};
		
		Parser::Choice userCommandAlpha(std::string command);
		int userCommandNum(std::string command);
		void determineCommandAlpha(std::string input, Parser::Choice enumCommand);
		void determineCommandNum(std::string input, int commandNumber);
>>>>>>> 4cf39fe5503bf7a8da74137fa9628ff0060487a6

		int getDelete();

		std::string getDisplay();

		std::string getEditCat();
		int editDay();
		int editMonth();
		int editYear();
		int editSTime();
		int editETime();
		bool isDate();
		bool isTime();

		//Subject
		std::string userContent();

		//Date
		std::string userDate();
		int dateDay();
		int dateMonth();
		int dateYear();

		//Time
		std::string userTime();
		int startTime();
		int endTime();

		//Impt
		std::string userPriority();

		//Category
		std::string userCat();

		void testParser();
};
#endif