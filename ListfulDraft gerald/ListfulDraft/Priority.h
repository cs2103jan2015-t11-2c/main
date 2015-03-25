#ifndef PRIORITY_H
#define PRIORITY_H

#include "DataStore.h"

class Priority {
private:
	std::string _priority;

public:
	Priority();

	bool Priority::checkPriority(std::string &);

	std::string getPriority();
	
	void changeToLower(std::string &);
	void convertToTFH(std::string, size_t, size_t, size_t, size_t, int, int &);
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