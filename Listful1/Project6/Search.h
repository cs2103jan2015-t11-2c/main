#ifndef SEARCH_H
#define SEARCH_H

#include "DataStore.h"

class Search
{
public:
	Search(){};
	void searchFile(std::string &fileName, DataStore &, std::string readInLine);
	bool foundContent(DataStore &, std::string &readInLine);
	void printSearchedContent(DataStore &data);
};
#endif

