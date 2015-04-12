#ifndef DELETE_H
#define DELETE_H

#include "DataStore.h"
#include "Search.h"
#include "Add.h"

class Delete {
	private:
		Add add;
		Search search;

	public:
		Delete() {};

		bool deleteContent(DataStore &, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, bool &);
		
		bool deleteByIndex(DataStore &, std::string, std::ostringstream &,std::ostringstream &, std::ostringstream &, std::ostringstream &);
		bool deleteBySubject(DataStore &, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, bool &);
		
		void deleteAll(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, bool &);
		void remove(DataStore &, std::vector <int>);
		bool isRepeat(DataStore &, std::vector <int>, int);
		void checkDataBaseEmpty(DataStore &, std::ostringstream &);

		int &getIndex();
};

#endif