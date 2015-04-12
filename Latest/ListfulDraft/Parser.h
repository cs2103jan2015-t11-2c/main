#ifndef PARSER_H
#define PARSER_H

#include "DataStore.h"
#include "Classes.h"

#define TIME_DATE 1
#define CAT_IMPT 2
#define FRONT 1
#define BACK 2

class Parser {
	private:
		//List of possible extra words before where time/date was found
		std::vector <std::string> extraFront;
		std::vector <std::string> extraFront2;

		//List of possible extra word after where time/date was found
		std::vector <std::string> extraBack;

		//List of possible extra word before/after category/priority was found
		std::vector <std::string> extraCatImpt;

		//List of words hinting at the entry is a deadline type, not timed type
		std::vector <std::string> deadlineWord;

		bool date;
		bool time;
		bool cat;
		bool priority;
		bool complete;

		std::string _information;
		
	public:
		Parser() {};
		void init(std::string);
		
		void separateWord(Classes &, DataStore &, bool &, bool &);
		
		void retrieveDate(Classes &, bool &);
		void retrieveTime(Classes &, bool &);
		void retrievePriority(Classes &);
		void retrieveCategory(Classes &);
		void retrieveCompleteAndRefNo(Classes &, DataStore &);

		bool getMonth(Classes, DataStore &);
		bool getIndex(DataStore &, int &);
		bool getEditInfo(DataStore &, Classes, int &, int &, std::string, std::ostringstream &);
		void assignCat(DataStore &, Classes , int &);
	
		void takeFirstWord(int &, size_t &, std::string &);

		void cutExtraWord(size_t, int, int);
		bool extraWord(std::string, size_t, int, int, int);
		void getFirstWord(Classes, std::string &, std::string , size_t, size_t &);
		void changeToLower(std::string &);
		void removeFrontChar(std::string &);
		void removeBackChar(std::string &);
		void getNextWord (std::string &, size_t &, size_t &);
		void updateStr(std::string &, size_t &, size_t &);
		void joinStr(std::string &, size_t &);
		
		bool &getDate();
		bool &getTime();
		bool &getCat();
		bool &getPriority();
		bool &getComplete();
		//void testParser();
};

#endif