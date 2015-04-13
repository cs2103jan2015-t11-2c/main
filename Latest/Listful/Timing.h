#ifndef TIMING_H
#define TIMING_H

#include "DataStore.h"

class Timing {
	private:
		std::vector <std::string> _linkWord;
		int _startTime;
		int _endTime;

	public:
		Timing();
		
		bool checkForTime (std::string &, int &, bool &);
		
		bool takeTime(std::string &, int &, bool &);
		void checkAMPM (std::string &, int , int &, bool &, int);
		bool isTimeValid(int);
		bool extractNum (std::string, int &, int &);
		
		void countWord(std::string, int &);
		void changeToLower(std::string &);
		void extractRemainingStr(std::string &, std::string &, size_t);
		void removeNonTimeChar(std::string &);
		
		void updateTime();
		bool checkStartEnd();
		
		int &getStart();
		int &getEnd();
};

#endif