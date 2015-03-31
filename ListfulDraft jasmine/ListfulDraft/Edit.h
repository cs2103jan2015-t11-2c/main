#ifndef EDIT_H
#define EDIT_H

#include "DataStore.h"

class Edit {
private:
	enum subCategory {
		SUBJECT, TIME, DATE, IMPT, CATEGORY, INVALID
	};


public:
	Edit(){};
	bool editContent(DataStore &, std::string , std::string, int, int);
	int determineCategory(std::string);
};

#endif
