#ifndef SEARCH_H
#define SEARCH_H

#include "DataStore.h"

class Search
{
	private:
	enum subCategory {
			DATE, SUBJECT, TIME, PRIORITY, CATEGORY, INVALIDCAT
		};



	public:
	Search(){};
	bool searchFile(DataStore &, std::string , int );
	bool foundSubject(DataStore &, std::string &);
	bool foundCategory(DataStore &, std::string &);
	bool foundPriority(DataStore &, std::string &);
	bool foundDate(DataStore &, std::string &);
	bool foundTime(DataStore &, std::string &);
	
	void printSearchedContent(DataStore &);
	int determineCategory(std::string );
};
#endif

