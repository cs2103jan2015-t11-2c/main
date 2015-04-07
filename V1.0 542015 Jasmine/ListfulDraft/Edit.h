#ifndef EDIT_H
#define EDIT_H

#include "DataStore.h"
#include "Add.h"

class Edit {
private:
	int _category;
	Entry _editEntry;

public:
	Edit() {};

	bool editContent(DataStore &, int, std::ostringstream &);
	void editTime(DataStore &, Add &, int, std::ostringstream &, bool);
	void editDate(DataStore &, Add &, int, std::ostringstream &, bool);

	int &getCat();
};

#endif