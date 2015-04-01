#ifndef PARSER_H
#define PARSER_H

#include "DataStore.h"
#include "Classes.h"

class Parser {
	private:
		enum commandType {
			ADD, DISPLAY, REMOVE, CLEAR, EDIT, SORT, SEARCH, UNDO, REDO, INVALID, EXIT
		};

		enum subCategory {
			DATE, SUBJECT, TIME, PRIORITY, CATEGORY, INVALIDCAT
		};

		std::vector <std::string> extra;
		std::vector <std::string> extraBack;
		std::vector <std::string> extraCAT_IMPT;

		int TIME_DATE;
		int CAT_IMPT;
		int FRONT;
		int BACK;

		bool date;
		bool time;
		bool cat;
		bool priority;
		
		std::string _userInput;
		std::string _information;
		bool _isEnd;
		
	public:
		Parser() {};
		
		void init(std::string);
		bool isRunProgram();
		bool isClearScreen(std::string);
		int determineCommand();
		int carryOutCommand(Classes &, DataStore &, std::ostringstream &);
		int determineCategory(std::string);

		void separateWord(Classes &, DataStore &);
		void retrieveDate(Classes &);
		void retrieveTime(Classes &);
		void retrievePriority(Classes &);
		void retrieveCategory(Classes &);
		void cutExtraWord(size_t, int, int);
		bool extraWord(std::string, size_t, int, int);

		void changeToLower(std::string &);
		void removeFrontChar(std::string &str);
		void removeBackChar(std::string &str);
		void getNextWord (std::string &, size_t &, size_t &);
		void updateStr(std::string &, size_t &, size_t &);
		void joinStr(std::string &, size_t &);

		//void testParser();
};

#endif