#ifndef TIME_H
#define TIME_H

#include "DataStore.h"

class Timing {
	private:
		std::vector <std::string> _linkWord;
		std::vector <std::string> _words;
		int _startTime;
		int _endTime;

	public:
		Timing();
	
		void changeToLower(std::string &);
		bool isTimeValid(int);
		void updateStr(std::string &, std::string &, size_t);
		bool extractNum (std::string, int &, int &);
		void updateTime();
		void removeNonTimeChar(std::string &);
		void countWord(std::string, int &);
		bool takeTime(std::string &, int &, bool &);
		void checkAMPM (std::string &, int , int &, bool &, int);
		bool extractTime (std::string &, int &, bool &);
		bool checkStartEnd();

		int &getStart();
		int &getEnd();
};

#endif