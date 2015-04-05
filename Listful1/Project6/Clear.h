#ifndef CLEAR_H
#define CLEAR_H

#include "DataStore.h"

class Clear {
public:
	Clear() {};
	void clearFile(std::string &, DataStore &);
};

#endif