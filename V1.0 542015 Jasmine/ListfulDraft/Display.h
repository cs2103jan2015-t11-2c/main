#ifndef DISPLAY_H
#define DISPLAY_H

#include "DataStore.h"

class Display {
private:
	static const int FLOAT_SUB_SIZE;
	static const int NON_FLOAT_SUB_SIZE;

public:
	Display() {};

	std::string getTempDataString(DataStore &, int, bool);
	void getTempDisplay(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
	void getReminder(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
	bool getDisplay(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
	std::string getDataString(DataStore &, int, bool);
	void printSub(DataStore &, std::ostringstream &, int, int, bool, bool);
	void printDate(DataStore &, std::ostringstream &, int, bool);
	void printTime(DataStore &, std::ostringstream &, int, bool);
	void printCat(DataStore &, std::ostringstream &, int, bool);
	void printDone(DataStore &, std::ostringstream &, int, bool);
	
	std::string getDate(DataStore &, int);
	std::string getTime(DataStore &, int);

	int countDigit(int);
	void printZero(int, std::ostringstream &, int);
	void printSpace(std::ostringstream &, int);

	void setColour(int);
	
};

#endif