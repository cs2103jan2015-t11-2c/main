#ifndef DELETE_H
#define DELETE_H

#include "DataStore.h"
#include "Display.h"
#include "Add.h"

class Delete {
	private:
		Add add;
		Display show;

	public:
		Delete() {};

		void remove(DataStore &, std::vector <int>);
		bool isRepeat(DataStore &, std::vector <int>, int);
		bool deleteContent(DataStore &, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, bool &);
		bool deleteByIndex(DataStore &, std::string, std::ostringstream &,std::ostringstream &, std::ostringstream &, std::ostringstream &);
		bool deleteBySubject(DataStore &, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, bool &);
		bool deleteMore(DataStore &, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void checkDataBaseEmpty(DataStore &, std::ostringstream &);

		int &getIndex();
};

#endif