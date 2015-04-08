#ifndef DELETE_H
#define DELETE_H

#include "DataStore.h"
#include "Display.h"
#include "Add.h"

class Delete {
	int _index;

	std::vector <int> _indexList;

public:
	Delete() {};

	bool deleteContent(DataStore &, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, bool &);
	bool deleteByIndex(DataStore &, std::string, std::ostringstream &,std::ostringstream &, std::ostringstream &, std::ostringstream &);
	bool deleteBySubject(DataStore &, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, bool &);
	bool deleteMore(DataStore &, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
	void checkDataBaseEmpty(DataStore &, std::ostringstream &);

	int &getIndex();
};

#endif