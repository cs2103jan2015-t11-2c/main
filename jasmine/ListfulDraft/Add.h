#ifndef ADD_H
#define ADD_H

#include "DataStore.h"

class Add {
public:
	Add() {};

	bool addContent(DataStore &, std::ostringstream &);
	void checkDuplicate(DataStore, std::ostringstream &);
	bool isSameDate(DataStore, int);
	bool isSameTime(DataStore, int);
	void insertionAdd(DataStore &);
	bool sameDayAdd(DataStore &);
	bool diffDayAdd(DataStore &);
	void floatAdd(DataStore &);
};

#endif