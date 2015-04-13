//@author A0116177E
#ifndef ADD_H
#define ADD_H

#include "DataStore.h"
#include "Search.h"

class Add {
	public:
		Add() {};

		bool addContent(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, bool);
	
		bool isSameDate(DataStore, int);
		bool isSameTime(DataStore, int);
		void checkDateTime(DataStore, std::ostringstream &, bool, bool);
		void checkDuplicate(DataStore, std::ostringstream &);

		void addToDataBase(DataStore &, bool, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		bool addScheduled(DataStore &, bool);
		bool addDeadline(DataStore &, bool);
		void addFloat(DataStore &, bool);

		bool isAdded(DataStore &, std::vector <Entry> &, std::vector <Entry>::iterator, int, bool);

		void selectDataBase(DataStore &, std::vector <Entry> &, bool);
		void revertDataBase(DataStore &, std::vector <Entry> &, bool);
};

#endif