#ifndef ADD_H
#define ADD_H

#include "DataStore.h"

class Add {
public:
	Add() {};

	void addContent(DataStore &);
	bool isDuplicate(DataStore &);
	bool isSameDate(DataStore &, int, int, int, int);
	bool isSameTime(DataStore &, int, int, int);
};

#endif