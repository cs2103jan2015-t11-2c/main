#ifndef SORT_H
#define SORT_H

#include "DataStore.h"

class Sort
{
	private:
	enum subCategory {
		SUBJECT, TIME, DATE, IMPT, CATEGORY, INVALID
	};

	int category;
public:
	Sort() {};
	int determineCategory(std::string);
	void Switch(int &, int &, DataStore &);
	void sort(std::string &, DataStore &, std::string);
};

#endif