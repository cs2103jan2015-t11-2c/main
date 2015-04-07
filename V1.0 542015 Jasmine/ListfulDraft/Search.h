#ifndef SEARCH_H
#define SEARCH_H

#include "DataStore.h"
#include "Sort.h"

class Search {
private:
	enum subCategory {
			DATE, SUBJECT, TIME, PRIORITY, CATEGORY, INVALIDCAT
	};

	int _category;

public:
	Search() {};
	/*
	bool searchFile(DataStore &, std::string, std::ostringstream &);
	bool foundSubject(DataStore &, std::string &, std::ostringstream &);
	bool foundCategory(DataStore &, std::string &, std::ostringstream &);
	bool foundPriority(DataStore &, std::string &, std::ostringstream &);
	bool foundDate(DataStore &, std::string &, std::ostringstream &);
	bool foundTime(DataStore &, std::string &, std::ostringstream &);
	
	void printSearchedContent(DataStore &, std::ostringstream &);
	*/
	int &getCat();
};
#endif
