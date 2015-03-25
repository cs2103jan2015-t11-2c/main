#ifndef DATASTORE_H
#define DATASTORE_H

#include "Entry.h"

class DataStore {
public:	
	std::vector <Entry> _dataBase;

	std::queue <std::vector <Entry>> _pastData;

	std::queue <std::vector <Entry>> _futureData;

	Entry _tempEntry;

	DataStore () {};

	std::string getDataString(int &);
	int countDigit(int &);
	void printZero(int &, std::ostringstream &, int);
	//void entryType(std::string &, int &, int &, int &, int &, int &, std::string &, std::string &);
	void updateFile(std::string &);
	void savePrevFile();
	void undoData();
	void redoData();

	std::vector <Entry> &getData();
	Entry &getEntry(int &);
	Entry &get_tempEntry();
};

#endif