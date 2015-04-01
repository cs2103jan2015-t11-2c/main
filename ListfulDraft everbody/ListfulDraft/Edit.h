#ifndef EDIT_H
#define EDIT_H

#include "DataStore.h"

class Edit {
private:
	enum subCategory {
		DATE, SUBJECT, TIME, PRIORITY, CATEGORY, INVALID
	};


public:
	Edit(){};
	bool editContent(DataStore &, std::string, int, int);
	int determineCategory(std::string);
};

#endif
