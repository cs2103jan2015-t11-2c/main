#ifndef DELETE_H
#define DELETE_H

#include "DataStore.h"

class Delete {
public:
	Delete() {};

	//bool deleteContent(DataStore &, int);

	bool deleteContent(DataStore &, std::string, std::ostringstream &);
	bool deletebyIndex(DataStore &, int, std::ostringstream &);
	bool deletebySubject(DataStore &, std::string, std::string, std::ostringstream &);

	//int getContentIndex(DataStore &, std::string);
};

#endif