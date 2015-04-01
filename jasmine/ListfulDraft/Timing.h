#ifndef TIME_H
#define TIME_H

#include "DataStore.h"
#include "Date.h"

class Timing {
private:
	int _startTime;
	int _endTime;

	Date date;

public:
	Timing();
	
	void changeToLower(std::string &);
	bool checkHourValid(int);
	bool checkMinValid(int);
	void updateStr(std::string &, std::string &, size_t);
	bool extractNum (std::string, int &, int &);
	void updateTime();
	void removeNonTimeChar(std::string &);
	void countWord(std::string &, int &);
	bool checkDate(std::string &, int);
	bool takeTime(std::string &, std::string &, int &);
	void checkAMPM (std::string &, std::string &, int , int &);
	bool extractTime (std::string &, int &, size_t &, std::string);
	//void checkStartEnd();

	int getStart();
	int getEnd();
};

#endif