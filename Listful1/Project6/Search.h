#ifndef SEARCH_H
#define SEARCH_H

#include "DataStore.h"

class Search
{
public:
	Search(){};
	void searchFile(std::string &fileName, std::string readInLine);
	bool foundContent(std::string &readInLine);
};
#endif

