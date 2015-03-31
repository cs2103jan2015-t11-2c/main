#ifndef PARSER_H
#define PARSER_H

#include "DataStore.h"
#include "Classes.h"

class Parser {
	private:
		enum commandType {
			ADD, DISPLAY, EDIT, REMOVE, CLEAR, EXIT, SORT, SEARCH, UNDO, REDO, INVALID
		};

		enum subCategory {
			DATE, SUBJECT, TIME, PRIORITY, CATEGORY, INVALIDSORT, INVALIDEDIT
		};

		int TIME_DATE;
		int CAT_IMPT;
		int FRONT;
		int BACK;

		bool date;
		bool time;
		bool cat;
		bool priority;
		
		int _day;
		int _month;
		int _year;
		int _sTime;
		int _eTime;
		std::string _cat;
		std::string _priority;
		std::string _userInput;
		std::string _information;
		bool _isEnd;
		
	public:
		Parser() {};
		
		void init(std::string);
		bool isRunProgram();
		bool isClearScreen(std::string);
		int determineCommand();
		int carryOutCommand(Classes &, DataStore &);
		int determineCategory();

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

		int &getDay();
		int &getMonth();
		int &getYear();
		int &getSTime();
		int &getETime();
		std::string &getCat();
		std::string &getPriority();

		int determineEditCategory(std::string category);
};

#endif