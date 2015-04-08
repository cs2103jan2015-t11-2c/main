#ifndef ADD_H
#define ADD_H

#include "DataStore.h"
#include "Display.h"

class Add {
public:
	Add() {};

	bool addContent(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, bool);

	void checkDuplicate(DataStore, std::ostringstream &);
	bool isSameDate(DataStore, int);
	bool isSameTime(DataStore, int);

	void insertionAdd(DataStore &, bool, std::ostringstream &, std::ostringstream &, std::ostringstream &);
	bool scheduledAdd(DataStore &, bool);
	bool deadlineAdd(DataStore &, bool);
	void floatAdd(DataStore &, bool);
	bool pushData(DataStore &, std::vector <Entry>::iterator, int, bool);
};

#endif