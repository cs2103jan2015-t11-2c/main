#ifndef DELETE_H
#define DELETE_H

#include "DataStore.h"

class Delete {
public:
	Delete() {};
	void deleteContent(std::string &, DataStore &, int = 0);
	int getContentIndex(DataStore &, std::string);
};

#endif