#ifndef EDIT_H
#define EDIT_H

#include "DataStore.h"

class Edit {
private:
	enum subCategory {
		SUBJECT, TIME, DATE, IMPT, CATEGORY, INVALID
	};

	int category;

public:
	Edit(){};
	void editFunction(std::string &, DataStore &, std::string , std::string, int);
	int determineCategory(std::string);
	int getContentIndex(DataStore &, std::string);
};

#endif
