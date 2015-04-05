#ifndef ADD_H
#define ADD_H

#include "DataStore.h"

class Add {
public:
	Add() {};

	bool addContent(DataStore &);
	bool isDuplicate(DataStore);
	bool isSameDate(DataStore, int);
	bool isSameTime(DataStore, int);
	void insertionAdd(DataStore &);
	bool sameDayAdd(DataStore &);
	bool diffDayAdd(DataStore &);
	void diffDayAdd2(DataStore &);

	bool isDatePassed(DataStore &,  int date, int month, int year, int index);
	struct std::tm tm;
};

#endif