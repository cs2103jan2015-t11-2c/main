#ifndef DELETE_H
#define DELETE_H

#include "DataStore.h"

class Delete {
public:
	Delete() {};

	bool deleteContent(DataStore &, int);
	int getContentIndex(DataStore &, std::string);
};

#endif