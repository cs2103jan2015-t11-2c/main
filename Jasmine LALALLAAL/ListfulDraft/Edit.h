#ifndef EDIT_H
#define EDIT_H

#include "DataStore.h"
#include "Add.h"
#include "Display.h"
#include "Sort.h"

class Edit {
private:
	int _category;
	Entry _editEntry;

public:
	Edit() {};
	
	bool isRepeat(DataStore &, std::vector <int>, int);
	bool checkComplete(DataStore &, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &);
	bool editContent(DataStore &, int, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
	void editTime(DataStore &, int);
	void editDate(DataStore &, int);

	int &getCat();
};

#endif