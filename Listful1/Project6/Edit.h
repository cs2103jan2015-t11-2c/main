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
	void editContent(std::string &, DataStore &, std::string, int, std::string, int = 0, int = 0, int = 0);
	int determineCategory(std::string);
	int getContentIndex(DataStore &, std::string);
};

#endif
