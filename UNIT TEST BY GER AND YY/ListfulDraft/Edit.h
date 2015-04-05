#ifndef EDIT_H
#define EDIT_H

#include "DataStore.h"

class Edit {
private:
	enum subCategory {
		DATE, SUBJECT, TIME, PRIORITY, CATEGORY, INVALID
	};

	int _category;

public:
	Edit() {};

	bool editContent(DataStore &, std::string, int);

	int &getCat();
};

#endif