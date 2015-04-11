#ifndef SEARCH_H
#define SEARCH_H

#include "DataStore.h"
#include "Add.h"
#include "Display.h"

class Search {
private:
	enum subCategory {
			SUBJECT, DATE, TIME, PRIORITY, CATEGORY, INVALIDCAT
	};

	int _category;

public:
	Search() {};

	bool searchFile(DataStore &, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
	bool foundSubject(DataStore &, std::string &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, Add &, Display &);
	bool foundCatPriority(DataStore &, std::string &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &,  Add &, Display &);
	bool foundDate(DataStore &, std::string &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, Add &, Display &);
	bool foundTime(DataStore &, std::string &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &,  Add &, Display &);
	
	void printSearchedContent(DataStore &, std::ostringstream &, Display &);

	int &getCat();
};
#endif