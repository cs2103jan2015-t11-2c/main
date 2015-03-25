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
	void convertToTFH(size_t, size_t, size_t, size_t, int, int &);
	bool checkHourValid(int, int &);
	void updateStr(std::string &, std::string &, size_t);
	bool checkMinValid(int &, int);
	bool checkRealTime (std::string &, std::string &, int &, int &, int &);
	void convertTime (std::string, int &,int &, int &);
	bool extractTime (std::string &, int);
	void updateTime();
	void checkStartEnd();

	int getStart();
	int getEnd();
};

#endif