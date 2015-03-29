#ifndef TIME_H
#define TIME_H

#include "DataStore.h"

class Time {
private:
	int _startTime;
	int _endTime;

public:
	Time();
	
	void changeToLower(std::string &);
	bool checkHourValid(int);
	bool checkMinValid(int);
	void updateStr(std::string &, std::string        &, size_t);
	bool extractNum (std::string, int &, int &);
	void updateTime();
	void removeNonTimeChar(std::string &);
	int countWord(std::string);
	bool checkDate(std::string, int);
	bool takeTime(std::string &, std::string &, int &);
	void checkAMPM (std::string &, std::string &, int , int &);
	bool extractTime (std::string &, int &);
	//void checkStartEnd();

	int getStart();
	int getEnd();
};

#endif