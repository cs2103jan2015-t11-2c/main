#ifndef DELETE_H
#define DELETE_H

#include "DataStore.h"

class Delete {
public:
	Delete() {};

	bool deleteContent(DataStore &, int);

	//void deleteContent(DataStore &, std::string);
	//void deletebyIndex(DataStore &, int);
	//void deletebySubject(DataStore &, std::string, std::string);

	int getContentIndex(DataStore &, std::string);
};

#endif