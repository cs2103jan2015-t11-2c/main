#ifndef SEARCH_H
#define SEARCH_H

#include "DataStore.h"

class Search
{
	private:
	enum subCategory {
		SUBJECT, TIME, DATE, IMPT, CATEGORY, INVALID
	};

	int category;

	public:
	Search(){};
	void searchFile(std::string &, DataStore &, std::string , std::string );
	bool foundSubject(DataStore &, std::string &);
	void printSearchedContent(DataStore &);
	int determineCategory(std::string );
};
#endif

