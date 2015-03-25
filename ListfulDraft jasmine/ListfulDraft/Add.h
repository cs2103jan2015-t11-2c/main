#ifndef ADD_H
#define ADD_H

#include "DataStore.h"

class Add {
public:
	Add() {};

	bool addContent(DataStore &, std::string);
	bool isDuplicate(DataStore);
	bool isSameDate(DataStore, int);
	bool isSameTime(DataStore, int);
};

#endif