#ifndef EDIT_H
#define EDIT_H

#include "DataStore.h"

class Edit {
private:
	enum subCategory {
		TIME, SUBJECT, DATE, PRIORITY, CATEGORY, INVALID
	};


public:
	Edit(){};
	bool editContent(DataStore &, std::string, int, int);
	int determineCategory(std::string);
};

#endif
