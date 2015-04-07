#ifndef DISPLAY_H
#define DISPLAY_H

#include "DataStore.h"

class Display {
private:
	static const int FLOAT_SUB_SIZE;
	static const int NON_FLOAT_SUB_SIZE;

public:
	Display() {};

	void getReminder(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
	void getDeleteDisplay(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
	bool getDisplay(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
	std::string getDataString(DataStore &, int, bool);
	void printSub(DataStore &, std::ostringstream &, int, int, bool);
	void printDate(DataStore &, std::ostringstream &, int);
	void printTime(DataStore &, std::ostringstream &, int);
	void printCat(DataStore &, std::ostringstream &, int);
	void printDone(DataStore &, std::ostringstream &, int);

	int countDigit(int);
	void printZero(int, std::ostringstream &, int);
	void printSpace(std::ostringstream &, int);

	void setColour(int);
	
};

#endif