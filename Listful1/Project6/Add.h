#ifndef ADD_H
#define ADD_H

#include "DataStore.h"

class Add {
private:
	DataStore data;

public:
	Add() {};
	void addContent(std::string &, int &, std::string, int, int, int, int, int, std::string, std::string, DataStore &);
	bool isDuplicate(DataStore &);
	bool isSameDate(DataStore &, int, int, int, int);
	bool isSameTime(DataStore &, int, int, int);
};

#endif