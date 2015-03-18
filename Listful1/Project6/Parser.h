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

		void determineCommand(DataStore &, std::string, int, int &, Add &, Delete &, Display &, Edit &, Clear &);

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