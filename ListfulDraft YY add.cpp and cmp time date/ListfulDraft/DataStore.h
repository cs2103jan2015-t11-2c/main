#ifndef DATASTORE_H
#define DATASTORE_H

#include "Entry.h"

class DataStore {
public:	
	std::vector <Entry> _dataBase;

	std::vector <Entry> _tempDataBase;

	std::vector <std::vector <Entry>> _pastData;

	std::vector <std::vector <Entry>> _futureData;

	Entry _tempEntry;

	std::string _fileName;

	DataStore () {};
	DataStore (std::string);

	std::string getDataString(int &);
	int countDigit(int &);
	void printZero(int &, std::ostringstream &, int);
	void printSpace(std::ostringstream &, int);
	//void entryType(std::string &, int &, int &, int &, int &, int &, std::string &, std::string &);
	void updateFile();
	void savePrevFile();
	void undoData();
	void redoData();

	std::vector <Entry> &getData();
	std::vector <Entry> &getTempData();
	Entry &getEntry(int);
	Entry &get_tempEntry();
	
	//search function
	void updateTempDataBase(Entry);
	std::string printTempDataBase();
	std::string getDate(Entry);
    std::string getTime(Entry);
};

#endif