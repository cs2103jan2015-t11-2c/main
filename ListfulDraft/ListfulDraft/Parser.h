#ifndef PARSER_H
#define PARSER_H

#include "DataStore.h"
#include "Classes.h"

class Parser {
	private:
		enum commandType {
			ADD, DISPLAY, EDIT, DELETE, CLEAR, EXIT, SORT, SEARCH, UNDO, REDO, INVALID
		};
	
		std::string _userInput;
		std::string _information;
		bool _isEnd;
		int _sTime;
		int _eTime;
		int _day;
		int _month;
		int _year;
		std::string _cat;
		std::string _priority;
		std::string _subject;
		
	public:
		Parser() {};
		
		void init(std::string);
		bool isRunProgram();
		bool isClearScreen(std::string);
		int determineCommand();
		void carryOutCommand(Classes, DataStore);
		void getNextWord (std::string &, size_t &, size_t &);
		void separateWord(Classes, DataStore);
		void retrieveDate(Classes, DataStore, size_t &);
		void retrieveTime(Classes, DataStore, size_t &);
		void updateStr(std::string &, size_t &, size_t &);
		void joinStr(std::string &, size_t &);

		//void testParser();
};

#endif