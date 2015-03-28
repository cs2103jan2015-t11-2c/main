#ifndef PARSER_H
#define PARSER_H

#include "DataStore.h"
#include "Classes.h"

class Parser {
	private:
		enum commandType {
			ADD, DISPLAY, EDIT, REMOVE, CLEAR, EXIT, SORT, SEARCH, UNDO, REDO, INVALID
		};

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
		int carryOutCommand(Classes, DataStore &);

		void separateWord(Classes, DataStore &);
		void retrieveDate(Classes);
		void retrieveTime(Classes);
		void retrievePriority(Classes);
		void retrieveCategory(Classes);
		void getNextWord (std::string &, size_t &, size_t &);
		void updateStr(std::string &, size_t &, size_t &);
		void joinStr(std::string &, size_t &);
		void cutExtraWord(size_t, int, int);
		bool extraWord(std::string, size_t, int, int);
		void changeToLower(std::string &);
		void removeFrontChar(std::string &str);
		void removeBackChar(std::string &str);
		//void testParser();

		int &getDay();
		int &getMonth();
		int &getYear();
		int &getSTime();
		int &getETime();
		std::string &getCat();
		std::string &getPriority();
};

#endif