#ifndef PARSER_H
#define PARSER_H

#include "Add.h"
#include "Clear.h"
#include "DataStore.h"
#include "Delete.h"
#include "Display.h"
#include "Edit.h"
#include "Sort.h"
#include "Search.h"

class Parser {
	private:
		enum commandType {
			ADD, DISPLAY, EDIT, DELETE, CLEAR, EXIT, SORT, SEARCH, UNDO, REDO, INVALID
		};

		/*
		int commandIndex;
		int index;
		std::string userInput;
		std::string command;
		*/
		
		std::string _userInput;
		bool _isEnd;
		int _startTime;
		int _endTime;
		int _day;
		int _month;
		int _year;
		std::string _cat;
		std::string _priority;
		std::string _subject;
		
	public:
		Parser();
		Parser(std::string &);

		bool isRunProgram();
		bool isClearScreen();
		int determineCommand();
		void convertLowerCase();
		void carryOutCommand(int);
		void getTime();
		/*int getIndex() {
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

		//void testParser();
		*/
};

#endif