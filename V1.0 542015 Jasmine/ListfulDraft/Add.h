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
	bool scheduledAdd(DataStore &);
	bool deadlineAdd(DataStore &);
	void floatAdd(DataStore &);
	bool pushData(DataStore &, std::vector <Entry>::iterator, int);
};

#endif