#ifndef DATASTORE_H
#define DATASTORE_H

#include "Entry.h"

class DataStore {
private:
	std::vector <Entry> _dataBase;

	std::queue <std::vector <Entry>> _pastData;

	std::queue <std::vector <Entry>> _futureData;

	Entry _tempEntry;

public:
	DataStore () {};

	std::string getDataString(int &);
	int countDigit(int &);
	void printTimeZero(int &, std::ostringstream &);
	void printDateZero(int &, std::ostringstream &);
	//void entryType(std::string &, int &, int &, int &, int &, int &, std::string &, std::string &);
	void updateFile(std::string &);
	void savePrevFile();
	void undoData();
	void redoData();

	Entry getEntry(int &);
	Entry get_tempEntry();
};

#endif