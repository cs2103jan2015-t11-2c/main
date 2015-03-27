#ifndef SORT_H
#define SORT_H

#include "DataStore.h"

class Sort {
private:
	enum subCategory {
		DATE, SUBJECT, TIME, PRIORITY, CATEGORY, INVALID
	};

	int _category;

public:
	Sort() {};

	void sortSwitch(int &, int &, DataStore &);
	void compareLineSize(std::string &, std::string &, std::string &);
	bool compareWord(std::string &, std::string &, std::string &);
	void sortSub(DataStore &);
	void sortDate(DataStore &);
	void sortTime(DataStore &);
	void sortCat(DataStore &);
	void sortPriority(DataStore &);
	bool sortContent(DataStore &);

	int &getSortCat();
};

#endif