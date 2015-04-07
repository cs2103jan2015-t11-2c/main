#ifndef EDIT_H
#define EDIT_H

#include "DataStore.h"

class Edit {
private:
	int _category;
	Entry _editEntry;

public:
	Edit() {};

	bool editContent(DataStore &, int, std::ostringstream &);

	int &getCat();
};

#endif