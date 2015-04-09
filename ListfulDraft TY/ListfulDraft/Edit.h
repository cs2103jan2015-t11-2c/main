//@author A0116237L
#ifndef EDIT_H
#define EDIT_H

#include "DataStore.h"
#include "Add.h"
#include "Display.h"

class Edit {
private:
	int _category;
	Entry _editEntry;

public:
	Edit() {};

	bool editContent(DataStore &, int, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
	void editTime(DataStore &, int);
	void editDate(DataStore &, int);

	int &getCat();
};

#endif