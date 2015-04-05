#ifndef DATASTORE_H
#define DATASTORE_H

#include "Entry.h"

class DataStore {
private:
	std::vector <Entry> _dataBase;
	std::vector <Entry> _tempDataBase;
	std::vector <std::vector <Entry>> _pastData;
	std::vector <std::vector <Entry>> _futureData;

	Entry _tempEntry;
	std::string _fileName;

public:
	DataStore () {};
	void init (std::string);

	std::string getDataString(int);
	std::string getTempDataString(int);
	int countDigit(int &);
	void printZero(int &, std::ostringstream &, int);
	void printSpace(std::ostringstream &, int);

	void updateFile();
	void savePrevFile();
	bool undoData();
	bool redoData();

	void setColour(int);
	
	std::vector <Entry> &getData();
	std::vector <Entry> &getTempData();
	Entry &getEntry(int);
	Entry &get_tempEntry();
	
	std::string getDate(Entry);
    std::string getTime(Entry);
};

#endif