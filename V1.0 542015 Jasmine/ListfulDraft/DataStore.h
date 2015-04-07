#ifndef DATASTORE_H
#define DATASTORE_H

#include "Entry.h"

class DataStore {
private:
	std::vector <Entry> _dataBase;
	std::vector <std::vector <Entry>> _pastData;
	std::vector <std::vector <Entry>> _futureData;

	std::vector <std::string> _pastActionLog;
	std::vector <std::string> _futureActionLog;

	std::vector <Entry> _tempDataBase;

	Entry _tempEntry;
	Entry _emptyEntry;
	std::string _fileName;

public:
	DataStore () {};

	void updateFile(DataStore &);
	void savePrevFile();
	bool undoData(DataStore &, std::ostringstream &);
	bool redoData(DataStore &, std::ostringstream &);
	
	std::string &getFileName();

	std::vector <Entry> &getData();
	std::vector <Entry> &getTempData();

	std::vector <std::string> &getPastActionLog();
	std::vector <std::string> &getFutureActionLog();

	Entry &getEntry(int);
	Entry &get_tempEntry();
	Entry &get_emptyEntry();

	/*
	std::string getDate(Entry);
    std::string getTime(Entry);
	std::string getTempDataString(int);*/
};

#endif