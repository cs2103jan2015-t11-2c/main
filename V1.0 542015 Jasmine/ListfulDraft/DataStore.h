#ifndef DATASTORE_H
#define DATASTORE_H

#include "Entry.h"

class DataStore {
private:
	std::vector <Entry> _dataBase;
	std::vector <std::vector <Entry>> _pastData;
	std::vector <std::vector <Entry>> _futureData;

	std::vector <Entry> _tempDataBase;

	Entry _tempEntry;
	Entry _emptyEntry;
	std::string _fileName;

public:
	DataStore () {};
	void init (std::string);

	void updateFile(DataStore &);
	void savePrevFile();
	bool undoData(DataStore &);
	bool redoData(DataStore &);
	
	std::vector <Entry> &getData();
	std::vector <Entry> &getTempData();
	Entry &getEntry(int);
	Entry &get_tempEntry();
	Entry &get_emptyEntry();
	/*
	std::string getDate(Entry);
    std::string getTime(Entry);
	std::string getTempDataString(int);*/
};

#endif